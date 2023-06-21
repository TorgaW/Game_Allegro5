#ifndef ED35E175_3887_4F65_8BF6_6E13E144D75D
#define ED35E175_3887_4F65_8BF6_6E13E144D75D

#include <cstdint>
#include <cmath>

namespace ComMath
{
    inline float Clamp(float x, float min, float max)
    {
        const float t = x < min ? min : x;
        return t > max ? max : t;
    };
}

class Noise
{
private:
    float **Values;
    uint16_t Width, Height;
public:
    Noise(uint16_t w, uint16_t h);
    ~Noise();
    inline uint16_t GetWidth() { return Width; };
    inline uint16_t GetHeight() { return Height; };
    bool SetValueAt(uint16_t x, uint16_t y, float value);
    float GetValueAt(int x, int y);
};

namespace NoiseMath
{
    //gaussian kernel for 3x3 matrix
    const float KernelGaussian[9] = {0.0625f, 0.125f, 0.0625f, 0.125f, 0.25f, 0.125f, 0.0625f, 0.125f, 0.0625f};

    //box kernel for 3x3 matrix
    const float KernelBox[9] = {0.111111f, 0.111111f, 0.111111f, 0.111111f, 0.111111f, 0.111111f, 0.111111f, 0.111111f, 0.111111f};

    //sharpen kernel for 3x3 matrix
    const float KernelSharpen[9] = { 0.0f, -1.0f, 0.0f, -1.0f, 5.0f, -1.0f, 0.0f, -1.0f, 0.0f };

    //ridge kernel for 3x3 matrix
    const float KernelRidge[9] = { 0.0f, -1.0f, 0.0f, -1.0f, 4.0f, -1.0f, 0.0f, -1.0f, 0.0f };

    //edge kernel for 3x3 matrix
    const float KernelEdge[9] = { 1.0f, 0.0f, -1.0f, 2.0f, 0.0f, -2.0f, 1.0f, 0.0f, -1.0f };

    enum EFilterKernelType
    {
        Gaussian = 0,
        Box = 1,
        Sharpen = 2,
        Ridge = 3,
        Edge = 4
    };

    Noise *Mul(Noise *l1, Noise *l2);
    void Mul(Noise *l1, float val);
    void Power(Noise *l1, float exp);
    void Clamp(Noise *l1, float min = 0.0f, float max = 1.0f);
    void Filter2D(Noise *l1, EFilterKernelType type, uint8_t iterations = 3);
    Noise *Filter(Noise *l1, bool(*lambda)(float value));
}

#endif /* ED35E175_3887_4F65_8BF6_6E13E144D75D */
