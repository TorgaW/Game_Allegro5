#ifndef C3619743_A32F_42FD_BC12_1CA87C3A6027
#define C3619743_A32F_42FD_BC12_1CA87C3A6027

#include <allegro5/allegro5.h>
#include "../STD_DefaultInclude.hpp"

class BitmapManager
{
private:
    static inline std::map<std::string, ALLEGRO_BITMAP*> loaded_bitmaps {};
public:
    static ALLEGRO_BITMAP *LoadBitmap(std::string path_to_bitmap);
    BitmapManager(){};
    ~BitmapManager();
};


#endif /* C3619743_A32F_42FD_BC12_1CA87C3A6027 */
