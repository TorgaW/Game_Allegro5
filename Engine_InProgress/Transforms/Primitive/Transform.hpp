#ifndef A93688A8_EA0D_47D0_BC9C_8A2DB39C1C44
#define A93688A8_EA0D_47D0_BC9C_8A2DB39C1C44

#include "Vector.hpp"

struct Transform
{
    Vec2 position;
    Vec2 size;
    Vec2 scale;
    float rotation;

    Transform():rotation(0.0f){};
    Transform(Vec2 _pos, Vec2 _scale, Vec2 _size, float _rot) : 
    position(_pos), size(_size), scale(_scale), rotation(_rot)
    {};

    inline void Reset()
    {
        position.Reset();
        scale.Reset();
        size.Reset();
        rotation = 0.0f;
    }

};


#endif /* A93688A8_EA0D_47D0_BC9C_8A2DB39C1C44 */
