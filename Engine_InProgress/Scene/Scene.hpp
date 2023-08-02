#ifndef C1E09A79_990B_4A63_96D2_D8E857A2EF2F
#define C1E09A79_990B_4A63_96D2_D8E857A2EF2F

// #include "../STD_DefaultInclude.hpp"
#include "../SceneObject/SceneObject.hpp"

class Scene
{
private:
    uint64_t scene_id {0};
    std::string scene_name {""};
    std::vector<Ref<SceneObject>> scene_vector_buffer {};

public:
    inline std::string GetName() { return scene_name; };
    inline uint64_t GetId() { return scene_id; };
    inline std::vector<Ref<SceneObject>> *GetBuffer() { return &scene_vector_buffer; };

public:
    Scene(uint64_t id, std::string name) : 
    scene_id(id), scene_name(name)
    {};
    ~Scene(){};

public:
    template<class T>
    void AddSceneObject(Ref<T> object)
    {   
        if(object.IsValidStrict())
        {
            scene_vector_buffer.push_back(object);
            object->CallBegin();
        }
    };
};


#endif /* C1E09A79_990B_4A63_96D2_D8E857A2EF2F */
