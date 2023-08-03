#ifndef DA6FE60F_F02D_48B3_96B4_1C90BA0DCEC2
#define DA6FE60F_F02D_48B3_96B4_1C90BA0DCEC2

#include <cmath>
#include <stdexcept>

struct Vec2
{
    float x, y;
    Vec2() : x(0.0f), y(0.0f){};
    Vec2(float _x, float _y) : x(_x), y(_y){};
    inline Vec2 operator+(Vec2 const &rhs)
    {
        return Vec2(x + rhs.x, y + rhs.y);
    };
    inline Vec2 operator-(Vec2 const &rhs)
    {
        return Vec2(x - rhs.x, y - rhs.y);
    };
    inline Vec2 operator+(float const &rhs)
    {
        return Vec2(x + rhs, y + rhs);
    };
    inline Vec2 operator-(float const &rhs)
    {
        return Vec2(x - rhs, y - rhs);
    };
    inline Vec2 operator*(float const &rhs)
    {
        return Vec2(x * rhs, y * rhs);
    };
    inline Vec2 operator/(float const &rhs)
    {
        if (rhs == 0.0f)
            throw std::invalid_argument("Zero division");
        return Vec2(x / rhs, y / rhs);
    };
    inline void Reset()
    {
        x = 0.0f;
        y = 0.0f;
    };
    inline float Length()
    {
        return std::sqrt(x * x + y * y);
    };
};

struct Vec4
{
    float x, y, z, w;
    Vec4(){};
    Vec4(Vec2 _x, Vec2 _y) : x(_x.x), y(_x.y), z(_y.x), w(_y.y){};
    Vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w){};
    inline Vec4 operator+(Vec4 const &rhs)
    {
        return Vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
    };
    inline Vec4 operator-(Vec4 const &rhs)
    {
        return Vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
    };
    inline Vec4 operator+(float const &rhs)
    {
        return Vec4(x + rhs, y + rhs, z + rhs, w + rhs);
    };
    inline Vec4 operator-(float const &rhs)
    {
        return Vec4(x - rhs, y - rhs, z - rhs, w - rhs);
    };
    inline Vec4 operator*(float const &rhs)
    {
        return Vec4(x * rhs, y * rhs, z * rhs, w * rhs);
    };
    inline Vec4 operator/(float const &rhs)
    {
        if (rhs == 0.0f)
            throw std::invalid_argument("Zero division");
        return Vec4(x / rhs, y / rhs, z / rhs, w / rhs);
    };
    inline void Reset()
    {
        x = 0.f;
        y = 0.f;
        z = 0.f;
        w = 0.f;
    };
    inline float Length()
    {
        return std::sqrt(x * x + y * y + z * z + w * w);
    };
};

#endif /* DA6FE60F_F02D_48B3_96B4_1C90BA0DCEC2 */
