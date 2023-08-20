#include "Chunk.hpp"

Chunk::~Chunk()
{
    UnloadChunk();
}

void Chunk::GenerateChunkTextures()
{
    if (is_up_to_date)
        return;
    if (!is_visible)
        return;

    t_chunk_index[0] = chunk_index.x;
    t_chunk_index[1] = chunk_index.y;

    // draw grass texture
    //--------------------------------------------------
    al_set_target_bitmap(grass_texture);
    al_use_shader(sh_grass);
    al_set_shader_float("seed", world_seed);
    al_set_shader_float_vector("chunk_index", 2, t_chunk_index, 1);
    al_draw_bitmap(chunk_texture, 0, 0, 0);
    //--------------------------------------------------

    // draw dirt texture
    //--------------------------------------------------
    al_set_target_bitmap(dirt_texture);
    al_use_shader(sh_dirt);
    al_set_shader_float("seed", world_seed);
    al_set_shader_float_vector("chunk_index", 2, t_chunk_index, 1);
    al_draw_bitmap(chunk_texture, 0, 0, 0);
    //--------------------------------------------------

    //draw cobblestole texture
    al_set_target_bitmap(cobblestone_texture);
    al_use_shader(sh_cobblestone);
    al_set_shader_float("seed", world_seed);
    al_set_shader_float_vector("chunk_index", 2, t_chunk_index, 1);
    al_draw_bitmap(chunk_texture, 0, 0, 0);

    // draw terrain
    //--------------------------------------------------
    al_set_target_bitmap(chunk_texture);
    al_use_shader(sh_terrain_blend);
    al_set_shader_float("seed", world_seed);
    al_set_shader_float_vector("chunk_index", 2, t_chunk_index, 1);
    al_set_shader_sampler("grass_tex", grass_texture, 1);
    al_set_shader_sampler("mossy_cobblestone_tex", cobblestone_texture, 2);
    al_set_shader_sampler("dirt_tex", dirt_texture, 3);
    al_draw_bitmap(t_texture, 0, 0, 0);
    //--------------------------------------------------
    // end of blening
    Render::SetViewportAsRenderTarget();
    al_use_shader(nullptr);

    is_up_to_date = true;
}

void Chunk::SetChunkIndex(Vec2i new_index)
{
    if(chunk_index == new_index || std::abs(new_index.x) > BC_WG_MAX_CHUNK_COORD_VALUE || std::abs(new_index.x) > BC_WG_MAX_CHUNK_COORD_VALUE) return;
    chunk_index = new_index;
    chunk_global_pos = {new_index.x * chunk_texture_size * chunk_draw_scale, new_index.y * chunk_texture_size * chunk_draw_scale * (-1.0f)};
    chunk_global_cen = {chunk_global_pos.x + (chunk_draw_scale * chunk_texture_size / 2.0f),
                        chunk_global_pos.y + (chunk_draw_scale * chunk_texture_size / 2.0f)};

                // upper-left point                 //chunk size
    chunk_bounds = {chunk_global_pos, Vec2(chunk_texture_size * chunk_draw_scale)};
    is_up_to_date = false;
}

void Chunk::UnloadChunk()
{
    if(!is_loaded) return;
    is_visible = false;
    al_destroy_bitmap(grass_texture);
    al_destroy_bitmap(dirt_texture);
    al_destroy_bitmap(water_texture);
    al_destroy_bitmap(cobblestone_texture);
    al_destroy_bitmap(chunk_texture);
    al_destroy_bitmap(t_texture);
    is_loaded = false;
}

void Chunk::LoadChunk()
{
    if(is_loaded) return;
    grass_texture = al_create_bitmap(chunk_texture_size, chunk_texture_size);
    dirt_texture = al_create_bitmap(chunk_texture_size, chunk_texture_size);
    water_texture = al_create_bitmap(chunk_texture_size, chunk_texture_size);
    cobblestone_texture = al_create_bitmap(chunk_texture_size, chunk_texture_size);
    chunk_texture = al_create_bitmap(chunk_texture_size, chunk_texture_size);
    t_texture = al_create_bitmap(chunk_texture_size, chunk_texture_size);

    sh_grass = ShaderManager::GetShader("Grass");
    sh_dirt = ShaderManager::GetShader("Dirt");
    sh_water = ShaderManager::GetShader("Water");
    sh_cobblestone = ShaderManager::GetShader("MossyCobblestone");
    sh_terrain_blend = ShaderManager::GetShader("TerrainBlending");

    is_loaded = true;
}

void Chunk::DrawChunk()
{   
    // if(!is_visible) return;
    al_draw_scaled_bitmap(chunk_texture, 0, 0, chunk_texture_size, chunk_texture_size,
                        chunk_global_pos.x, chunk_global_pos.y,
                        chunk_texture_size * chunk_draw_scale, chunk_texture_size * chunk_draw_scale,
                        0);
}

void Chunk::DebugChunk()
{
    al_draw_rectangle(chunk_bounds.p00.x, chunk_bounds.p00.y, chunk_bounds.p11.x, chunk_bounds.p11.y, EngineColors::red, 10.0);
    al_draw_circle(chunk_global_cen.x, chunk_global_cen.y, 2.0f, EngineColors::red, 5.0f);
    al_draw_circle(chunk_global_pos.x, chunk_global_pos.y, 2.0f, EngineColors::red, 20.0f);
    chunk_collision_quad_tree.DebugQuadTree();
}

void Chunk::UpdateChunkCollision()
{
    chunk_collision_quad_tree.Clear();
    chunk_collision_quad_tree = QuadTree(chunk_bounds);
    for (size_t i = 0; i < chunk_objects_vector.size(); i++)
    {
        chunk_collision_quad_tree.InsertPoint(chunk_objects_vector[i]->transform.position);
    }
}
