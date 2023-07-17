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

    //creates scene object
    template<class T>
    static ObjRef<T> CreateObject(const std::string& name, const std::string& base_class)
    {
        static_assert(std::is_base_of<SceneObject, T>::value, "Scene manager error: must be SceneObject at least.");
        return ObjectManager::CreateObject<T>(name, base_class);
    }

    //copies scene object
    template<class T>
    static ObjRef<T> CopyObject(const ObjRef<T> &candidate, const std::string &name)
    {
        static_assert(std::is_base_of<SceneObject, T>::value, "Scene manager error: must be SceneObject at least.");
        return ObjectManager::CopyObject<T>(candidate, name);
    }

    //destroys scene object from memory
    static bool DestroyObject(Scene *_scene, const ObjRef<SceneObject>& _candidate)
    {
        if(_scene == nullptr) return false;
        
        _scene->scene_object_buffer.erase(std::remove_if(_scene->scene_object_buffer.begin(), _scene->scene_object_buffer.end(), 
        [_candidate](const ObjRef<SceneObject>& p)
        {
            return _candidate == p;
        }), _scene->scene_object_buffer.end());

        return ObjectManager::DestroyObject(_candidate);
    }

    
};

#endif /* B0EB5C86_0615_4316_A089_D0AA42406677 */
