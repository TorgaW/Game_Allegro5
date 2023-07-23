#ifndef E1E34B5C_F77F_41E7_9CDB_53ECF6CF2EA1
#define E1E34B5C_F77F_41E7_9CDB_53ECF6CF2EA1

#include "../STD_DefaultInclude.hpp"
#include "../ALLEGRO_DefaultInclude.hpp"
#include "../UI/WidgetManager/WidgetManager.hpp"

class EngineDebugger
{
private:
    
public:
    EngineDebugger(){};
    ~EngineDebugger(){};

    static inline void ShowFPS(double delta)
    {
        std::stringstream strs;
        strs.precision(2);
        strs << "FPS: " << std::fixed << 1.0f/delta << "; " << delta*1000.0f << " ms;";
        al_draw_text(EngineFonts::Ubuntu18R, al_map_rgb(255,255,255), 0, 0, 0, strs.str().c_str());
    }
};


#endif /* E1E34B5C_F77F_41E7_9CDB_53ECF6CF2EA1 */
