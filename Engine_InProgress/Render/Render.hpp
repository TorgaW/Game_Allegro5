#ifndef C54372D7_3DDA_4F17_B3E6_90E29E558310
#define C54372D7_3DDA_4F17_B3E6_90E29E558310

#include "../SceneManager/SceneManager.hpp"
// #include "../UI/WidgetManager/WidgetManager.hpp"
#include "../ALLEGRO_DefaultInclude.hpp"
#include "../UI/Widget/Widget.hpp"

class Widget;
class SceneObject;

class Render
{
private:
    // static inline Scene *rd_target_scene {nullptr};
    // static inline void *rd_target_ui {nullptr};
    
    static inline double new_frame_time {0.0}, delta_time {0.0}, prev_frame_time {0.0};
public:
    Render(){};
    ~Render(){};

    static inline double UpdateDeltaTime()
    {
        new_frame_time = al_get_time();
        delta_time = new_frame_time - prev_frame_time;
        prev_frame_time = new_frame_time;
        return delta_time;
    }

    static inline int GetMonitorWidth()
    {
        ALLEGRO_MONITOR_INFO info;
        al_get_monitor_info(0, &info);
        return info.x2 - info.x1;
    }

    static inline int GetMonitorHeight()
    {
        ALLEGRO_MONITOR_INFO info;
        al_get_monitor_info(0, &info);
        return info.y2 - info.y1;
    }

    static inline double GetDeltaTime() { return delta_time; };

    // static inline void SetTargetScene(Scene *_scene) { rd_target_scene = _scene; };
    // static inline Scene *GetTargetScene() { return rd_target_scene; };

    // static inline void SetTargetUI(void *_ui) { rd_target_ui = _ui; };
    // static inline void *GetTargetUI() { return rd_target_ui; };

    // static void DrawScene();
    // static void DrawScene(Scene*);

    static void DrawScene(std::vector<Ref<SceneObject>> *objects);

    static void DrawUI(std::vector<Ref<Widget>>& widgets);
};


#endif /* C54372D7_3DDA_4F17_B3E6_90E29E558310 */
