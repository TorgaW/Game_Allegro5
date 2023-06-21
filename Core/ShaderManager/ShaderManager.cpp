#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
    BuiltShaders = {};
}

ShaderManager::~ShaderManager()
{
    for (size_t i = 0; i < BuiltShaders.size(); i++)
    {
        al_destroy_shader(BuiltShaders[i].second);
    }
}

bool ShaderManager::LoadShader(std::string name, std::string path, ALLEGRO_SHADER_PLATFORM allegro_shader_platform, ALLEGRO_SHADER_TYPE allgero_shader_type)
{
    ALLEGRO_SHADER *t = al_create_shader(allegro_shader_platform);
    if(t == nullptr) return false;
    bool r = al_attach_shader_source_file(t, allgero_shader_type, path.c_str());
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
    BuiltShaders.push_back(std::pair<std::string, ALLEGRO_SHADER*>(name, t));
    return true;
}

ALLEGRO_SHADER *ShaderManager::GetShader(std::string name)
{
    for (size_t i = 0; i < BuiltShaders.size(); i++)
    {
        if(BuiltShaders[i].first == name) return BuiltShaders[i].second;
    }
    return nullptr;
}
