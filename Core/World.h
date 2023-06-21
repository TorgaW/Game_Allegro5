#ifndef FC9DC838_281C_49D6_9F9C_0B27E0EB9003
#define FC9DC838_281C_49D6_9F9C_0B27E0EB9003

#include "../SceneObjects/Scene/AScene.h"
#include "../SceneObjects/SceneObject/SceneObject.h"
#include "UI/Viewport.h"

class AScene;
class Viewport;
class Profiler;

class World
{
private:
    AScene *WorldScene;
public:
    World();
    ~World();

    void AddToWorld(AObject *obj);
    void AddToWorld(ASceneObject *obj);
    void RemoveFromWorld(AObject *obj);
    void RemoveFromWorld(ASceneObject *obj);

    void UpdateScene();
    AScene *GetScene();

    Viewport *GetViewport();
    Profiler *GetProfiler();
};


#endif /* FC9DC838_281C_49D6_9F9C_0B27E0EB9003 */
