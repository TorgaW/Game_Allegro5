#ifndef B77A1BA5_6AE4_4C87_82C0_638A325673FE
#define B77A1BA5_6AE4_4C87_82C0_638A325673FE

#include <vector>
#include <string>
#include "../../Core/Input/InputManager.h"

template<class T>
struct IInputComponentAction
{
    std::string ActName;
    T* Object;
    void(T::*Func)();
    int KeyEventType;
    IInputComponentAction(std::string name, int eventType, T* obj, void(T::*fn)())
    {
        Object = obj;
        ActName = name;
        Func = fn;
        KeyEventType = eventType;
    }
};

template<class T>
struct IInputComponentMouseAction
{
    std::string ActName;
    T* Object;
    void(T::*Func)(float);
    uint8_t EventType;
    IInputComponentMouseAction(std::string name, uint8_t eventType, T* obj, void(T::*fn)(float))
    {
        Object = obj;
        ActName = name;
        Func = fn;
        EventType = eventType;
    }
};

template<class T>
class IInputComponent
{
private:
    std::vector<IInputComponentAction<T>> Bindings;
    std::vector<IInputComponentMouseAction<T>> MouseBindings;
public:
    void AddActionBinding(std::string name, int keyEventType, T* object, void(T::*func)())
    {
        for (size_t i = 0; i < InputManager::Get().GetNumberOfActions(); i++)
        {
            if(InputManager::Get().GetAction(i).ActionName == name)
                Bindings.push_back(IInputComponentAction<T>(name, keyEventType, object, func));
        }
    }
    void AddMouseActionBinding(std::string name, uint8_t eventType, T* object, void(T::*func)(float))
    {
        for (size_t i = 0; i < InputManager::Get().GetNumberOfMouseActions(); i++)
        {
            if(InputManager::Get().GetMouseAction(i).ActionName == name)
                MouseBindings.push_back(IInputComponentMouseAction<T>(name, eventType, object, func));
        }
    }
    void RemoveActionBinding(std::string name)
    {
        for (size_t i = 0; i < Bindings.size(); i++)
        {
            if(Bindings[i].ActName == name)
            {
                Bindings.erase(Bindings.begin() + i);
                return;
            }
        }
    }
    void RemoveMouseActionBinding(std::string name)
    {
        for (size_t i = 0; i < MouseBindings.size(); i++)
        {
            if(MouseBindings[i].ActName == name)
            {
                MouseBindings.erase(MouseBindings.begin() + i);
                return;
            }
        }
    }
    void ListenToInput()
    {
        for (size_t i = 0; i < Bindings.size(); i++)
        {
            int tstate = InputManager::Get().GetActionState(Bindings[i].ActName);
            if(tstate > 0)
            {
                if((tstate == BC_KEY_DOWN && Bindings[i].KeyEventType == BC_KEY_HOLD) || tstate == Bindings[i].KeyEventType)
                    (Bindings[i].Object->*(Bindings[i].Func))();
            }
        }
        for (size_t i = 0; i < MouseBindings.size(); i++)
        {
            IMouseState tmouse = InputManager::Get().GetMouseActionState(MouseBindings[i].ActName);
            if(MouseBindings[i].EventType == BC_MOUSE_AXES_X)
                (MouseBindings[i].Object->*(MouseBindings[i].Func))(tmouse.dx);
            else if(MouseBindings[i].EventType == BC_MOUSE_AXES_Y)
                (MouseBindings[i].Object->*(MouseBindings[i].Func))(tmouse.dy);
            else if(MouseBindings[i].EventType == BC_MOUSE_AXES_Z)
                (MouseBindings[i].Object->*(MouseBindings[i].Func))(tmouse.dz);
        }
        
    }
};

#endif /* B77A1BA5_6AE4_4C87_82C0_638A325673FE */
