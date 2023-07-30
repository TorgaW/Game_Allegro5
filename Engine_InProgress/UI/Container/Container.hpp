#ifndef DA9AC788_B999_4293_9BEC_C38A514E2DBC
#define DA9AC788_B999_4293_9BEC_C38A514E2DBC

#include "../Widget/Widget.hpp"

enum Alignment
{
    RowUpperLeft = 0,
    RowUpperCenter,
    RowUpperRight,
    RowMiddleLeft,
    RowMiddleCenter,
    RowMiddleRight,
    RowLowerLeft,
    RowLowerCenter,
    RowLowerRight,
    ColUpperLeft,
    ColUpperCenter,
    ColUpperRight,
    ColMiddleLeft,
    ColMiddleCenter,
    ColMiddleRight,
    ColLowerLeft,
    ColLowerCenter,
    ColLowerRight
};

class Container : public Widget
{
public:
    float border_thickness{0.f};

    ALLEGRO_COLOR border_color{al_map_rgb(0, 0, 0)};

    ALLEGRO_COLOR background_color{al_map_rgba(0, 0, 0, 0)};

    float border_radius{0.f};

    virtual void Update(float delta);

    void SetElementsAlignment(Alignment elements_alignment);

    void SetBackgroundColor(ALLEGRO_COLOR background_color);

    void SetBorderRadius(float border_radius);

    void SetBorderThickness(float border_thickness);

    void SetBorderColor(ALLEGRO_COLOR border_color);

    Container(const std::string &_obj_class, const ObjectSignature &obj_sign) : Widget(_obj_class, obj_sign){};
    ~Container(){};
};

#endif /* DA9AC788_B999_4293_9BEC_C38A514E2DBC */
