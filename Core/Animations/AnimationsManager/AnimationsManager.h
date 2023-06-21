#ifndef B931EBF5_8493_4B01_A975_313827B1E814
#define B931EBF5_8493_4B01_A975_313827B1E814

#include <allegro5/allegro5.h>
#include "../Animation/AAnimation.h"

class AnimationsManager
{
public:
    static AnimationsManager &Get()
    {
        static AnimationsManager instance;
        return instance;
    }
private:
    AnimationsManager(){};
public:
    AnimationsManager(AnimationsManager const &) = delete;
    void operator=(AnimationsManager const &) = delete;

    template <class T>
    T *CreateAnimation(std::string name, std::string path_to_image, uint16_t columns_num, uint16_t rows_num)
    {
        AAnimation *t = new AAnimation(name);
        if(!(t->LoadBitmap(path_to_image, columns_num, rows_num)))
        {
            delete t;
            return nullptr;
        }
        
        return t;
    }
};

#endif /* B931EBF5_8493_4B01_A975_313827B1E814 */
