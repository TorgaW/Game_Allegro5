#include "ShaderManager.hpp"

ShaderManager::~ShaderManager()
{
    for (auto const& x : built_shaders)
    {
        al_destroy_shader(x.second);
    }
}

bool ShaderManager::LoadShader(std::string name, std::string path, ALLEGRO_SHADER_PLATFORM allegro_shader_platform, ALLEGRO_SHADER_TYPE allgero_shader_type)
{
    ALLEGRO_SHADER *t = al_create_shader(allegro_shader_platform);
    if(t == nullptr) return false;
    bool r = al_attach_shader_source_file(t, ALLEGRO_VERTEX_SHADER, "Resources/Shaders/Vertex.glsl");
    // std::cout << al_get_default_shader_source(allegro_shader_platform, ALLEGRO_VERTEX_SHADER) << "|||||\n";
    if(!r)
    {
        std::cout << al_get_shader_log(t) << "\n";
        return false;
    }
    r = al_attach_shader_source_file(t, allgero_shader_type, path.c_str());
    // r = al_attach_shader_source(t, ALLEGRO_PIXEL_SHADER, al_get_default_shader_source(allegro_shader_platform, ALLEGRO_PIXEL_SHADER));
    if(!r)
    {
        std::cout << al_get_shader_log(t) << "\n";
        return false;
    }
    r = al_build_shader(t);
    if(!r)
    {
        std::cout << al_get_shader_log(t) << "\n";
        return false;
    }
    built_shaders[name] = t;
    return true;
}

ALLEGRO_SHADER *ShaderManager::GetShader(std::string name)
{
    return built_shaders[name];
}
