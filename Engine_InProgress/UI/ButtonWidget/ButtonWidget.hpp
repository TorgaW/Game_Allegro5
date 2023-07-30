#ifndef B55B37E9_7277_4750_88B4_EE4DBCB708A3
#define B55B37E9_7277_4750_88B4_EE4DBCB708A3

#include "../Widget/Widget.hpp"

class ButtonWidget : public Widget
{
    ButtonWidget(const std::string &_obj_class, const ObjectSignature &obj_sign) : Widget(_obj_class, obj_sign){};
    ~ButtonWidget(){};

    virtual void Begin();

    virtual void Draw();
};

#endif /* B55B37E9_7277_4750_88B4_EE4DBCB708A3 */
