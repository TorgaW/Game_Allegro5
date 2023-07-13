#ifndef AED8A420_1B5D_4C75_BD29_FAAB5B661F0C
#define AED8A420_1B5D_4C75_BD29_FAAB5B661F0C

#include "../STD_DefaultInclude.hpp"
#include "../ALLEGRO_DefaultInclude.hpp"

#include "../ObjectManager/ObjectManager.hpp"
#include "../SceneObject/SceneObject.hpp"


class Render
{
private:
    static double delta_time;
    static double new_frame_time;
    static double prev_frame_time;
    std::vector<ObjRef<SceneObject>> GBuffer {};
public:
    Render(){};
    ~Render() = default;

    inline static void UpdateDeltaTime()
    {
        new_frame_time = al_get_time();
        delta_time = new_frame_time - prev_frame_time;
        prev_frame_time = new_frame_time;
    };

    inline static double GetDeltaTime() { return delta_time; };

    inline static void SetViewportAsRenderTarget()
    {
        al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
    };
};


#endif /* AED8A420_1B5D_4C75_BD29_FAAB5B661F0C */
