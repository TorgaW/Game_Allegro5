#ifndef D990DDE9_031E_433B_83B3_3E5CA87EEA78
#define D990DDE9_031E_433B_83B3_3E5CA87EEA78
#include <stdexcept>
#include <cmath>
struct Vector2D
{
    float X, Y;
    Vector2D();
    Vector2D(float, float);
    inline Vector2D operator+(Vector2D const &rhs)
    {
        return Vector2D(X+rhs.X, Y+rhs.Y);
    };
    inline Vector2D operator-(Vector2D const &rhs)
    {
        return Vector2D(X-rhs.X, Y-rhs.Y);
    };
    inline Vector2D operator+(float const &rhs)
    {
        return Vector2D(X+rhs, Y+rhs);
    };
    inline Vector2D operator-(float const &rhs)
    {
        return Vector2D(X-rhs, Y-rhs);
    };
    inline Vector2D operator*(float const &rhs)
    {
        return Vector2D(X*rhs, Y*rhs);
    };
    inline Vector2D operator/(float const &rhs)
    {
        if(rhs == 0.0f)
            throw std::invalid_argument("Zero division");
        return Vector2D(X/rhs, Y/rhs);
    };
    inline void Reset()
    {
        X = 0.0f;
        Y = 0.0f;
    };
    inline float Length()
    {
        return std::sqrt(X*X + Y*Y);
    };
};


struct Transform2D
{
    Vector2D Position;
    Vector2D Scale;
    float Rotation;
    Transform2D(Vector2D pos, Vector2D scl, float rot) : Position(pos), Scale(scl), Rotation(rot) {}
    Transform2D()
    {
        Rotation = 0.0f;
    }
};

struct Rectangle2D
{
    Vector2D p00; //up-left
    Vector2D p01; //up-right
    Vector2D p10; //down-left
    Vector2D p11; //down-right
    Rectangle2D(){};
    Rectangle2D(Vector2D up_left_point, Vector2D size)
    {
        p00 = up_left_point;
        p01 = Vector2D(p00.X + size.X, p00.Y);
        p10 = Vector2D(p00.X, p00.Y + size.Y);
        p11 = Vector2D(p00.X + size.X, p00.Y + size.Y);
    }
    inline Rectangle2D(Vector2D p1, Vector2D p2, Vector2D p3, Vector2D p4)
    {
        p00 = p1;
        p01 = p2;
        p10 = p3;
        p11 = p4;
    };
    inline bool ContainsPoint(Vector2D point)
    {
        return point.X >= p00.X && point.X <= p10.X
                && point.Y >= p00.Y && point.Y <= p11.Y;
    };
    inline bool IntersectsWith(Rectangle2D rect)
    {
        return !(p01.X < rect.p00.X || p00.X > rect.p01.X ||
                    p10.Y < rect.p00.Y || p00.Y > rect.p10.Y);
    };
    inline float GetWidth()
    {
        return p01.X - p00.X;
    };
    inline float GetHeight()
    {
        return p10.Y - p00.Y;
    };
    inline Vector2D GetCenter()
    {
        return {p01.X - GetWidth()/2, p10.Y - GetHeight()/2};
    }

    inline Rectangle2D operator-(Vector2D const &rhs)
    {
        return Rectangle2D(p00 - rhs, p01 - rhs, p10 - rhs, p11 - rhs);
    };
    inline Rectangle2D operator+(Vector2D const &rhs)
    {
        return Rectangle2D(p00 + rhs, p01 + rhs, p10 + rhs, p11 + rhs);
    };
    inline Rectangle2D operator*(float const &rhs)
    {
        return Rectangle2D(p00 * rhs, p01 * rhs, p10 * rhs, p11 * rhs);
    };
    inline Rectangle2D operator/(float const &rhs)
    {
        return Rectangle2D(p00 / rhs, p01 / rhs, p10 / rhs, p11 / rhs);
    };
};
// typedef Vector2D Vector2D;

#endif /* D990DDE9_031E_433B_83B3_3E5CA87EEA78 */
