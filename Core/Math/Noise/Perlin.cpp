#include "Perlin.h"

Vector2D PerlinNoise::grad(Vector2D v)
{
    // from wikipedia
    const uint32_t w = 8 * sizeof(uint32_t);
    const uint32_t s = w / 2; // rotation width
    uint32_t a = v.X, b = v.Y;
    a *= 3284157443;
    b ^= a << s | a >> (w - s);
    b *= 1911520717;
    a ^= b << s | b >> (w - s);
    a *= seed;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
    return Vector2D(std::cos(random), std::sin(random));
}

PerlinNoise::PerlinNoise()
{
    std::mt19937 mt(time(nullptr));
    seed = mt();
}

PerlinNoise::PerlinNoise(int32_t seed_)
{
    seed = seed_;
}

void PerlinNoise::ChangeSeed()
{
    std::mt19937 mt(time(nullptr));
    seed = mt();
}

float PerlinNoise::Generate2D(float x, float y)
{
    return Generate2D(Vector2D(x, y));
}

float PerlinNoise::Generate2D(Vector2D p)
{
    Vector2D p0 = VMath::Floor(p);
    Vector2D p1 = p0 + Vector2D(1.0f, 0.0f);
    Vector2D p2 = p0 + Vector2D(0.0f, 1.0f);
    Vector2D p3 = p0 + Vector2D(1.0f, 1.0f);

    Vector2D g00 = grad(p0);
    Vector2D g10 = grad(p1);
    Vector2D g01 = grad(p2);
    Vector2D g11 = grad(p3);

    Vector2D fd = fadeVector(p - p0);

    float p0p1 = (1.0f - fd.X) * VMath::Dot(g00, (p - p0)) + fd.X * VMath::Dot(g10, (p - p1));
    float p2p3 = (1.0f - fd.X) * VMath::Dot(g01, (p - p2)) + fd.X * VMath::Dot(g11, (p - p3));

    return ((1.0f - fd.Y) * p0p1 + fd.Y * p2p3);
}

Noise *PerlinNoise::GenerateNoise(uint16_t width, uint16_t height, uint8_t octaves, float scale)
{
    Noise *t = new Noise(width, height);

    if (boost::thread::hardware_concurrency() > 8)
    {
        // auto time_start = std::chrono::high_resolution_clock::now();
        uint16_t t_width = width / 8;
        boost::thread_group tg;
        for (size_t l = 0; l < 8; l++)
        {
            tg.create_thread(boost::bind<void>([height, octaves, scale, this](Noise *n, uint16_t start, uint16_t stop)
            {
                for (uint16_t i = start; i < stop; i++)
                {
                    for (uint16_t j = 0; j < height; j++)
                    {
                        float v = 0.0f;
                        for (uint8_t k = 0; k < octaves; k++)
                            v += Generate2D(i / std::pow(2.0f * scale, k + 1), j / std::pow(2.0f * scale, k + 1)) * (1.0f / (octaves - k));
                        v = v * 0.5f + 0.5f;
                        n->SetValueAt(i, j, v);
                    }
                } 
            },
            t, l * t_width, (l + 1) * t_width));
        }
        tg.join_all();
        // auto time_stop = std::chrono::high_resolution_clock::now();
        // std::cout << "4 Threads used; Total time: " << std::chrono::duration_cast<std::chrono::milliseconds>(time_stop - time_start).count() << "ms;\n";
    }
    else
    {
        for (uint16_t i = 0; i < width; i++)
        {
            for (uint16_t j = 0; j < height; j++)
            {
                float v = 0.0f;
                for (uint8_t k = 0; k < octaves; k++)
                    v += Generate2D(i / std::pow(2.0f * scale, k + 1), j / std::pow(2.0f * scale, k + 1)) * (1.0f / (octaves - k));
                v = v * 0.5f + 0.5f;
                t->SetValueAt(i, j, v);
            }
        }
    }

    return t;
}
