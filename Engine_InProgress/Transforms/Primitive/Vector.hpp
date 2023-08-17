#ifndef DA6FE60F_F02D_48B3_96B4_1C90BA0DCEC2
#define DA6FE60F_F02D_48B3_96B4_1C90BA0DCEC2

#include <cmath>
#include <stdexcept>
#include <iostream>

struct Vec2
{
    float x, y;
    Vec2():x(0.0f),y(0.0f){};
    // Vec2(int _x):x(_x),y(_x){};
    // Vec2(int _x, int _y):x(_x),y(_y){};
    Vec2(float _x):x(_x),y(_x){};
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
    inline bool operator==(Vec2 const &rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
    inline void Reset()
    {
        x = 0.0f;
        y = 0.0f;
    };
    inline float Length()
    {
        return std::sqrt(x*x + y*y);
    };

    friend std::ostream& operator<< (std::ostream& stream, const Vec2 &v)
    {
        stream << "(" << v.x << ", " << v.y << ")";
        return stream; 
    }
};

struct Vec2i
{
    int x, y;
    Vec2i():x(0),y(0){};
    Vec2i(int _x):x(_x),y(_x){};
    Vec2i(int _x, int _y):x(_x),y(_y){};
    inline Vec2i operator+(Vec2i const &rhs)
    {
        return Vec2i(x+rhs.x, y+rhs.y);
    };
    inline Vec2i operator-(Vec2i const &rhs)
    {
        return Vec2i(x-rhs.x, y-rhs.y);
    };
    inline Vec2i operator+(int const &rhs)
    {
        return Vec2i(x+rhs, y+rhs);
    };
    inline Vec2i operator-(int const &rhs)
    {
        return Vec2i(x-rhs, y-rhs);
    };
    inline Vec2i operator*(int const &rhs)
    {
        return Vec2i(x*rhs, y*rhs);
    };
    inline Vec2i operator/(int const &rhs)
    {
        if(rhs == 0)
            throw std::invalid_argument("Zero division");
        return Vec2i(x/rhs, y/rhs);
    };
    inline bool operator==(Vec2i const &rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
    inline void Reset()
    {
        x = 0;
        y = 0;
    };
    inline float Length()
    {
        return std::sqrt(x*x + y*y);
    };

    friend std::ostream& operator<< (std::ostream& stream, const Vec2i &v)
    {
        stream << "(" << v.x << ", " << v.y << ")";
        return stream; 
    }
};



struct Vec2MapComprasion
{
    template<typename T>
    bool operator()(const T &l, const T &r) const
    {
        return l.x == r.x ? l.y < r.y : l.x < r.x;
    }
};

#endif /* DA6FE60F_F02D_48B3_96B4_1C90BA0DCEC2 */
