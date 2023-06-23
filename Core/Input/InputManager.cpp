#include "InputManager.h"

IInputAction::IInputAction(std::string name)
{
    ActionName = name;
    EventState = 0x0;
}

IInputAction::IInputAction(std::string name, bool shift, bool alt, bool ctrl)
{
    ActionName = name;
    bUseShift = shift;
    bUseAlt = alt;
    bUseCtrl = ctrl;
    EventState = 0x0;
}

void InputManager::UpdateKeyDown(uint8_t keycode)
{
    Keys[keycode] = BC_KEY_DOWN;
}

void InputManager::UpdateKeyReleased(uint8_t keycode)
{
    KeyUpQueue[keycode] = true;
}

void InputManager::UpdateKeysInRender()
{
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
    {
        if(KeyUpQueue[i])
        {
            Keys[i] = BC_KEY_UP;
            KeyUpQueue[i] = false;
        }
        else
            Keys[i] &= BC_KEY_HOLD;
    }
}

void InputManager::CreateInputAction(std::string name, unsigned char key, bool for_ui)
{
    if(for_ui)
    {
        for (size_t i = 0; i < UIInputActions.size(); i++)
            if(UIInputActions[i].ActionName == name) return;
        IInputAction t(name);
        t.Key = key;
        UIInputActions.push_back(t);
    }
    else
    {
        for (size_t i = 0; i < InputActions.size(); i++)
            if(InputActions[i].ActionName == name) return;
        IInputAction t(name);
        t.Key = key;
        InputActions.push_back(t);
    }
}

void InputManager::CreateMouseInputAction(std::string name, uint8_t action_type, bool for_ui)
{
    if(for_ui)
    {
        for (size_t i = 0; i < UIMouseInputActions.size(); i++)
            if(UIMouseInputActions[i].ActionName == name) return;
    
        IMouseInputAction t(name, action_type);
        UIMouseInputActions.push_back(t);
    }
    else
    {
        for (size_t i = 0; i < MouseInputActions.size(); i++)
            if(MouseInputActions[i].ActionName == name) return;
    
        IMouseInputAction t(name, action_type);
        MouseInputActions.push_back(t);
    }
}

// void InputManager::CreateMouseInputAction(std::string name, unsigned char mouse_key)
// {
//     for (size_t i = 0; i < MouseInputActions.size(); i++)
//         if(MouseInputActions[i].ActionName == name) return;
//     IMouseInputAction t(name);
//     t.Key = mouse_key;
//     MouseInputActions.push_back(t);
// }

void InputManager::UpdateInputActions()
{
    if(UIInputEnabled)
    {
        for (size_t i = 0; i < UIInputActions.size(); i++)
        {
            UIInputActions[i].EventState = Keys[UIInputActions[i].Key];
        }
    }
    else
    {
        for (size_t i = 0; i < InputActions.size(); i++)
        {
            InputActions[i].EventState = Keys[InputActions[i].Key];
        }
    }
    // al_draw_textf(StaticFonts::Get().GetUbuntu12R(), al_map_rgb(255, 255, 255), 0, 100, 0, "{x: %f; y: %f; dx: %f; dy: %f}", Mouse.x, Mouse.y, Mouse.dx, Mouse.dy);
}

void InputManager::UpdateMouseActions()
{
    if(UIInputEnabled)
    {
        for (size_t i = 0; i < UIMouseInputActions.size(); i++)
        {
            UIMouseInputActions[i].Mouse = Mouse;
        }
    }
    else
    {
        for (size_t i = 0; i < MouseInputActions.size(); i++)
        {
            MouseInputActions[i].Mouse = Mouse;
        }
    }
    
}

void InputManager::UpdateMouseState(ALLEGRO_MOUSE_EVENT mouse, ALLEGRO_DISPLAY *display)
{
    Mouse.dx += mouse.dx * MouseSensitivity;
    Mouse.dy += mouse.dy * MouseSensitivity;
    Mouse.x += mouse.dx * MouseSensitivity;
    Mouse.y += mouse.dy * MouseSensitivity;
    Mouse.dz += mouse.dz;

    if(!UIInputEnabled) al_set_mouse_xy(display, al_get_display_width(display)/2, al_get_display_height(display)/2);
}

IMouseInputAction::IMouseInputAction(std::string name, uint8_t action_type)
{
    ActionName = name;
    ActionType = action_type;
}

IMouseInputAction::IMouseInputAction(std::string name, uint8_t action_type, bool shift, bool alt, bool ctrl)
{
    ActionName = name;
    ActionType = action_type;
    bUseShift = shift;
    bUseCtrl = ctrl;
    bUseAlt = alt;
}
