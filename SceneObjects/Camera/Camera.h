#ifndef C39EE2EF_8756_4578_BF9A_400AE240BB51
#define C39EE2EF_8756_4578_BF9A_400AE240BB51

#include "allegro5/allegro_primitives.h"
#include "../../Core/Defines/Defines.h"
#include "../../Core/Render/Render.h"
#include "../../Components/InputComponent/InputComponent.h"
#include "../../Core/UI/Fonts/StaticFonts.h"
#include "../../Core/Main/Game.h"
#include "../../Core/Math/Vector/VectorMath.h"
#include <sstream>

class Camera
{
private:
    Transform2D Transform;
    Vector2D TargetPosition;
    Vector2D TargetZoom;
    IInputComponent<Camera> Input;
    ALLEGRO_TRANSFORM CameraTransform;

    Vector2D Direction;
    ASceneObject *Parent;
private:
    void Zoom(float dz);

public:
    Camera();
    void UpdateCameraPosition(Vector2D newPos);
    void Tick(float delta);
    inline Vector2D GetPosition() { return Transform.Position; };
    inline bool SetParent(ASceneObject *p) { 
        if(p != nullptr)
        {
            Parent = p;
            return true;
        }
        return false;
    };
    inline ASceneObject *GetParent() { return Parent; };
};

#endif /* C39EE2EF_8756_4578_BF9A_400AE240BB51 */
