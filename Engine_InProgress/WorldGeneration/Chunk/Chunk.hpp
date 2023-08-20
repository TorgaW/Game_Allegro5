#ifndef AE86D8C2_A3F2_4920_95FE_50ADDC322E57
#define AE86D8C2_A3F2_4920_95FE_50ADDC322E57

#include "../../STD_DefaultInclude.hpp"
#include "../../ALLEGRO_DefaultInclude.hpp"
#include "../../Transforms/Primitive/Vector.hpp"
#include "../../ShaderManager/ShaderManager.hpp"
#include "../../Render/Render.hpp"
#include "../../Algo/QuadTree.hpp"

#define BC_WG_DEFAULT_CHUNK_TEX_SIZE 256.0f
#define BC_WG_MAX_CHUNK_COORD_VALUE 2147483640

class Chunk
{
public:
    Vec2i chunk_index {BC_WG_MAX_CHUNK_COORD_VALUE + 1, BC_WG_MAX_CHUNK_COORD_VALUE + 1};
    Vec2 chunk_global_pos;
    Vec2 chunk_global_cen;
    float chunk_texture_size {512.0f};
    float chunk_draw_scale {4.0f};
    Rect2 chunk_bounds;
    // Vec2 chunk_bounds {2100.0f, 2100.0f};
    float world_seed {12345.0f};

    bool is_up_to_date {false};
    bool is_loaded {false};
    bool is_visible {false};

    Bitmap *grass_texture;
    Bitmap *dirt_texture;
    Bitmap *water_texture;
    Bitmap *cobblestone_texture;

    Bitmap *chunk_texture;
    Bitmap *t_texture;

    Shader *sh_grass;
    Shader *sh_dirt;
    Shader *sh_water;
    Shader *sh_cobblestone;

    Shader *sh_terrain_blend;

    float *t_chunk_index = new float[2];

    std::vector<Ref<SceneObject>> chunk_objects_vector{};

    QuadTree chunk_collision_quad_tree {chunk_bounds};

public:
    Chunk() : chunk_texture_size(BC_WG_DEFAULT_CHUNK_TEX_SIZE) {};
    Chunk(float chunk_tex_size) : chunk_texture_size(chunk_tex_size) {};
    ~Chunk();

    void GenerateChunkTextures();
    void SetChunkIndex(Vec2i new_index);

    void UnloadChunk();
    void LoadChunk();

    void DrawChunk();
    
    void DebugChunk();

    void UpdateChunkCollision();
};

class MetaChunk
{

};
#endif /* AE86D8C2_A3F2_4920_95FE_50ADDC322E57 */
