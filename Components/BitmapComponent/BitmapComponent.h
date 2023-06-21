#ifndef C90A805D_F815_4414_9372_66BA015E420A
#define C90A805D_F815_4414_9372_66BA015E420A

#include <allegro5/allegro5.h>
#include <string>
#include <iostream>
#include "../../Core/Defines/Defines.h"
class BitmapComponent
{
private:
    ALLEGRO_BITMAP *Bmp;
    uint16_t Width, Height;
    std::string Path;
    Vector2D DrawOffset;
public:
    BitmapComponent(){};
    BitmapComponent(std::string path);
    bool LoadBitmap(std::string path);
    void Draw(Vector2D position, Vector2D scale, int flg = 0);
    ~BitmapComponent();
};


#endif /* C90A805D_F815_4414_9372_66BA015E420A */
