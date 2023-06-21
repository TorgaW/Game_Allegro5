#ifndef A56D82E9_547D_48B4_B43D_0BF1ADB0B7E3
#define A56D82E9_547D_48B4_B43D_0BF1ADB0B7E3
#include <allegro5/allegro5.h>
#include <vector>
#include "../UI/Viewport.h"
#include "../Main/Game.h"
#include "../../SceneObjects/SceneObject/SceneObject.h"
#include "../ShaderManager/ShaderManager.h"

class Viewport;
// class ASceneObject;

class Render
{
private:
    double DeltaTime;
    double NewFrameTime;
    double PrevFrameTime;
    ALLEGRO_TRANSFORM SceneTransform;
    Transform2D CameraTransform;
    std::vector<ASceneObject*> TBuffer;
    ShaderManager *Shaders;
private:
    Render(){};
public:
    static Render &Get()
    {
        static Render instance;
        return instance;
    }
    Render(Render const &) = delete;
    void operator=(Render const &) = delete;
    
    inline void UpdateDeltaTime()
    {
        NewFrameTime = al_get_time();
        DeltaTime = NewFrameTime - PrevFrameTime;
        PrevFrameTime = NewFrameTime;
    }
    inline void SetViewportAsRenderTarget()
    {
        al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
    }
    int GetDisplayWidth();
    int GetDisplayHeight();
    Rectangle2D GetDisplayBoundsInWorldCoordinates();
    inline double GetDeltaTime()
    {
        return DeltaTime;
    }
    inline ALLEGRO_TRANSFORM *GetSceneTransform()
    {
        return &SceneTransform;
    }
    inline void SetSceneTransform(ALLEGRO_TRANSFORM* new_transform)
    {
        al_copy_transform(&SceneTransform, new_transform);
    }
    inline void SetCameraTransform(Transform2D new_transform)
    {
        CameraTransform = new_transform;
    }
    void DrawScreen(std::vector<ASceneObject*> *objects, Viewport *viewport);
    inline ShaderManager *GetShaders() { return Shaders; };
    inline void SetShaders(ShaderManager* sm) { Shaders = sm; };
};


#endif /* A56D82E9_547D_48B4_B43D_0BF1ADB0B7E3 */
