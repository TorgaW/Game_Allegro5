#ifndef E1E34B5C_F77F_41E7_9CDB_53ECF6CF2EA1
#define E1E34B5C_F77F_41E7_9CDB_53ECF6CF2EA1

#include "../STD_DefaultInclude.hpp"
#include "../ALLEGRO_DefaultInclude.hpp"

struct EngineDebugMessage
{
    std::string message {""};
    ALLEGRO_COLOR color {al_map_rgb_f(1.0f, 1.0f, 0.0f)};
    float live_time {0.0};
    EngineDebugMessage(){};
    EngineDebugMessage(std::string msg, ALLEGRO_COLOR clr, float time) :
    message(msg), color(clr), live_time(time)
    {};
};

class EngineDebugger
{
private:
    static inline ALLEGRO_FONT *debug_font {nullptr};
    static inline std::vector<EngineDebugMessage> messages_queue {};
public:
    EngineDebugger(){};
    ~EngineDebugger(){};

    static inline void Init()
    {
        debug_font = al_load_ttf_font("Resources/FontsSource/UbuntuMono-Regular.ttf", 14, 0);
    };

    static inline void ShowFPS(double delta)
    {
        std::stringstream strs;
        strs.precision(2);
        strs << "FPS: " << std::fixed << 1.0f/delta << "; " << delta*1000.0f << " ms;";
        al_draw_text(debug_font, al_map_rgb(255,255,255), 0, 0, 0, strs.str().c_str());
    };

    static void PrintDebugMessage(std::string msg, ALLEGRO_COLOR clr, float time);

    static void Update(float delta);
};


#endif /* E1E34B5C_F77F_41E7_9CDB_53ECF6CF2EA1 */
