#ifndef CA90DD33_173E_4FD2_82CB_48C9F491E0AE
#define CA90DD33_173E_4FD2_82CB_48C9F491E0AE

#include "SceneObject/SceneObject.hpp"

class Scene
{
public:
    std::string scene_name {""};
    std::vector<ObjRef<SceneObject>> scene_object_buffer {};
    size_t scene_max_buffer_size {0};
public:
    Scene(std::string name):scene_name(name)
    {
        scene_object_buffer.reserve(500);
    };
    Scene(std::string name, size_t max_buffer_size):
    scene_name(name), scene_max_buffer_size(max_buffer_size)
    {
        scene_object_buffer.reserve(max_buffer_size);
    };
    ~Scene(){};
};


#endif /* CA90DD33_173E_4FD2_82CB_48C9F491E0AE */
