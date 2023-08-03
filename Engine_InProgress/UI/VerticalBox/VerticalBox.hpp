#ifndef CBBEB7B5_CAC6_4D61_A03A_C9CA78261FFF
#define CBBEB7B5_CAC6_4D61_A03A_C9CA78261FFF

#include "../Widget/Widget.hpp"
#include "../HorizontalBox/HorizontalBox.hpp"

class VerticalBox : public Widget
{
public:
    float border_thickness{0.f};

    ALLEGRO_COLOR border_color{al_map_rgb(0, 0, 0)};

    ALLEGRO_COLOR background_color{al_map_rgba(0, 0, 0, 0)};

    float border_radius{0.f};

    Alignment container_alignment{UpperLeft};

    float elements_gap_y{0.f};

    bool horizontal_stretch{false};

    bool vertical_stretch{false};

    Vec4 padding{0, 0, 0, 0};

    virtual void Update(float delta);

    virtual void Draw(float delta);

    inline void SetPadding(Vec4 new_padding) { padding = new_padding; };

    inline void SetHorizontalStretch(bool isEnabled) { horizontal_stretch = isEnabled; };

    inline void SetVerticalStretch(bool isEnabled) { vertical_stretch = isEnabled; };

    inline void SetElementsGap(float new_elements_gap_x) { elements_gap_y = new_elements_gap_x; };

    inline void SetElementsAlignment(Alignment new_elements_alignment)
    {
        container_alignment = new_elements_alignment;
        requestAlignmentRender = true;
    };

    inline void SetBackgroundColor(ALLEGRO_COLOR new_background_color) { background_color = new_background_color; };

    inline void SetBorderRadius(float new_border_radius) { border_radius = new_border_radius; };

    inline void SetBorderThickness(float new_border_thickness) { border_thickness = new_border_thickness; };

    inline void SetBorderColor(ALLEGRO_COLOR new_border_color) { border_color = new_border_color; };

    VerticalBox(const std::string &_obj_class, const ObjectSignature &obj_sign) : Widget(_obj_class, obj_sign){};
    ~VerticalBox(){};

protected:
    bool requestAlignmentRender{true};
};

#endif /* CBBEB7B5_CAC6_4D61_A03A_C9CA78261FFF */
