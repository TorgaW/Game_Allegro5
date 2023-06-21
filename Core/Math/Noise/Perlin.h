#ifndef C59A3EF2_1FA0_4808_8E75_EFBB3A978728
#define C59A3EF2_1FA0_4808_8E75_EFBB3A978728

#include <cstdint>
#include <vector>
#include <cmath>
#include "../../Defines/Defines.h"
#include "../Vector/VectorMath.h"
#include "Noise.h"
#include <random>
#include <iostream>
#include <chrono>

#include <boost/thread.hpp>
#include <boost/bind.hpp>

class PerlinNoise
{
private:
    int32_t seed;
    std::vector<int> permut;
    inline float fade(float t)
    {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }
    inline float lerp(float t, float a, float b)
    {
        return a + t * (b - a);
    }
    inline Vector2D fadeVector(Vector2D v)
    {
        return Vector2D(fade(v.X), fade(v.Y));
    }
    Vector2D grad(Vector2D);
public:
    PerlinNoise();
    PerlinNoise(int32_t seed);
    inline void ChangeSeed(int32_t seed_)
    {
        seed = seed_;
    }
    void ChangeSeed();
    inline int32_t GetSeed()
    {
        return seed;
    }
    float Generate2D(float x, float y);
    float Generate2D(Vector2D p);

    //8 is max octaves
    Noise *GenerateNoise(uint16_t width, uint16_t height, uint8_t octaves, float scale);
};


#endif /* C59A3EF2_1FA0_4808_8E75_EFBB3A978728 */
