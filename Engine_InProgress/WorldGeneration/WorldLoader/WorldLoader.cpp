#include "WorldLoader.hpp"

void WorldLoader::Begin()
{
    chunk_square_axis_size = (chunks_draw_distance + chunks_draw_distance - 1);
    // for (size_t i = 0; i < 100; i++)
    // {
    //     Chunk *t = new Chunk(chunk_size);
    //     unloaded_chunks.push_back(t);
    // }
}

void WorldLoader::Update(float delta)
{
    Rect2 screen_bounds = Render::GetDisplayBoundsInWorldCoordinates();
    
    //get center of screen, not camera because screen = camera, it is faster
    Vec2 cn = screen_bounds.GetCenter();
    
    //check if camera position delta is too small
    if((last_spotted_camera_position - cn).Length() < camera_max_delta_trigger) return;

    last_spotted_camera_position = cn;

    //get central chunk index
    Vec2i cn_chunk_index;
    cn_chunk_index.x = std::floor(cn.x / chunk_size / chunk_draw_scale);
    cn_chunk_index.y = int(-(cn.y / chunk_size / chunk_draw_scale));
    if(cn.y < 0.0f) cn_chunk_index.y += 1;

    //get left-up corner of big square
    Vec2i lu_chunk_index;
    lu_chunk_index.x = cn_chunk_index.x - chunk_square_axis_size / 2;
    lu_chunk_index.y = cn_chunk_index.y + chunk_square_axis_size / 2;


    for (int i = 0; i < chunk_square_axis_size; i++)
    {
        for (int j = 0; j < chunk_square_axis_size; j++)
        {
            if(!loaded_chunks.count({lu_chunk_index.x + i, lu_chunk_index.y - j}))
            {   
                Vec2i p {lu_chunk_index.x + i, lu_chunk_index.y - j};
                Chunk *t = new Chunk(chunk_size);
                t->LoadChunk();
                t->SetChunkIndex(p);
                t->is_visible = true;
                visible_chunks[p] = t;
                loaded_chunks[p] = t;
            }
        }
    }
    
    std::vector<Vec2i> far_chunks;
    for (auto const &[key, val] : loaded_chunks)
    {   
        if((val->chunk_global_cen - cn).Length() >= chunks_draw_distance * chunk_size * chunk_draw_scale * far_chunks_mult)
        {
            far_chunks.push_back(key);
            continue;
        }
        if((val->chunk_global_cen - cn).Length() >= chunks_draw_distance * chunk_size * chunk_draw_scale)
        {
            val->is_visible = false;
            visible_chunks.erase(key);
        }
        else
        {
            val->is_visible = true;
            visible_chunks[key] = val;
        }
    }
    
    for (size_t i = 0; i < far_chunks.size(); i++)
    {   
        delete loaded_chunks[far_chunks[i]];
        visible_chunks.erase(far_chunks[i]);
        loaded_chunks.erase(far_chunks[i]);
    }
    
    // DebugChunks();
}

void WorldLoader::Draw(float delta)
{
    for (const auto &[key, val] : visible_chunks)
    {
        val->GenerateChunkTextures();
        val->DrawChunk();
    }
    // for (const auto &[key, val] : loaded_chunks)
    // {
    //     val->DebugChunk();
    // }
}

void WorldLoader::DebugChunks()
{
    // std::stringstream ss;
    // ss << "Loaded chunks: " << local_chunks.size();
    // int c = 0;
    // for (size_t i = 0; i < local_chunks.size(); i++)
    // {
    //     if(local_chunks[i].is_visible) c++;
    // }
    // ss << " Visible chunks: " << c;
    // EngineDebugger::PrintDebugMessage(ss.str(), al_map_rgb_f(1.0, 1.0, 0.0), 0.0);
}
