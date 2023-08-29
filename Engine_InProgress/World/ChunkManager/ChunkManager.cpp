#include "ChunkManager.hpp"

void ChunkManager::Begin()
{
    chunks_in_square_line = 2*chunks_draw_distance - 1;
}

void ChunkManager::Update(float delta)
{
    UpdateChunksVisibility();
}

void ChunkManager::Draw(float delta)
{
    for (auto &[key, val] : loaded_chunks)
    {
        (val)->Draw(delta);
    }
}

void ChunkManager::UpdateChunksVisibility()
{
    Rect2 screen_bounds = Render::GetDisplayBoundsInWorldCoordinates();

    //get center of screen (viewport)
    Vec2 cn = screen_bounds.GetCenter();

    //get central chunk index
    Vec2i cn_chunk_index;
    cn_chunk_index.x = std::floor(cn.x / (CHUNK_SIZE_PIXELS) / CHUNK_DRAW_SCALE);
    cn_chunk_index.y = int(-(cn.y / (CHUNK_SIZE_PIXELS) / CHUNK_DRAW_SCALE));
    if(cn.y < 0.0f) cn_chunk_index.y += 1;

    if((camera_last_position - cn).Length() < CHUNK_SIZE_PIXELS*CHUNK_DRAW_SCALE/2 && cn_chunk_index != Vec2i(0,0)) 
    {
        DrawBufferedChunks();
        return;
    }
    camera_last_position = cn;

    //get left-up corner of inner big square
    Vec2i lu_chunk_index;
    lu_chunk_index.x = cn_chunk_index.x - chunks_in_square_line / 2;
    lu_chunk_index.y = cn_chunk_index.y + chunks_in_square_line / 2;

    for (int i = 0; i < chunks_in_square_line; i++)
    {
        for (int j = 0; j < chunks_in_square_line; j++)
        {
            Vec2i idx = {lu_chunk_index.x + i, lu_chunk_index.y - j};
            if(loaded_chunks.count(idx) == 0 && pre_loaded_chunks.count(idx) == 0)
            {
                auto t = SceneManager::CreateSceneObject<Chunk>(std::to_string(idx.x) + std::to_string(idx.y) + "_chunk_gen", "class_Chunk", false);
                t->Begin();
                t->SetChunkIndex(idx);
                chunk_generation_queue.push_back(idx);
                pre_loaded_chunks[idx] = t;
            }
        }
    }

    DrawBufferedChunks();

    std::vector<Vec2i> far_chunks;
    for (auto i = loaded_chunks.begin(); i != loaded_chunks.end(); i++)
    {
        if((i->second->chunk_center_position - cn).Length() >= chunks_draw_distance * CHUNK_SIZE_PIXELS * CHUNK_DRAW_SCALE * far_chunks_distance_mul)
        {
            far_chunks.push_back(i->first);
            continue;
        }
        if((i->second->chunk_center_position - cn).Length() >= chunks_draw_distance * CHUNK_SIZE_PIXELS * CHUNK_DRAW_SCALE)
        {
            i->second->chunk_is_visible = false;
            visible_chunks.erase(i->first);
        }
        else if(i->second->chunk_is_visible == false)
        {
            visible_chunks[i->first] = i->second;
            i->second->chunk_is_visible = true;
        }
    }
    
    for (size_t i = 0; i < far_chunks.size(); i++)
    {   
        loaded_chunks[far_chunks[i]]->UnloadChunk();
        SceneManager::DestroySceneObject<Chunk>(loaded_chunks[far_chunks[i]]);
        visible_chunks.erase(far_chunks[i]);
        loaded_chunks.erase(far_chunks[i]);
    }
}

void ChunkManager::DrawBufferedChunks()
{
    for (size_t i = 0; i < chunks_per_frame_generation; i++)
    {
        if(last_draw_chunk_counter < chunk_generation_queue.size())
        {
            loaded_chunks[chunk_generation_queue[last_draw_chunk_counter]] = pre_loaded_chunks[chunk_generation_queue[last_draw_chunk_counter]];
            loaded_chunks[chunk_generation_queue[last_draw_chunk_counter]]->GenerateChunk();
            pre_loaded_chunks.erase(chunk_generation_queue[last_draw_chunk_counter]);
            last_draw_chunk_counter++;
        }
        else
        {
            chunk_generation_queue.clear();
            last_draw_chunk_counter = 0;
            break;
        }
    }
}
