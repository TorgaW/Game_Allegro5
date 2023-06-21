#ifndef CDE24679_5B01_4571_80CA_CB7786D36B25
#define CDE24679_5B01_4571_80CA_CB7786D36B25

#include "allegro5/allegro5.h"
#include <vector>
#include <string>
#include "../UI/Fonts/StaticFonts.h"

#define BC_MOUSE_LKEY 150 // left mouse button
#define BC_MOUSE_RKEY 151 // right mouse button
#define BC_MOUSE_MIDKEY 152 // middle mouse button

#define BC_MOUSE_AXES_X 0x0 //mouse x coordinate
#define BC_MOUSE_AXES_Y 0x1 //mouse y coordinate
#define BC_MOUSE_AXES_Z 0x2 //mouse wheel

#define BC_KEY_DOWN 0x3
#define BC_KEY_UP 0x2
#define BC_KEY_HOLD 0x1

struct IInputAction
{
    std::string ActionName;
    unsigned char Key;
    bool bUseShift;
    bool bUseAlt;
    bool bUseCtrl;
    uint8_t EventState;
    IInputAction(std::string name);
    IInputAction(std::string name, bool shift, bool alt, bool ctrl);
};

struct IMouseState
{
    float x, y, dx, dy, dz; //dz - mouse wheel scroll
};

struct IMouseInputAction
{
    std::string ActionName;
    uint8_t ActionType;
    IMouseState Mouse;
    bool bUseShift;
    bool bUseAlt;
    bool bUseCtrl;
    IMouseInputAction(std::string name, uint8_t action_type);
    IMouseInputAction(std::string name, uint8_t action_type, bool shift, bool alt, bool ctrl);
};


class InputManager
{
public:
    static InputManager &Get()
    {
        static InputManager instance;
        return instance;
    }

private:
    InputManager()
    {
        memset(Keys, 0, ALLEGRO_KEY_MAX);
        memset(KeyUpQueue, 0, ALLEGRO_KEY_MAX);
    };

public:
    InputManager(InputManager const &) = delete;
    void operator=(InputManager const &) = delete;

private:
    unsigned char Keys[ALLEGRO_KEY_MAX];
    bool KeyUpQueue[ALLEGRO_KEY_MAX];
    std::vector<IInputAction> InputActions;
    std::vector<IMouseInputAction> MouseInputActions;

    float MouseSensitivity = 0.01f;
    IMouseState Mouse;
public:
    void UpdateKeyDown(uint8_t keycode);
    void UpdateKeyReleased(uint8_t keycode);
    void UpdateKeysInRender();

    void CreateInputAction(std::string name, unsigned char key);
    void CreateMouseInputAction(std::string name, uint8_t action_type);
    inline size_t GetNumberOfActions() { return InputActions.size(); }
    inline size_t GetNumberOfMouseActions() { return MouseInputActions.size(); }
    inline IInputAction GetAction(size_t index) { return InputActions[index]; }
    inline IMouseInputAction GetMouseAction(size_t index) { return MouseInputActions[index]; }
    inline int GetActionState(std::string name)
    {
        for (size_t i = 0; i < InputActions.size(); i++)
        {
            if (InputActions[i].ActionName == name)
                return InputActions[i].EventState;
        }
        return -1;
    }
    inline void ResetMouseDelta()
    {
        Mouse.dx = 0.0f;
        Mouse.dy = 0.0f;
        Mouse.dz = 0.0f;
    }
    inline IMouseState GetMouseActionState(std::string name)
    {
        for (size_t i = 0; i < MouseInputActions.size(); i++)
            if(MouseInputActions[i].ActionName == name) return MouseInputActions[i].Mouse;
        return IMouseState();
    }

    void UpdateMouseState(ALLEGRO_MOUSE_EVENT, ALLEGRO_DISPLAY*);
    void UpdateInputActions();
    void UpdateMouseActions();
};

#endif /* CDE24679_5B01_4571_80CA_CB7786D36B25 */
