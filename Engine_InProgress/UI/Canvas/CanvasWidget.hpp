#ifndef CB72D98F_470D_4F42_9D3D_75543CBD29C0
#define CB72D98F_470D_4F42_9D3D_75543CBD29C0

#include "../Widget/Widget.hpp"

class CanvasWidget : public Widget
{
private:
    float target_width {1000.f}; //pixels
    float resize_speed {500.f}; //abstract value
    ALLEGRO_COLOR canvas_border_color {al_map_rgb_f(0.5f, 0.01f, 0.05f)};
    float canvas_border_thickness {3.0f}; //pixels
public:
    CanvasWidget(const std::string& _obj_class, const ObjectSignature& obj_sign) :
    Widget(_obj_class, obj_sign)
    {};
    ~CanvasWidget(){};

    /**
     * @brief called every frame after Update(). used to draw graphics.
     */
    virtual void Draw(float delta);
};


#endif /* CB72D98F_470D_4F42_9D3D_75543CBD29C0 */
