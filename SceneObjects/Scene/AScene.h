#ifndef B52EAACF_233B_490A_B4C1_8B02BDF12213
#define B52EAACF_233B_490A_B4C1_8B02BDF12213

#include "../SceneObject/SceneObject.h"
#include "../../Core/ObjectManager/ObjectManager.h"
#include "../Camera/Camera.h"
#include "../../Core/UI/Viewport.h"

#include <vector>

class Camera;
class Viewport;
class ASceneObject;

class AScene
{
private:
    std::vector<ASceneObject*> GraphicsBuffer;
    std::vector<AObject*> TickBuffer;
    Camera *MainCamera;
    Viewport *UIViewPort;
public:
    AScene();
    ~AScene();

    void AddObject(AObject *obj);
    void AddObject(ASceneObject *obj);
    void RemoveObject(AObject *obj);
    void RemoveObject(ASceneObject *obj);

    void SetMainCamera(Camera *cam);
    Camera *GetMainCamera();

    inline void ChangeViewport(Viewport *new_viewport)
    {
        UIViewPort = new_viewport;
    }

    inline Viewport *GetViewport()
    {
        return UIViewPort;
    }

    void UpdateScene();
};


#endif /* B52EAACF_233B_490A_B4C1_8B02BDF12213 */
