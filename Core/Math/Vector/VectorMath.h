#ifndef A090CCA6_C970_4D0C_80A2_F3782975F6A3
#define A090CCA6_C970_4D0C_80A2_F3782975F6A3

#include "../../Defines/Defines.h"
#include <cmath>

namespace VMath
{
    float Dot(Vector2D, Vector2D);
    float Length(Vector2D);
    Vector2D Floor(Vector2D);
    Vector2D Clamp(Vector2D, float min, float max);
    Vector2D Normalize(Vector2D);
    Vector2D Lerp(Vector2D current, Vector2D target, float t);
}


#endif /* A090CCA6_C970_4D0C_80A2_F3782975F6A3 */
