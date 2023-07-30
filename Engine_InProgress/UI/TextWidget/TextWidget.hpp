#ifndef FECA94A2_B659_4591_9C12_ADF82F73B3D1
#define FECA94A2_B659_4591_9C12_ADF82F73B3D1

#include "../Widget/Widget.hpp"

class TextWidget : public Widget
{
public:
    ALLEGRO_FONT *text_font{nullptr};
    ALLEGRO_COLOR text_color{al_map_rgb(255, 255, 255)};
    
    Vec2 text_position;

    std::string text;

    virtual void Begin();

    virtual void Update(float delta);

    virtual void Draw(float delta);

    void SetText(const std::string &text);

    void SetFont(ALLEGRO_FONT *font);

    void SetTextColor(ALLEGRO_COLOR color);

    TextWidget(const std::string &_obj_class, const ObjectSignature &obj_sign) : Widget(_obj_class, obj_sign){};
    ~TextWidget(){};
};

#endif /* FECA94A2_B659_4591_9C12_ADF82F73B3D1 */
