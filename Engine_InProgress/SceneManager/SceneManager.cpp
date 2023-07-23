#include "SceneManager.hpp"

bool SceneManager::AddObjectToScene(Scene *_scene, Ref<SceneObject> _obj)
{
    if(_scene == nullptr) return false;

    if(_scene->scene_map_object_buffer.size() == _scene->scene_max_buffer_size) return false;

    auto p = std::find(_scene->scene_map_object_buffer.begin(), _scene->scene_map_object_buffer.end(), _obj);
    
    if(p != _scene->scene_map_object_buffer.end()) return false;

    _scene->scene_map_object_buffer.emplace_back(_obj);

    return true;
}