#include "Noise.h"

Noise::Noise(uint16_t w, uint16_t h)
{
    Values = new float*[w];
    for (uint16_t i = 0; i < w; i++)
    {
        Values[i] = new float[h]();
    }
    Width = w;
    Height = h;
}

Noise::~Noise()
{
    for (uint16_t i = 0; i < Width; i++)
    {
        delete[] Values[i];
    }
    delete[] Values;
}

bool Noise::SetValueAt(uint16_t x, uint16_t y, float value)
{
    if(x > Width || y > Height) return false;
    Values[x][y] = value;
    return true;
}

float Noise::GetValueAt(int x, int y)
{
    if(x > Width-1 || y > Height-1 || x < 0 || y < 0) return 0.0f;
    return Values[x][y];
}

Noise *NoiseMath::Mul(Noise *l1, Noise *l2)
{
    if(l1 == nullptr || l2 == nullptr) return nullptr;
    if(l1->GetWidth() != l2->GetWidth() || l1->GetHeight() != l2->GetHeight()) return nullptr;

    Noise *t = new Noise(l1->GetWidth(), l1->GetHeight());
    for (uint16_t i = 0; i < l1->GetWidth(); i++)
    {
        for (uint16_t j = 0; j < l1->GetHeight(); j++)
        {
            t->SetValueAt(i, j, l1->GetValueAt(i, j) * l2->GetValueAt(i, j));
        }
    }
    return t;
}

void NoiseMath::Mul(Noise *l1, float val)
{
    if(l1 == nullptr) return;
    for (uint16_t i = 0; i < l1->GetWidth(); i++)
    {
        for (uint16_t j = 0; j < l1->GetHeight(); j++)
        {
            l1->SetValueAt(i, j, l1->GetValueAt(i, j) * val);
        }
    }
}

void NoiseMath::Power(Noise *base, float exp)
{
    if(base == nullptr) return;
    for (uint16_t i = 0; i < base->GetWidth(); i++)
    {
        for (uint16_t j = 0; j < base->GetHeight(); j++)
        {
            base->SetValueAt(i, j, std::pow(base->GetValueAt(i, j), exp));
        }
    }
}

void NoiseMath::Clamp(Noise *l1, float min, float max)
{
    if(l1 == nullptr) return;
    for (uint16_t i = 0; i < l1->GetWidth(); i++)
    {
        for (uint16_t j = 0; j < l1->GetHeight(); j++)
        {
            l1->SetValueAt(i, j, ComMath::Clamp(l1->GetValueAt(i, j), min, max));
        }
    }
}

void NoiseMath::Filter2D(Noise *l1, EFilterKernelType type, uint8_t iterations)
{
    if(l1 == nullptr) return;
    float t = 0.0f;
    const float *kernel;
    switch (type)
    {
    case EFilterKernelType::Gaussian:
        kernel = &KernelGaussian[0];
        break;
    case EFilterKernelType::Box:
        kernel = &KernelBox[0];
    case EFilterKernelType::Sharpen:
        kernel = &KernelSharpen[0];
    case EFilterKernelType::Ridge:
        kernel = &KernelRidge[0];
    case EFilterKernelType::Edge:
        kernel = &KernelEdge[0];
    default:
        break;
    }
    for (int i = 1; i < l1->GetWidth()-1; i++)
    {
        for (int j = 1; j < l1->GetHeight()-1; j++)
        {
            for (uint8_t k = 0; k < iterations; k++)
            {
                t = l1->GetValueAt(i-1, j-1) * kernel[0];
                t += l1->GetValueAt(i, j-1) * kernel[1];
                t += l1->GetValueAt(i+1, j-1) * kernel[2];

                t += l1->GetValueAt(i-1, j) * kernel[3];
                t += l1->GetValueAt(i, j) * kernel[4];
                t += l1->GetValueAt(i+1, j) * kernel[5];

                t += l1->GetValueAt(i-1, j+1) * kernel[6];
                t += l1->GetValueAt(i, j+1) * kernel[7];
                t += l1->GetValueAt(i+1, j+1) * kernel[8];
                l1->SetValueAt(i, j, ComMath::Clamp(t, 0.0f, 1.0f));
            }
        }
    }
}

Noise *NoiseMath::Filter(Noise *l1, bool (*lambda)(float value))
{
    if(l1 == nullptr || lambda == nullptr) return nullptr;
    Noise *t = new Noise(l1->GetWidth(), l1->GetHeight());
    float k = 0.0f;
    for (uint16_t i = 0; i < l1->GetWidth(); i++)
    {
        for (uint16_t j = 0; j < l1->GetHeight(); j++)
        {
            k = l1->GetValueAt(i, j);
            if(lambda(k))
                t->SetValueAt(i, j, k);
        }
    }
    return t;
}
