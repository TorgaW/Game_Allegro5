#ifndef E38DAEB6_BF2C_4C99_9C8A_6F9A5B9C4FEF
#define E38DAEB6_BF2C_4C99_9C8A_6F9A5B9C4FEF

#include "../../STD_DefaultInclude.hpp"
#include "../../ALLEGRO_DefaultInclude.hpp"
#include "../../Transforms/Transform.hpp"
#include "../../Object/Object.hpp"
#include "../../Render/Render.hpp"

class Widget : public Object
{
public:
    Transform widget_transform;

    Ref<Widget> widget_parent;
    std::vector<Ref<Widget>> widget_children;

    //is widget visible on screen
    bool widget_is_visible {true};
    
    //is widget triggers Update() and Draw() methods.
    bool widget_is_active {true};

    //is widget still valid or should be removed from any container.
    bool widget_is_removed {false};

public:
    Widget(const std::string& _obj_class, const ObjectSignature& obj_sign) :
    Object(_obj_class, obj_sign)
    {};
    ~Widget(){};

    /**
     * @brief called once when widget is created.
     */
    virtual void Begin() {};

    /**
     * @brief called every frame.
     */
    virtual void Update(float delta) {};

    /**
     * @brief called every frame after Update(). used to draw graphics.
     */
    virtual void Draw(float delta) {};

    /**
     * @brief called before widget destruction. 
     */
    virtual void End() {};

    //changes widget visibility.
    void SetVisibility(bool new_visibility, bool propagate_to_children = true);

    //disable or enable widget Update() and Draw() triggering.
    void SetIsActive(bool is_active, bool propagate_to_children = true);

    //add child to widget
    bool AttachChild(Ref<Widget> child);

    //remove child from widget
    bool DetachChild(Ref<Widget> child);

    void PropagateUpdate(float delta);

    void PropagateDraw(float delta);

    inline bool CanHaveChildren() { return widget_can_have_children; };

protected:
    //can widget hold children.
    bool widget_can_have_children {true};
};


#endif /* E38DAEB6_BF2C_4C99_9C8A_6F9A5B9C4FEF */
