#include "InputManager.hpp"

void InputManager::CreateKeyboardInputAction(std::string act_name, unsigned char act_key, /*KeyboardEventType event_type,*/ bool ui_action)
{
    if(ui_action)
    {
        ui_input_keyboard_actions[act_name] = KeyboardInputAction(act_name, act_key, /*event_type,*/ false, false, false);
    }
    else
    {
        input_keyboard_actions[act_name] = KeyboardInputAction(act_name, act_key, /*event_type,*/ false, false, false);
    }
}

void InputManager::CreateKeyboardInputAction(std::string act_name, unsigned char act_key, /*KeyboardEventType event_type,*/ bool use_shift, bool use_ctrl, bool use_alt, bool ui_action)
{
    if(ui_action)
    {
        ui_input_keyboard_actions[act_name] = KeyboardInputAction(act_name, act_key, /*event_type,*/ use_shift, use_ctrl, use_alt);
    }
    else
    {
        input_keyboard_actions[act_name] = KeyboardInputAction(act_name, act_key, /*event_type,*/ use_shift, use_ctrl, use_alt);
    }
}

void InputManager::UpdateKeyboardActions()
{
    if(ui_input_enabled)
    {
        for (auto const& [key, value] : ui_input_keyboard_actions)
        {
            ui_input_keyboard_actions[key].action_state = input_keyboard_keys[value.action_key];
        }
    }
    else
    {
        for (auto const& [key, value] : input_keyboard_actions)
        {
            input_keyboard_actions[key].action_state = input_keyboard_keys[value.action_key];
        }
    }
}
