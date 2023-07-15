#ifndef BE196868_93AC_4112_8252_67A52CEE3BB4
#define BE196868_93AC_4112_8252_67A52CEE3BB4

#include "Vector.hpp"

struct Rect2
{
    Vec2 p00; //up-left
    Vec2 p01; //up-right
    Vec2 p10; //down-left
    Vec2 p11; //down-right
    Rect2(){};
    Rect2(Vec2 up_left_point, Vec2 size)
    {
        p00 = up_left_point;
        p01 = Vec2(p00.x + size.x, p00.y);
        p10 = Vec2(p00.x, p00.y + size.y);
        p11 = Vec2(p00.x + size.x, p00.y + size.y);
    }
    inline Rect2(Vec2 p1, Vec2 p2, Vec2 p3, Vec2 p4)
    {
        p00 = p1;
        p01 = p2;
        p10 = p3;
        p11 = p4;
    };
    inline bool ContainsPoint(Vec2 point)
    {
        return point.x >= p00.x && point.x <= p10.x
                && point.y >= p00.y && point.y <= p11.y;
    };
    inline bool IntersectsWith(Rect2 rect)
    {
        return !(p01.x < rect.p00.x || p00.x > rect.p01.x ||
                    p10.y < rect.p00.y || p00.y > rect.p10.y);
    };
    inline float GetWidth()
    {
        return p01.x - p00.x;
    };
    inline float GetHeight()
    {
        return p10.y - p00.y;
    };
    inline Vec2 GetCenter()
    {
        return {p01.x - GetWidth()/2, p10.y - GetHeight()/2};
    }

    inline Rect2 operator-(Vec2 const &rhs)
    {
        return Rect2(p00 - rhs, p01 - rhs, p10 - rhs, p11 - rhs);
    };
    inline Rect2 operator+(Vec2 const &rhs)
    {
        return Rect2(p00 + rhs, p01 + rhs, p10 + rhs, p11 + rhs);
    };
    inline Rect2 operator*(float const &rhs)
    {
        return Rect2(p00 * rhs, p01 * rhs, p10 * rhs, p11 * rhs);
    };
    inline Rect2 operator/(float const &rhs)
    {
        return Rect2(p00 / rhs, p01 / rhs, p10 / rhs, p11 / rhs);
    };
};

#endif /* BE196868_93AC_4112_8252_67A52CEE3BB4 */
