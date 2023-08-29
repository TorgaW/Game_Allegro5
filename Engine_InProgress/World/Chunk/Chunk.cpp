#include "Chunk.hpp"

void Chunk::Begin()
{
    chunk_ground_mask = al_create_bitmap(CHUNK_TILES_NUM, CHUNK_TILES_NUM);
    chunk_final_bitmap = al_create_bitmap(CHUNK_SIZE_PIXELS, CHUNK_SIZE_PIXELS);
    chunk_temp_final_bitmap = al_create_bitmap(CHUNK_SIZE_PIXELS, CHUNK_SIZE_PIXELS);
    chunk_temp_map = al_create_bitmap(CHUNK_TILES_NUM, CHUNK_TILES_NUM);
    chunk_ground_mask_generator_shader = ShaderManager::GetShader("ChunkGroundMaskGenerator");
    chunk_ground_generator_shader = ShaderManager::GetShader("ChunkGroundGenerator");

    for (int i = 0; i < CHUNK_TILES_NUM; i++)
    {
        for (int j = 0; j < CHUNK_TILES_NUM; j++)
        {
            chunk_tiles[i*j] = Tile({i, j});
        }
    }
}

void Chunk::Draw(float delta)
{
    if(chunk_is_visible && chunk_is_loaded)
    al_draw_scaled_bitmap(chunk_final_bitmap, 0, 0, CHUNK_SIZE_PIXELS, CHUNK_SIZE_PIXELS,
                        chunk_position.x, chunk_position.y,
                        CHUNK_SIZE_PIXELS * CHUNK_DRAW_SCALE, CHUNK_SIZE_PIXELS * CHUNK_DRAW_SCALE,
                        0);
    
    // al_draw_rectangle(chunk_position.x, chunk_position.y, 
    // chunk_position.x + CHUNK_SIZE_PIXELS*CHUNK_DRAW_SCALE, chunk_position.y + CHUNK_SIZE_PIXELS*CHUNK_DRAW_SCALE,EngineColors::red, 2.0f);
}

void Chunk::SetChunkIndex(Vec2i idx)
{
    if(idx == chunk_index || std::abs(idx.x) >= MAX_CHUNK_INDEX_VALUE || std::abs(idx.y) >= MAX_CHUNK_INDEX_VALUE)
        return;
    
    chunk_index = idx;
    chunk_position = {idx.x * CHUNK_SIZE_PIXELS * CHUNK_DRAW_SCALE, idx.y * CHUNK_SIZE_PIXELS * CHUNK_DRAW_SCALE * (-1)};
    chunk_center_position = Vec2(chunk_position.x + CHUNK_SIZE_PIXELS/2, chunk_position.y + CHUNK_SIZE_PIXELS/2);
    chunk_bounds = {Vec2(chunk_position.x, chunk_position.y), Vec2(CHUNK_SIZE_PIXELS * CHUNK_DRAW_SCALE)};
    t_chunk_index[0] = idx.x;
    t_chunk_index[1] = idx.y;
}

void Chunk::GenerateChunk()
{
    if(chunk_is_loaded) return;
    al_set_target_bitmap(chunk_ground_mask);
    al_use_shader(chunk_ground_mask_generator_shader);
    al_set_shader_int("seed", chunk_seed);
    al_set_shader_float_vector("chunk_index", 2, t_chunk_index, 1);
    al_draw_bitmap(chunk_temp_map, 0, 0, 0);

    al_set_target_bitmap(chunk_final_bitmap);
    al_use_shader(chunk_ground_generator_shader);
    al_set_shader_int("seed", chunk_seed);
    al_set_shader_float_vector("chunk_index", 2, t_chunk_index, 1);
    al_set_shader_int("tile_size", CHUNK_TILE_SIZE);
    al_set_shader_sampler("ground_mask", chunk_ground_mask, 1);
    al_draw_bitmap(chunk_temp_final_bitmap, 0, 0, 0);

    Render::SetViewportAsRenderTarget();
    al_use_shader(nullptr);
    chunk_is_loaded = true;
}

void Chunk::UnloadChunk()
{
    al_destroy_bitmap(chunk_ground_mask);
    al_destroy_bitmap(chunk_final_bitmap);
    al_destroy_bitmap(chunk_temp_map);
    al_destroy_bitmap(chunk_temp_final_bitmap);
}
