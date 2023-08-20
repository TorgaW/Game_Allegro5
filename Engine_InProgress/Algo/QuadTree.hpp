#ifndef D3111752_1F44_4EE9_A960_507A833DF5B1
#define D3111752_1F44_4EE9_A960_507A833DF5B1

#include "../STD_DefaultInclude.hpp"
#include "../ALLEGRO_DefaultInclude.hpp"
#include "../Transforms/Transform.hpp"

struct QT_Rect
{
    Vec2 center;
    float half_size {0.0f};

    float left {0.0f};
    float right {0.0f};
    float top {0.0f};
    float bottom {0.0f};

    //Set QT_Rect params based on Rect2. 
    //Attention: hals_size is set from Rect2 width because QT_Rect must be a square.
    QT_Rect(Rect2 source);
    QT_Rect(Vec2 _center, float _half_size); 

    //Set QT_Rect params based on Rect2. 
    //Attention: hals_size is set from Rect2 width because QT_Rect must be a square.
    void SetFromRect2(Rect2 source);

    //Returns Rect2 object
    Rect2 ToRect2();

    bool ContainsPoint(Vec2 p);

    bool IntersectsWithRect(QT_Rect other_rect);

    inline Vec2 GetP00() { return {center.x - half_size, center.y - half_size}; };
    inline Vec2 GetP10() { return {center.x + half_size, center.y - half_size}; };
    inline Vec2 GetP01() { return {center.x - half_size, center.y + half_size}; };
    inline Vec2 GetP11() { return {center.x + half_size, center.y + half_size}; };
};



class QuadTree
{
private:
    int qt_capacity = 6;
    QT_Rect boundary;
    std::vector<Vec2> points;
    QuadTree *north_west {nullptr};
    QuadTree *north_east {nullptr};
    QuadTree *south_west {nullptr};
    QuadTree *south_east {nullptr};
    bool is_subdivided {false};
    bool is_cleared {false};
public:

    void Subdivide();
    bool InsertPoint(Vec2 point);
    void RemoveInRange(QT_Rect range);
    void RemoveInRange(Rect2 range);
    void RemovePoint(Vec2 point);
    std::vector<Vec2> Query(QT_Rect range);
    std::vector<Vec2> Query(Rect2 range);
    void Clear();

    void DebugQuadTree();

public:
    QuadTree(QT_Rect _boundary) : boundary(_boundary) {};
    ~QuadTree();
};




#endif /* D3111752_1F44_4EE9_A960_507A833DF5B1 */
