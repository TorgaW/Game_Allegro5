#ifndef DA6FE60F_F02D_48B3_96B4_1C90BA0DCEC2
#define DA6FE60F_F02D_48B3_96B4_1C90BA0DCEC2

#include <cmath>
#include <stdexcept>

struct Vec2
{
    float x, y;
    Vec2():x(0.0f),y(0.0f){};
    Vec2(float _x, float _y):x(_x),y(_y){};
    inline Vec2 operator+(Vec2 const &rhs)
    {
        return Vec2(x+rhs.x, y+rhs.y);
    };
    inline Vec2 operator-(Vec2 const &rhs)
    {
        return Vec2(x-rhs.x, y-rhs.y);
    };
    inline Vec2 operator+(float const &rhs)
    {
        return Vec2(x+rhs, y+rhs);
    };
    inline Vec2 operator-(float const &rhs)
    {
        return Vec2(x-rhs, y-rhs);
    };
    inline Vec2 operator*(float const &rhs)
    {
        return Vec2(x*rhs, y*rhs);
    };
    inline Vec2 operator/(float const &rhs)
    {
        if(rhs == 0.0f)
            throw std::invalid_argument("Zero division");
        return Vec2(x/rhs, y/rhs);
    };
    inline void Reset()
    {
        x = 0.0f;
        y = 0.0f;
    };
    inline float Length()
    {
        return std::sqrt(x*x + y*y);
    };
};


#endif /* DA6FE60F_F02D_48B3_96B4_1C90BA0DCEC2 */
