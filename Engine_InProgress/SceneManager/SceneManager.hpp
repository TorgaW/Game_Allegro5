#ifndef B0EB5C86_0615_4316_A089_D0AA42406677
#define B0EB5C86_0615_4316_A089_D0AA42406677

#include "../Scene/Scene.hpp"
#include <type_traits>

class SceneManager
{
public:
    SceneManager(){};
    ~SceneManager(){};

    bool AddObjectToScene(Scene *_scene, ObjRef<SceneObject> _obj);

    template<class T>
    static ObjRef<T> CreateObject(std::string name, std::string base_class)
    {
        static_assert(std::is_base_of<SceneObject, T>::value, "Scene manager error: must be SceneObject at least.");
        return ObjectManager::CreateObject<T>(name, base_class);
    }

    template<class T>
    static void DestroyObject(Scene *_scene, ObjRef<SceneObject> _candidate)
    {
        if(_scene == nullptr) return;
        
        auto p = std::find(_scene->scene_object_buffer.begin(), _scene->scene_object_buffer.end(), _candidate);
    }
};

#endif /* B0EB5C86_0615_4316_A089_D0AA42406677 */
