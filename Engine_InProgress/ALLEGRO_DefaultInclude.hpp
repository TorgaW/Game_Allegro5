#ifndef B095895A_BF01_40AF_A281_94EA868422C8
#define B095895A_BF01_40AF_A281_94EA868422C8

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_opengl.h"

typedef ALLEGRO_BITMAP Bitmap;
typedef ALLEGRO_SHADER Shader;

class EngineColors
{
public:
    EngineColors(){};
    ~EngineColors(){};

    static inline ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
    static inline ALLEGRO_COLOR green = al_map_rgb(0, 255, 0);
    static inline ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);
    static inline ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
    static inline ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
    static inline ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    static inline ALLEGRO_COLOR cyan = al_map_rgb(0, 255, 255);
    static inline ALLEGRO_COLOR magenta = al_map_rgb(255, 0, 255);
};


#endif /* B095895A_BF01_40AF_A281_94EA868422C8 */
