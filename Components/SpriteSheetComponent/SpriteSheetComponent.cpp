#include "SpriteSheetComponent.h"

SpriteSheetComponent::SpriteSheetComponent(std::string path, uint16_t rows, uint16_t columns)
{
    LoadBitmap(path, rows, columns);
}

bool SpriteSheetComponent::LoadBitmap(std::string path, uint16_t rows, uint16_t columns)
{
    if(rows == 0 || columns == 0)
    {
        std::cerr << "Failed to create SpriteSheetComponent! Invalid rows or columns value\n";
        return false;
    }
    Bmp = al_load_bitmap(path.c_str());
    if(Bmp == nullptr)
    {
        std::cerr << "Failed to load bitmap: '" << path << "'!\n";
        return false;
    }
    // AnimComponent.InstallBitmap(Bmp, columns, rows);
    Tint = al_map_rgb(255, 255, 255);
    return true;
}

void SpriteSheetComponent::Draw(Vector2D position, Vector2D scale, float delta_time, int flg)
{
    // AnimComponent.Update(delta_time);
    // AnimComponent.Draw(position, scale, Tint);
}
