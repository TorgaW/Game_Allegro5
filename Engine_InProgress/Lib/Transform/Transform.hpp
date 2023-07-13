#ifndef B22BAF97_CDFF_4A44_83F4_BC1310288800
#define B22BAF97_CDFF_4A44_83F4_BC1310288800

#include <cmath>
#include <stdexcept>

struct Vec2
{
    float x, y;
    Vec2() : x(0.0f), y(0.0f) {};
    Vec2(float _x, float _y) : x(_x), y(_y) {};

    inline void Reset()
    {
        x = 0.0f;
        y = 0.0f;
    };

    inline float Len()
    {
        return std::sqrt(x*x + y*y);
    };

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
};

struct Transform
{
    Vec2 position, scale;
    float rotation {0};

    Transform(){};
    Transform(Vec2 _position, Vec2 _scale, float _rotation) : 
    position(_position), scale(_scale), rotation(_rotation)
    {};
};


#endif /* B22BAF97_CDFF_4A44_83F4_BC1310288800 */
