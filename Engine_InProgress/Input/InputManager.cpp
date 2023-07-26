#include "InputManager.hpp"

void InputManager::CreateKeyInputAction(std::string act_name, unsigned char act_key, /*KeyboardEventType event_type,*/ bool ui_action)
{
    if(ui_action)
    {
        ui_input_key_actions[act_name] = KeyboardInputAction(act_name, act_key, /*event_type,*/ false, false, false);
    }
    else
    {
        input_key_actions[act_name] = KeyboardInputAction(act_name, act_key, /*event_type,*/ false, false, false);
    }
}

void InputManager::CreateKeyInputAction(std::string act_name, unsigned char act_key, /*KeyboardEventType event_type,*/ bool use_shift, bool use_ctrl, bool use_alt, bool ui_action)
{
    if(ui_action)
    {
        ui_input_key_actions[act_name] = KeyboardInputAction(act_name, act_key, /*event_type,*/ use_shift, use_ctrl, use_alt);
    }
    else
    {
        input_key_actions[act_name] = KeyboardInputAction(act_name, act_key, /*event_type,*/ use_shift, use_ctrl, use_alt);
    }
}

void InputManager::CreateMouseInputAction(std::string act_name, unsigned char act_key, bool ui_action)
{
    if(ui_action)
    {
        ui_input_key_actions[act_name] = KeyboardInputAction(act_name, act_key, /*event_type,*/ false, false, false);
    }
    else
    {
        input_key_actions[act_name] = KeyboardInputAction(act_name, act_key, /*event_type,*/ false, false, false);
    }
}

void InputManager::CreateMouseInputAction(std::string act_name, unsigned char act_key, bool use_shift, bool use_ctrl, bool use_alt, bool ui_action)
{

}

void InputManager::UpdateKeyActions()
{
    if(ui_input_enabled)
    {
        for (auto const& [key, value] : ui_input_key_actions)
        {
            ui_input_key_actions[key].action_state = input_keys[value.action_key];
        }
    }
    else
    {
        for (auto const& [key, value] : input_key_actions)
        {
            input_key_actions[key].action_state = input_keys[value.action_key];
        }
    }
}

void InputManager::UpdateMouseState(ALLEGRO_MOUSE_EVENT mouse, ALLEGRO_DISPLAY *display)
{
    input_mouse_state.delta_position.x = -(input_mouse_state.position.x - mouse.x);
    input_mouse_state.delta_position.y = -(input_mouse_state.position.y - mouse.y);
    input_mouse_state.position.x = mouse.x;
    input_mouse_state.position.y = mouse.y;
    input_mouse_state.wheel = mouse.dz;
    // std::stringstream ss;
    // ss << "x: " << input_mouse_state.delta_position.x << "y: " << input_mouse_state.delta_position.y << "z: " << input_mouse_state.wheel;
    // EngineDebugger::PrintDebugMessage(ss.str(), al_map_rgb(255, 255, 0), 0.1f);
}
