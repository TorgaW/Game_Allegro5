#include "VectorMath.h"

namespace VMath
{
    float Dot(Vector2D a, Vector2D b)
    {
        return a.X*b.X + a.Y*b.Y;
    }
    float Length(Vector2D v)
    {
        return std::sqrt(v.X*v.X + v.Y*v.Y);
    }
    Vector2D Floor(Vector2D v)
    {
        return Vector2D(std::floor(v.X), std::floor(v.Y));
    }
    Vector2D Clamp(Vector2D v, float min, float max)
    {
        float tx = v.X < min ? min : v.X;
        tx = tx > max ? max : tx;
        float ty = v.Y < min ? min : v.Y;
        ty = ty > max ? max : ty;
        return Vector2D(tx, ty);
    }
    Vector2D Normalize(Vector2D v)
    {
        float t = v.Length();
        if(std::abs(t) < 0.0001f) return Vector2D(0, 0);
        return Vector2D(v.X / t, v.Y / t);
    }
    Vector2D Lerp(Vector2D current, Vector2D target, float t)
    {
        return Vector2D(current.X + (target.X - current.X) * t,
                        current.Y + (target.Y - current.Y) * t);
    }
}