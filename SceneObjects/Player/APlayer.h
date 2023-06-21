#ifndef B1ECA89D_105D_4E06_AE3B_F35103A57D10
#define B1ECA89D_105D_4E06_AE3B_F35103A57D10

// #include "../../Core/CoreInclude.h"
// #include "../../Components/ComponentsInclude.h"
#include "../SceneObject/SceneObject.h"
#include "../../Components/InputComponent/InputComponent.h"
#include "../../Components/AnimationComponent/AnimationComponent.h"
#include "../../Core/Main/Game.h"
#include <allegro5/allegro5.h>
#include <sstream>

// class ASceneObject;
class Camera;

class APlayer : public ASceneObject
{
private:
    Vector2D TargetPosition = {0, 0};
    AnimationComponent AnimComp;
    IInputComponent<APlayer> Input;

    Vector2D Direction = {0, 0};
    Camera *PlayerCamera = nullptr;
    float PlayerSpeed = 2000.0f;
public:
    APlayer(uint32_t id, uint64_t timestamp, std::string name, std::string static_class_name);
    ~APlayer();

    virtual void Begin();
    virtual void GTick(float delta);
    virtual void Tick(float delta);
    virtual void End();

    inline bool SetPlayerCamera(Camera *c)
    {
        if(c == nullptr) return false;
        PlayerCamera = c;
        return true;
    };
    inline Camera *GetPlayerCamera() { return PlayerCamera; };

private:
    void SetDirectionForward();
    void SetDirectionBackward();
    void SetDirectionRight();
    void SetDirectionLeft();

    void ResetDirectionY();
    void ResetDirectionX();


};


#endif /* B1ECA89D_105D_4E06_AE3B_F35103A57D10 */
