#ifndef B1CBA0EA_5BE5_42CC_9CEC_6EF223767600
#define B1CBA0EA_5BE5_42CC_9CEC_6EF223767600

#include "../ObjectManager/ObjectManager.hpp"
#include "../Scene/Scene.hpp"
#include "../Render/Render.hpp"
#include <type_traits>

class SceneManager
{
private:
    static inline Scene* current_scene {nullptr};
    static inline uint64_t last_scene_id {1};
    static inline std::vector<Scene*> scenes_buffer {};
public:
    SceneManager(){};
    ~SceneManager(){};

public:
    static void Init();

    static void UpdateSceneObjects();

    static inline Scene* GetCurrentScene() { return current_scene; };

    template<class T>
    static Ref<T> CreateSceneObject(const std::string& name, const std::string& obj_class, bool add_to_scene = true)
    {
        static_assert(std::is_base_of<SceneObject, T>::value, "Scene manager creation error: must be SceneObject at least.");
        auto t = ObjectManager::CreateObject<T>(name, obj_class);
        if(add_to_scene)
        {
            current_scene->AddSceneObject(t);
            t->is_on_scene = true;
        }
        return t;
    };

    template<class T>
    static Ref<T> CopySceneObject(Ref<T> candidate, std::string name)
    {
        static_assert(std::is_base_of<SceneObject, T>::value, "Scene manager copy error: must be SceneObject at least.");
        auto t = ObjectManager::CopyObject<T>(candidate, name);
        current_scene->AddSceneObject(t);
        return t;
    }

    template<class T>
    static bool DestroySceneObject(Ref<T> candidate)
    {
        static_assert(std::is_base_of<SceneObject, T>::value, "Scene manager destroy error: must be SceneObject at least.");
        if(candidate.IsValidStrict() && candidate->is_on_scene == true) 
            return false;
        bool t = ObjectManager::DestroyObject<T>(candidate);
        return t;
    }

    static inline void CreateGameScene(const std::string& name)
    {
        scenes_buffer.push_back(new Scene(last_scene_id, name));
        last_scene_id++;
    };

    static inline void ChangeGameScene(const std::string& to_name)
    {
        auto r = std::find_if(scenes_buffer.begin(), scenes_buffer.end(), 
        [to_name](Scene* s)
        {
            return s->GetName() == to_name;
        });
        if(r != scenes_buffer.end())
        {
            current_scene = (*r);
        }
    };

    //TODO
    static void SetObjectHiddenInScene(){};
};


#endif /* B1CBA0EA_5BE5_42CC_9CEC_6EF223767600 */
