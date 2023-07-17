#include "AChunkManager.h"

SChunk::SChunk(ALLEGRO_BITMAP *bitmap, Vector2D pos, Vector2D wpos, Vector2D offset)
{
    btm = bitmap;
    coord = pos;
    worldPos = wpos;
    offsetMapPos = offset;
}

AChunkManager::~AChunkManager()
{
    al_destroy_bitmap(Chunk);
}

void AChunkManager::Begin()
{
    ChunkSize = Vector2D(1024, 1024);
    ChunkPivotPoint = (ChunkSize / 2.0f) * 4.0f;
    GrassTileSample = al_load_bitmap("Resources/Sprites/GroundPlaceHolder/Grass.png");
    WaterTileSample = al_load_bitmap("Resources/Sprites/GroundPlaceHolder/Water.png");
    Chunk = al_create_bitmap(ChunkSize.X, ChunkSize.Y);
    IgnoreDrawBounds = true;
    Layer = -100;
    Transform.Scale = {4, 4};
    sh = al_create_shader(ALLEGRO_SHADER_GLSL);
    al_attach_shader_source_file(sh, ALLEGRO_PIXEL_SHADER, "Shaders/World/Perlin.glsl");
    al_build_shader(sh);
    std::cout << al_get_shader_log(sh) << "\n";
}

void AChunkManager::GTick(float delta_time)
{
    // al_draw_scaled_bitmap(Chunk, 0, 0, ChunkSize.X, ChunkSize.Y, -ChunkPivotPoint.X, -ChunkPivotPoint.Y, ChunkSize.X * 4, ChunkSize.Y * 4, 0);
    // al_draw_bitmap(Chunk, 0, 0, 0);
    // al_draw_bitmap(GrassTileSample, 0, 0, 0);
    // al_draw_bitmap(WaterTileSample, Render::Get().GetDisplayBoundsInWorldCoordinates().p01.X - 16, Render::Get().GetDisplayBoundsInWorldCoordinates().p01.Y, 0);
    // al_set_target_bitmap(Chunk);
    // ALLEGRO_SHADER *p = Render::Get().GetShaders()->GetShader("Test #1");
    // al_use_shader(p);
    // al_set_shader_int("octaves", 1);
    // al_set_shader_float("scale", 1.0f);
    // al_set_shader_int("seed", 123456);
    // al_draw_bitmap(Chunk, 0, 0, 0);
    // al_use_shader(nullptr);
    // Render::Get().SetViewportAsRenderTarget();
    // al_draw_bitmap(Chunk, 0, 0, 0);
    // Rectangle2D MonitorBounds = Render::Get().GetDisplayBoundsInWorldCoordinates();
    // for (size_t i = 0; i < Chunks.size(); i++)
    // {
    //     if(MonitorBounds.IntersectsWith(Rectangle2D(Chunks[i].worldPos, {128*16*Transform.Scale.X, 128*16*Transform.Scale.Y})))
    //     {
    //         if(Chunks[i].btm == nullptr)
    //             Chunks[i].btm = CreateBitmapChunk(Chunks[i].offsetMapPos.X, Chunks[i].offsetMapPos.Y, 128, 128);
    //     }
    //     else
    //     {
    //         if(Chunks[i].btm != nullptr)
    //         {
    //             al_destroy_bitmap(Chunks[i].btm);
    //             Chunks[i].btm = nullptr;
    //         }
    //     }
    // }
    // Render::Get().SetViewportAsRenderTarget();
    // for (size_t i = 0; i < Chunks.size(); i++)
    // {
    //     if(Chunks[i].btm != nullptr)
    //         al_draw_scaled_bitmap(Chunks[i].btm, 0, 0, 128 * 16, 128 * 16, 
    //         Chunks[i].coord.X * 128 * 16 * 4, Chunks[i].coord.Y * 128 * 16 * 4, 
    //         128 * 16 * Transform.Scale.X, 128 * 16 * Transform.Scale.Y, 
    //         0);
    // }
}

void AChunkManager::Tick(float delta_time)
{
    // std::vector<Vector2D> t = Render::Get().GetDisplayBoundsInWorldCoordinates();
    // std::cout << "Upper: (" << t[0].X << ", " << t[0].Y << ")\n";
}

void AChunkManager::GenerateWorld()
{
    Generator.ChangeSeed();
    WorldMap = Generator.GenerateNoise(1024, 1024, 8, 1.0f);

    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            Chunks.push_back({nullptr, 
            Vector2D(i, j), 
            Vector2D(i*128*16*Transform.Scale.X, j*128*16*Transform.Scale.Y),
            Vector2D(i * 128, j * 128)
            });
        }
    }
    

    // for (size_t i = 0; i < 8; i++)
    // {
    //     for (size_t j = 0; j < 8; j++)
    //     {
    //         ALLEGRO_BITMAP *bmt = CreateBitmapChunk(i * 128, j * 128, 128, 128);
    //         SChunk tc(bmt, Vector2D(i, j),
    //         Vector2D(i*128*16*Transform.Scale.X, j*128*16*Transform.Scale.Y),
    //         Vector2D(i * 128, j * 128));
    //         Chunks.push_back(tc);
    //     }
    // }
}

ALLEGRO_BITMAP *AChunkManager::CreateBitmapChunk(uint16_t offsetX, uint16_t offsetY, uint16_t width, uint16_t height)
{
    ALLEGRO_BITMAP *bmt = al_create_bitmap(width * 16, height * 16);
    al_set_target_bitmap(bmt);
    float t = 0.0f;
    for (size_t i = offsetX; i < width + offsetX; i++)
    {
        for (size_t j = offsetY; j < height + offsetY; j++)
        {
            t = WorldMap->GetValueAt(i, j);
            if (t > 0.5f)
            {
                al_draw_bitmap_region(GrassTileSample, 0, 0, 16, 16, (i - offsetX) * 16, (j - offsetY) * 16, 0);
            }
            else
            {
                al_draw_bitmap_region(WaterTileSample, 0, 0, 16, 16, (i - offsetX) * 16, (j - offsetY) * 16, 0);
            }
        }
    }
    // al_lock_bitmap(bmt, ALLEGRO_LOCK_WRITEONLY, 0);
    // for (size_t k = 0; k < 16 * 128; k++)
    // {
    //     al_put_pixel(k, 0, al_map_rgb_f(1, 0, 0));
    //     al_put_pixel(0, k, al_map_rgb_f(1, 0, 0));
    // }
    // al_unlock_bitmap(bmt);
    return bmt;
}
