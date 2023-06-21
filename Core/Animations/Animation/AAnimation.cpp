#include "AAnimation.h"

bool AAnimation::LoadBitmap(std::string path_to_image, uint16_t columns_num, uint16_t rows_num)
{
    if(path_to_image == "") return false;
    if(columns_num == 0 || rows_num == 0) return false;
    Bitmap = BitmapLoader::Get().LoadBitmap(path_to_image.c_str());
    if(Bitmap == nullptr) return false;
    SizeX = al_get_bitmap_width(Bitmap);
    SizeY = al_get_bitmap_height(Bitmap);
    CellsNumX = columns_num;
    CellsNumY = rows_num;
    CellSizeX = SizeX / columns_num;
    CellSizeY = SizeY / rows_num;
    EndPositionX = CellsNumX;
    EndPositionY = CellsNumY;
    return true;
}

void AAnimation::Update(float delta)
{
    FramesCounter += delta * AnimationSpeed;
    if(FramesCounter >= FrameDelta)
    {
        if(CurrentX < EndPositionX)
            CurrentX++;
        else
            CurrentX = StartPositionX;
        FramesCounter = 0.0f;
    }
}

AAnimation::AAnimation(std::string name)
{
    Name = name;
}

AAnimation::~AAnimation()
{
    al_destroy_bitmap(Bitmap);
}