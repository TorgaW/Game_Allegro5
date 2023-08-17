#ifndef BEA9B3D9_2064_440F_B959_F0A8021F8D87
#define BEA9B3D9_2064_440F_B959_F0A8021F8D87

#include "../SceneManager/SceneManager.hpp"
#include "../ShaderManager/ShaderManager.hpp"
#include "../BitmapManager/BitmapManager.hpp"

class Chunk_dev : public SceneObject
{
private:
    // Bitmap *grass_tex {nullptr};
    // Bitmap *dirt_tex {nullptr};
    // Shader *noise_shader {nullptr};
    // Shader *terrain_shader {nullptr};

    Shader *sh_mossy_cobblestone {nullptr};
    Shader *sh_grass {nullptr};
    Shader *sh_dirt {nullptr};
    Shader *sh_water {nullptr};
    Shader *sh_terrain_blending {nullptr};

    Bitmap *grass_bitmap {nullptr};
    Bitmap *dirt_bitmap {nullptr};
    Bitmap *mossy_cobblestone_bitmap {nullptr};
    Bitmap *terrain_bitmap {nullptr};

    Bitmap *bitmap_t {nullptr};

    float world_seed {2.0f};

public:
    Chunk_dev(const std::string& _obj_class, const ObjectSignature& obj_sign) : 
    SceneObject(_obj_class, obj_sign)
    {};
    virtual ~Chunk_dev(){};

    virtual void Begin()
    {
        // grass_tex = BitmapManager::LoadBitmap("Resources/Sprites/Ground/Grass_pp_128.png");
        // dirt_tex = BitmapManager::LoadBitmap("Resources/Sprites/Ground/Dirt_pp_128.png");
        sh_grass = ShaderManager::GetShader("Grass");
        sh_dirt = ShaderManager::GetShader("Dirt");
        sh_water = ShaderManager::GetShader("Water");
        sh_mossy_cobblestone = ShaderManager::GetShader("MossyCobblestone");
        sh_terrain_blending = ShaderManager::GetShader("TerrainBlending");
        bitmap_t = al_create_bitmap(512, 512);
        grass_bitmap = al_create_bitmap(512, 512);
        dirt_bitmap = al_create_bitmap(512, 512);
        mossy_cobblestone_bitmap = al_create_bitmap(512, 512);
        terrain_bitmap = al_create_bitmap(512, 512);
    }

