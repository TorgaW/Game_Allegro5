#ifndef B0EB5C86_0615_4316_A089_D0AA42406677
#define B0EB5C86_0615_4316_A089_D0AA42406677

#include "../Scene/Scene.hpp"
#include <type_traits>

//condition for fast search object
enum FindObjectMode
{
    Name,
    ObjClass,
    NameAndClass,
    NameOrClass
};

class SceneManager
{
private:
    static inline Scene *mng_target_scene {nullptr};

public:
    SceneManager(){};
    ~SceneManager(){};

    static inline void SetTargetScene(Scene *_scene)
    {
        if(_scene != nullptr)
            mng_target_scene = _scene;
    };

    static inline Scene *GetTargetScene() { return mng_target_scene; };

    // bool AddObjectToScene(Scene *_scene, Ref<SceneObject> _obj);

    // bool AddObjectToScene(Ref<SceneObject> _obj);

    //creates scene object
    template<class T>
    static Ref<T> CreateObject(const std::string& name, const std::string& _obj_class)
    {
        static_assert(std::is_base_of<SceneObject, T>::value, "Scene manager error: must be SceneObject at least.");
        return ObjectManager::CreateObject<T>(name, _obj_class);
    }

    template<class T>
    static Ref<T> CopyObject(const Ref<T> &candidate, const std::string &name)
    {
        static_assert(std::is_base_of<SceneObject, T>::value, "Scene manager error: must be SceneObject at least.");
        return ObjectManager::CopyObject<T>(candidate, name);
    }

    template<class T>
    static bool AddObjectToScene(Ref<T> _object)
    {
        if(!_object.IsValidStrict()) return false;
        mng_target_scene->scene_map_object_buffer[_object->GetClass()].push_back(static_cast<Ref<SceneObject>>(_object));
        return true;
    }

    template<class T>
    static Ref<T> FindObject(FindObjectMode mode, std::string name, std::string obj_class)
    {
        for (auto const& [key, val] : mng_target_scene->scene_map_object_buffer)
        {
            // switch (mode)
            // {
            // case FindObjectMode::Name:
            //     auto p = std::find_if(val.begin(), val.end(), 
            //     [name](Ref<SceneObject> l)
            //     {
            //         return l->GetName() == name;
            //     });
            //     if(p != val.end()) return (*p);
            //     break;
            
            // // case FindObjectMode::ObjClass:

            // // default:
            //     // break;
            // }
        }
        return Ref<T>();
    }

    
    // template<class T>
    // static bool AddToScene(Ref<Object>)
    // {
    //     return true;
    // }

    //copy scene object

    //destroys scene object from memory
    template<class T>
    static bool DestroyObject(Scene *_scene, Ref<T> _candidate)
    {
        if(_scene == nullptr) return false;
        // auto p = static_cast<Ref<SceneObject>>(_candidate);
        
        // _scene->scene_map_object_buffer.erase(std::remove_if(_scene->scene_map_object_buffer.begin(), _scene->scene_map_object_buffer.end(), 
        // [_candidate](const Ref<SceneObject>& p)
        // {
        //     return _candidate == p;
        // }), _scene->scene_map_object_buffer.end());

        return ObjectManager::DestroyObject(_candidate);
    }
    
};

#endif /* B0EB5C86_0615_4316_A089_D0AA42406677 */
