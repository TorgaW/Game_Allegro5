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
    static inline ALLEGRO_TRANSFORM camera_offset_transform;
    static inline Transform camera_transform;
    static inline ALLEGRO_TRANSFORM ui_transform;
    static inline Vec2i game_window_bounds;
    static inline ALLEGRO_DISPLAY *game_display {nullptr};
public:
    Render(){};
    ~Render(){};

    static inline void Init()
    {
        al_identity_transform(&ui_transform);
    };

    static inline double UpdateDeltaTime()
    {
        new_frame_time = al_get_time();
        delta_time = new_frame_time - prev_frame_time;
        prev_frame_time = new_frame_time;
        return delta_time;
    };

    static inline int GetMonitorWidth()
    {
        ALLEGRO_MONITOR_INFO info;
        al_get_monitor_info(0, &info);
        return info.x2 - info.x1;
    };

    static inline int GetMonitorHeight()
    {
        ALLEGRO_MONITOR_INFO info;
        al_get_monitor_info(0, &info);
        return info.y2 - info.y1;
    };

    static inline Vec2i GetGameWindowBounds()
    {
        return {al_get_display_width(game_display), al_get_display_height(game_display)};
    };

    static inline int GetDisplayWidth()
    {
        return al_get_display_width(game_display);
    };

    static inline int GetDisplayHeight()
    {
        return al_get_display_height(game_display);
    };

    static inline void SetGameDisplay(ALLEGRO_DISPLAY *new_game_display)
    {
        game_display = new_game_display;
    };

    static inline void SetGameWindowBounds(Vec2i new_game_window_bounds)
    {
        game_window_bounds = new_game_window_bounds;
    };

    static Rect2 GetDisplayBoundsInWorldCoordinates();

    static inline Transform GetCameraTransfrom() 
    {
        return camera_transform;
    };

    static inline double GetDeltaTime() { return delta_time; };

    static inline void SetViewportAsRenderTarget()
    {
        al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
    };

    static inline void SetCameraOffsetTransform(ALLEGRO_TRANSFORM new_camera_offset_transform)
    {
        camera_offset_transform = new_camera_offset_transform;
    };

    static inline void SetCameraTransform(Transform new_camera_transform)
    {
        camera_transform = new_camera_transform;
    };

    static void DrawScene(std::vector<Ref<SceneObject>> *objects);

    static void DrawUI(std::vector<Ref<Widget>>& widgets);
};


#endif /* C54372D7_3DDA_4F17_B3E6_90E29E558310 */
