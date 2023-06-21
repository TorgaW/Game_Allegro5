#include "BitmapComponent.h"

BitmapComponent::BitmapComponent(std::string path)
{
    Bmp = al_load_bitmap(path.c_str());
    if(Bmp == nullptr)
    {
        std::cerr << "Failed to load bitmap: '" << path << "'!";
        return;
    }
    Width = al_get_bitmap_width(Bmp);
    Height = al_get_bitmap_height(Bmp);
    Path = path;
}

bool BitmapComponent::LoadBitmap(std::string path)
{
    Bmp = al_load_bitmap(path.c_str());
    if(Bmp == nullptr)
    {
        std::cerr << "Failed to load bitmap: '" << path << "'!";
        return false;
    }
    Width = al_get_bitmap_width(Bmp);
    Height = al_get_bitmap_height(Bmp);
    Path = path;
    return true;
}

void BitmapComponent::Draw(Vector2D position, Vector2D scale, int flg)
{
    al_draw_scaled_bitmap(Bmp, 0, 0, Width, Height, position.X, position.Y, Width * scale.X, Height * scale.Y, flg);
}

BitmapComponent::~BitmapComponent()
{
    al_destroy_bitmap(Bmp);
}
