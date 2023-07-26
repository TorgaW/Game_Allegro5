#ifndef EA215E60_BBF3_4A1A_9738_87E04A69592F
#define EA215E60_BBF3_4A1A_9738_87E04A69592F

#include "../STD_DefaultInclude.hpp"
#include <allegro5/allegro5.h>
#include "../EngineDebugger/EngineDebugger.hpp"

#define BC_MOUSE_LKEY 150   // left mouse button
#define BC_MOUSE_RKEY 151   // right mouse button
#define BC_MOUSE_MIDKEY 152 // middle mouse button

#define BC_MOUSE_AXES_X 0x0 // mouse x coordinate
#define BC_MOUSE_AXES_Y 0x1 // mouse y coordinate
#define BC_MOUSE_AXES_Z 0x2 // mouse wheel

#define BC_KEY_DOWN 0x3
#define BC_KEY_UP 0x2
#define BC_KEY_HOLD 0x1

enum KeyboardEventType
{
    Hold = 0x1,
    Up = 0x2,
    Down = 0x3
};

struct KeyboardInputAction
{
    std::string action_name;
    unsigned char action_key;
    // KeyboardEventType action_event_type;
    bool action_use_shift;
    bool action_use_ctrl;
    bool action_use_alt;
    uint8_t action_state{0};

    KeyboardInputAction(){};
    KeyboardInputAction(std::string name, unsigned char key, /*KeyboardEventType event_type,*/ bool use_shift, bool use_ctrl, bool use_alt) : 
    action_name(name), action_key(key), /*action_event_type(event_type),*/
    action_use_shift(use_shift), action_use_ctrl(use_ctrl), action_use_alt(use_alt){};
};

class InputManager
{
private:
    static inline std::map<std::string, KeyboardInputAction> input_keyboard_actions{};
    static inline std::map<std::string, KeyboardInputAction> ui_input_keyboard_actions{};
    static inline std::array<unsigned char, ALLEGRO_KEY_MAX> input_keyboard_keys;
    static inline std::array<unsigned char, ALLEGRO_KEY_MAX> input_keyboard_key_up_queue;

    static inline bool ui_input_enabled{false};

public:
    static inline void Init()
    {
        input_keyboard_keys.fill(0x0);
        input_keyboard_key_up_queue.fill(0x0);
    };

    static inline bool KeyboardActionExists(std::string act_name)
    {
        return input_keyboard_actions.find(act_name) != input_keyboard_actions.end();
    };

    static inline uint8_t GetKeyboardActionState(std::string action_name)
    {
        if(KeyboardActionExists(action_name))
            return input_keyboard_actions[action_name].action_state;
        else 
            return 255;
    };

    static void CreateKeyboardInputAction(std::string act_name, unsigned char act_key, /*KeyboardEventType event_type,*/ bool ui_action = false);
    static void CreateKeyboardInputAction(std::string act_name, unsigned char act_key, /*KeyboardEventType event_type,*/ bool use_shift,
                                          bool use_ctrl, bool use_alt, bool ui_action = false);

    static void UpdateKeyboardActions();

    static inline void UpdateKeyboardKeyDown(uint8_t keycode)
    {
        input_keyboard_keys[keycode] = BC_KEY_DOWN;
    };
    static inline void UpdateKeyboardKeyUp(uint8_t keycode)
    {
        input_keyboard_key_up_queue[keycode] = true;
    };
    static inline void UpdateKeyboardKeysDuringRender()
    {
        for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
        {
            if (input_keyboard_key_up_queue[i])
            {
                input_keyboard_keys[i] = BC_KEY_UP;
                input_keyboard_key_up_queue[i] = false;
            }
            else
                input_keyboard_keys[i] &= BC_KEY_HOLD;
        }
        // EngineDebugger::PrintDebugMessage(std::to_string(input_keyboard_keys[ALLEGRO_KEY_W]), al_map_rgb(255, 255, 255), 0.0f);

    };

    InputManager(){};
    ~InputManager(){};
};

#endif /* EA215E60_BBF3_4A1A_9738_87E04A69592F */
