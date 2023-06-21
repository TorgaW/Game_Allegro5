#ifndef AAF5B084_F260_42F2_B940_26773B28A0C9
#define AAF5B084_F260_42F2_B940_26773B28A0C9

#include <vector>
#include <string>
#include <cstdint>
#include "../../Defines/Defines.h"

class Widget
{
private:
    uint32_t ID;
    uint64_t TimeStamp;
    std::string Name;
    Widget *Parent;
    std::vector<Widget*> Children;
    Vector2D ScreenPosition;
public:
    bool bIsHidden;
public:
    Widget(uint32_t, uint64_t, std::string);
    ~Widget();
    inline std::string GetName()
    {
        return Name;
    }
    inline Widget *GetParent()
    {
        return Parent;
    }
    virtual bool ChangeParent(Widget *new_parent);

    inline std::vector<Widget*> GetChildren() 
    {
        return Children;
    }
    virtual bool AddChild(Widget *new_child);

    inline void SetScreenPosition(Vector2D new_pos)
    {
        ScreenPosition = new_pos;
    }
    inline Vector2D GetScreenPosition()
    {
        return ScreenPosition;
    }

    virtual void Update(){};

    bool operator==(const Widget& b) const;
};


#endif /* AAF5B084_F260_42F2_B940_26773B28A0C9 */
