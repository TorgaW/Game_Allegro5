#ifndef C306283A_6E0B_44C1_A0CA_1392372D626D
#define C306283A_6E0B_44C1_A0CA_1392372D626D

#include <allegro5/allegro5.h>
#include <string>
#include <iostream>
#include "../../Core/Defines/Defines.h"
#include "../AnimationComponent/AnimationComponent.h"
// #include "../../Core/Render/Render.h"

class SpriteSheetComponent
{
private:
    ALLEGRO_BITMAP *Bmp;
    uint16_t Width, Height, Rows, Columns, RowHeight, ColumnWidth, OffsetColumn, OffsetRow;
    ALLEGRO_COLOR Tint;

    AnimationComponent AnimComponent;
public:
    SpriteSheetComponent(){};
    SpriteSheetComponent(std::string path, uint16_t rows, uint16_t columns);
    bool LoadBitmap(std::string path, uint16_t rows, uint16_t columns);
    void Draw(Vector2D position, Vector2D scale, float delta_time, int flg = 0);
    ~SpriteSheetComponent(){ al_destroy_bitmap(Bmp); };
};


#endif /* C306283A_6E0B_44C1_A0CA_1392372D626D */
