#ifndef C0468F21_8B70_4A70_BC17_461040A37DB8
#define C0468F21_8B70_4A70_BC17_461040A37DB8

#include "../../Core/Defines/Defines.h"
#include "../../Core/Object/AObject.h"
// #include "../../Core/Render/Render.h"

class ASceneObject : public AObject
{
public:
    Transform2D Transform;
    Rectangle2D DrawBounds;
    Vector2D DrawBoundsOffset;
public:
    bool IgnoreDrawBounds;
    int Layer = 0;
    ASceneObject(uint32_t id, uint64_t timestamp, std::string name, std::string static_class_name);
    virtual ~ASceneObject();
    inline Rectangle2D GetDrawBounds()
    {
        return DrawBounds + DrawBoundsOffset;
    };
    inline Rectangle2D GetAbsoluteDrawBounds()
    {
        return Rectangle2D(Transform.Position + DrawBoundsOffset, Vector2D(DrawBounds.GetWidth(), DrawBounds.GetHeight()));
    }
};


#endif /* C0468F21_8B70_4A70_BC17_461040A37DB8 */
