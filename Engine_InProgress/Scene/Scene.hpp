#ifndef C52C8DAF_16D7_49B6_9971_2110AEC1596E
#define C52C8DAF_16D7_49B6_9971_2110AEC1596E

#include "../STD_DefaultInclude.hpp"
#include "../SceneObject/SceneObject.hpp"

class Scene
{
private:
    std::vector<ObjRef<SceneObject>> scene_objects {};
public:
    Scene();
    ~Scene(){};

    //add object to the scene
    void AddToScene(ObjRef<SceneObject> obj);

    //remove object from the scene
    void RemoveFromScene(ObjRef<SceneObject> obj);
};


#endif /* C52C8DAF_16D7_49B6_9971_2110AEC1596E */
