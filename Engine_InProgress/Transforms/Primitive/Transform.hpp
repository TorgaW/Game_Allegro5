#ifndef A93688A8_EA0D_47D0_BC9C_8A2DB39C1C44
#define A93688A8_EA0D_47D0_BC9C_8A2DB39C1C44

#include "Vector.hpp"

struct Transform2
{
    Vec2 position;
    Vec2 scale;
    float rotation;

    Transform2():rotation(0.0f){};
    Transform2(Vec2 _pos, Vec2 _scale, float _rot) : 
    position(_pos), scale(_scale), rotation(_rot)
    {};

    inline void Reset()
    {
        position.Reset();
        scale.Reset();
        rotation = 0.0f;
    }

};


#endif /* A93688A8_EA0D_47D0_BC9C_8A2DB39C1C44 */
