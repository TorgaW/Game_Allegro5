#ifndef CA90DD33_173E_4FD2_82CB_48C9F491E0AE
#define CA90DD33_173E_4FD2_82CB_48C9F491E0AE

#include "SceneObject/SceneObject.hpp"

class Scene
{
public:
    std::string scene_name {""};
    std::map<std::string, std::vector<Ref<SceneObject>>> scene_map_object_buffer {};
    std::vector<Ref<SceneObject>> scene_obj_buffer {};
    // size_t scene_max_buffer_size {0};
public:
    Scene(std::string name):scene_name(name) 
    {};
    // Scene(std::string name, size_t max_buffer_size):
    // scene_name(name), scene_max_buffer_size(max_buffer_size)
    // {};
    ~Scene(){};
};


#endif /* CA90DD33_173E_4FD2_82CB_48C9F491E0AE */
