#ifndef D0A3E47C_DF70_492A_9E22_71E1EFB91614
#define D0A3E47C_DF70_492A_9E22_71E1EFB91614

#include "../InputManager.hpp"

template<class T>
struct InputComponentKeyboardAction
{
    std::string action_name;
    T* object_ptr;
    void(T::*action_function)();
    int key_event_type;
    InputComponentKeyboardAction(std::string name, int eventType, T* obj, void(T::*fn)())
    {
        object_ptr = obj;
        action_name = name;
        action_function = fn;
        key_event_type = eventType;
    }
};

// template<class T>
// struct InputComponentMouseAction
// {
//     std::string action_name;
//     T* object_ptr;
//     void(T::*action_function)(float);
//     uint8_t EventType;
//     InputComponentMouseAction(std::string name, uint8_t eventType, T* obj, void(T::*fn)(float))
//     {
//         object_ptr = obj;
//         action_name = name;
//         action_function = fn;
//         EventType = eventType;
//     }
// };

template<class T>
class InputComponent
{
private:
    std::vector<InputComponentKeyboardAction<T>> keyboard_action_bindings;
    // std::vector<InputComponentMouseAction<T>> mouse_action_bindings;
public:
    void AddKeyboardActionBinding(std::string name, KeyboardEventType keyEventType, T* object, void(T::*func)())
    {
        if(InputManager::KeyboardActionExists(name))
        {
            keyboard_action_bindings.push_back(InputComponentKeyboardAction<T>(name, keyEventType, object, func));
        }
    }
    // void AddMouseActionBinding(std::string name, uint8_t eventType, T* object, void(T::*func)(float))
    // {
    //     for (size_t i = 0; i < InputManager::Get().GetNumberOfMouseActions(); i++)
    //     {
    //         if(InputManager::Get().GetMouseAction(i).ActionName == name)
    //             mouse_action_bindings.push_back(InputComponentMouseAction<T>(name, eventType, object, func));
    //     }
    // }
    void RemoveActionBinding(std::string name)
    {
        for (size_t i = 0; i < keyboard_action_bindings.size(); i++)
        {
            if(keyboard_action_bindings[i].action_name == name)
            {
                keyboard_action_bindings.erase(keyboard_action_bindings.begin() + i);
                return;
            }
        }
    }
    // void RemoveMouseActionBinding(std::string name)
    // {
    //     for (size_t i = 0; i < mouse_action_bindings.size(); i++)
    //     {
    //         if(mouse_action_bindings[i].action_name == name)
    //         {
    //             mouse_action_bindings.erase(mouse_action_bindings.begin() + i);
    //             return;
    //         }
    //     }
    // }
    void ListenToInput()
    {
        for (size_t i = 0; i < keyboard_action_bindings.size(); i++)
        {
            int tstate = InputManager::GetKeyboardActionState(keyboard_action_bindings[i].action_name);
            if(tstate > 0)
            {
                if((tstate == BC_KEY_DOWN && keyboard_action_bindings[i].key_event_type == BC_KEY_HOLD) || tstate == keyboard_action_bindings[i].key_event_type)
                    (keyboard_action_bindings[i].object_ptr->*(keyboard_action_bindings[i].action_function))();
            }
        }
        // for (size_t i = 0; i < mouse_action_bindings.size(); i++)
        // {
        //     IMouseState tmouse = InputManager::Get().GetMouseActionState(mouse_action_bindings[i].action_name);
        //     if(mouse_action_bindings[i].EventType == BC_MOUSE_AXES_X)
        //         (mouse_action_bindings[i].object_ptr->*(mouse_action_bindings[i].action_function))(tmouse.dx);
        //     else if(mouse_action_bindings[i].EventType == BC_MOUSE_AXES_Y)
        //         (mouse_action_bindings[i].object_ptr->*(mouse_action_bindings[i].action_function))(tmouse.dy);
        //     else if(mouse_action_bindings[i].EventType == BC_MOUSE_AXES_Z)
        //         (mouse_action_bindings[i].object_ptr->*(mouse_action_bindings[i].action_function))(tmouse.dz);
        // }
        
    }
};

#endif /* D0A3E47C_DF70_492A_9E22_71E1EFB91614 */
