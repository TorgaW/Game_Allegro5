#ifndef DFE43440_CE75_4456_89EA_F7B14429519C
#define DFE43440_CE75_4456_89EA_F7B14429519C

#include "allegro5/allegro5.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>

class StaticFonts
{
private:
    ALLEGRO_FONT *Ubuntu12R;
    ALLEGRO_FONT *Ubuntu14R;
    ALLEGRO_FONT *Ubuntu16R;
    ALLEGRO_FONT *Ubuntu18R;
    ALLEGRO_FONT *Ubuntu20R;
    ALLEGRO_FONT *Ubuntu22R;
    ALLEGRO_FONT *Ubuntu24R;
private:
    StaticFonts()
    {
    };

public:
    inline ALLEGRO_FONT *GetUbuntu12R()
    {
        return Ubuntu12R;
    }
    inline ALLEGRO_FONT *GetUbuntu14R()
    {
        return Ubuntu14R;
    }
    inline ALLEGRO_FONT *GetUbuntu16R()
    {
        return Ubuntu16R;
    }
    inline ALLEGRO_FONT *GetUbuntu18R()
    {
        return Ubuntu18R;
    }
    inline ALLEGRO_FONT *GetUbuntu20R()
    {
        return Ubuntu20R;
    }
    inline ALLEGRO_FONT *GetUbuntu22R()
    {
        return Ubuntu22R;
    }
    inline ALLEGRO_FONT *GetUbuntu24R()
    {
        return Ubuntu24R;
    }
public:
    static StaticFonts &Get()
    {
        static StaticFonts instance;
        return instance;
    }
    StaticFonts(StaticFonts const &) = delete;
    void operator=(StaticFonts const &) = delete;

    void LoadFonts();
    void FreeFonts();
};



#endif /* DFE43440_CE75_4456_89EA_F7B14429519C */
