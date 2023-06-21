#ifndef B91FFFED_3F9B_4B56_815A_7D704248B1D2
#define B91FFFED_3F9B_4B56_815A_7D704248B1D2

#include <allegro5/allegro5.h>
#include <map>
#include <string>
#include <iostream>

class BitmapLoader
{
private:
    std::map<std::string, ALLEGRO_BITMAP*> LoadedBitmaps;
    BitmapLoader(){}
public:
    static BitmapLoader &Get()
    {
        static BitmapLoader instance;
        return instance;
    }
    BitmapLoader(BitmapLoader const &) = delete;
    void operator=(BitmapLoader const &) = delete;
    ALLEGRO_BITMAP *LoadBitmap(std::string path);
    ~BitmapLoader();
};


#endif /* B91FFFED_3F9B_4B56_815A_7D704248B1D2 */
