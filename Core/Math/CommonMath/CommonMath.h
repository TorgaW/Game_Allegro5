#ifndef D5C93B14_FE3D_4664_89FC_D4868F38F516
#define D5C93B14_FE3D_4664_89FC_D4868F38F516

namespace CommonMath
{
    inline float Clamp(float x, float min, float max)
    {
        const float t = x < min ? min : x;
        return t > max ? max : t;
    };
}

#endif /* D5C93B14_FE3D_4664_89FC_D4868F38F516 */