    virtual void Draw(float delta)
    {   
        //draw grass texture
        //--------------------------------------------------
        al_set_target_bitmap(grass_bitmap);
        al_use_shader(sh_grass);
        al_set_shader_float("seed", world_seed);
        float t[2] = {0, 0};
        al_set_shader_float_vector("chunk_index", 2, t, 1);
        al_draw_bitmap(bitmap_t, 0, 0, 0);
        //--------------------------------------------------

        //draw dirt texture
        //--------------------------------------------------
        al_set_target_bitmap(mossy_cobblestone_bitmap);
        al_use_shader(sh_dirt);
        al_set_shader_float("seed", world_seed);
        al_set_shader_float_vector("chunk_index", 2, t, 1);
        al_draw_bitmap(bitmap_t, 0, 0, 0);
        //--------------------------------------------------
        
        //draw terrain
        //--------------------------------------------------
        al_set_target_bitmap(terrain_bitmap);
        al_use_shader(sh_terrain_blending);
        al_set_shader_float("seed", world_seed);
        al_set_shader_float_vector("chunk_index", 2, t, 1);
        al_set_shader_sampler("grass_tex", grass_bitmap, 1);
        al_set_shader_sampler("mossy_cobblestone_tex", mossy_cobblestone_bitmap, 2);
        al_draw_bitmap(bitmap_t, 0, 0, 0);
        //--------------------------------------------------
        //end of blening

        Render::SetViewportAsRenderTarget();
        al_use_shader(nullptr);
        al_draw_scaled_bitmap(terrain_bitmap, 0, 0, 512, 512, 0, 0, 512*4, 512*4, 0);

        
        
        //draw grass texture
        //--------------------------------------------------
        al_set_target_bitmap(grass_bitmap);
        al_use_shader(sh_grass);
        al_set_shader_float("seed", world_seed);
        float t2[2] = {1, 0};
        al_set_shader_float_vector("chunk_index", 2, t2, 1);
        al_draw_bitmap(bitmap_t, 0, 0, 0);
        //--------------------------------------------------

        //draw dirt texture
        //--------------------------------------------------
        al_set_target_bitmap(mossy_cobblestone_bitmap);
        al_use_shader(sh_dirt);
        al_set_shader_float("seed", world_seed);
        al_set_shader_float_vector("chunk_index", 2, t2, 1);
        al_draw_bitmap(bitmap_t, 0, 0, 0);
        //--------------------------------------------------
        
        //draw terrain
        //--------------------------------------------------
        al_set_target_bitmap(terrain_bitmap);
        al_use_shader(sh_terrain_blending);
        al_set_shader_float("seed", world_seed);
        al_set_shader_float_vector("chunk_index", 2, t2, 1);
        al_set_shader_sampler("grass_tex", grass_bitmap, 1);
        al_set_shader_sampler("mossy_cobblestone_tex", mossy_cobblestone_bitmap, 2);
        al_draw_bitmap(bitmap_t, 0, 0, 0);
        //--------------------------------------------------
        //end of blening

        Render::SetViewportAsRenderTarget();
        al_use_shader(nullptr);
        al_draw_scaled_bitmap(terrain_bitmap, 0, 0, 512, 512, 512*4, 0, 512*4, 512*4, 0);

        
        
        //draw grass texture
        //--------------------------------------------------
        al_set_target_bitmap(grass_bitmap);
        al_use_shader(sh_grass);
        al_set_shader_float("seed", world_seed);
        float t3[2] = {0, -1};
        al_set_shader_float_vector("chunk_index", 2, t3, 1);
        al_draw_bitmap(bitmap_t, 0, 0, 0);
        //--------------------------------------------------

        //draw dirt texture
        //--------------------------------------------------
        al_set_target_bitmap(mossy_cobblestone_bitmap);
        al_use_shader(sh_dirt);
        al_set_shader_float("seed", world_seed);
        al_set_shader_float_vector("chunk_index", 2, t3, 1);
        al_draw_bitmap(bitmap_t, 0, 0, 0);
        //--------------------------------------------------
        
        //draw terrain
        //--------------------------------------------------
        al_set_target_bitmap(terrain_bitmap);
        al_use_shader(sh_terrain_blending);
        al_set_shader_float("seed", world_seed);
        al_set_shader_float_vector("chunk_index", 2, t3, 1);
        al_set_shader_sampler("grass_tex", grass_bitmap, 1);
        al_set_shader_sampler("mossy_cobblestone_tex", mossy_cobblestone_bitmap, 2);
        al_draw_bitmap(bitmap_t, 0, 0, 0);
        //--------------------------------------------------
        //end of blening

        Render::SetViewportAsRenderTarget();
        al_use_shader(nullptr);
        al_draw_scaled_bitmap(terrain_bitmap, 0, 0, 512, 512, 0, 512*4, 512*4, 512*4, 0);



        //draw grass texture
        //--------------------------------------------------
        al_set_target_bitmap(grass_bitmap);
        al_use_shader(sh_grass);
        al_set_shader_float("seed", world_seed);
        float t4[2] = {1, -1};
        al_set_shader_float_vector("chunk_index", 2, t4, 1);
        al_draw_bitmap(bitmap_t, 0, 0, 0);
        //--------------------------------------------------

        //draw dirt texture
        //--------------------------------------------------
        al_set_target_bitmap(mossy_cobblestone_bitmap);
        al_use_shader(sh_dirt);
        al_set_shader_float("seed", world_seed);
        al_set_shader_float_vector("chunk_index", 2, t4, 1);
        al_draw_bitmap(bitmap_t, 0, 0, 0);
        //--------------------------------------------------
        
        //draw terrain
        //--------------------------------------------------
        al_set_target_bitmap(terrain_bitmap);
        al_use_shader(sh_terrain_blending);
        al_set_shader_float("seed", world_seed);
        al_set_shader_float_vector("chunk_index", 2, t4, 1);
        al_set_shader_sampler("grass_tex", grass_bitmap, 1);
        al_set_shader_sampler("mossy_cobblestone_tex", mossy_cobblestone_bitmap, 2);
        al_draw_bitmap(bitmap_t, 0, 0, 0);
        //--------------------------------------------------
        //end of blening

        Render::SetViewportAsRenderTarget();
        al_use_shader(nullptr);
        al_draw_scaled_bitmap(terrain_bitmap, 0, 0, 512, 512, 512*4, 512*4, 512*4, 512*4, 0);
        
        // al_set_target_bitmap(result_bitmap);
        // al_use_shader(noise_shader);
        // al_set_shader_float("seed", 999999.0f);
        // float t2[2] = {1, 0};
        // al_set_shader_float_vector("chunk_index", 2, t2, 1);
        // al_draw_bitmap(result_bitmap, 0, 0, 0);
        // Render::SetViewportAsRenderTarget();
        // al_use_shader(nullptr);
        // al_draw_scaled_bitmap(result_bitmap, 0, 0, 512, 512, 512*4, 0, 512*4, 512*4, 0);
        // al_use_shader(terrain_shader);
        // al_set_shader_sampler("noise_texture", result_bitmap, 1);
        // al_draw_bitmap(result_bitmap, 0, 0, 0);
        // al_draw_scaled_bitmap(dirt_tex, 0, 0, 32, 32, 0, 0, 256, 256, 0);
        // Render::SetViewportAsRenderTarget();
        // al_use_shader(nullptr);
        // al_set_target_bitmap(result_bitmap);
        // al_draw_bitmap(result_bitmap, 0, 512, 0);
        // al_clear_to_color(al_map_rgb(0,0,0));
        // Render::SetViewportAsRenderTarget();
    }
};


#endif /* BEA9B3D9_2064_440F_B959_F0A8021F8D87 */
