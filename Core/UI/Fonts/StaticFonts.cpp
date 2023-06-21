#include "StaticFonts.h"

void StaticFonts::LoadFonts()
{
    Ubuntu12R = al_load_ttf_font("Resources/Fonts/UbuntuMono-Regular.ttf", 12, 0);
    Ubuntu14R = al_load_ttf_font("Resources/Fonts/UbuntuMono-Regular.ttf", 14, 0);
    Ubuntu16R = al_load_ttf_font("Resources/Fonts/UbuntuMono-Regular.ttf", 16, 0);
    Ubuntu18R = al_load_ttf_font("Resources/Fonts/UbuntuMono-Regular.ttf", 18, 0);
    Ubuntu20R = al_load_ttf_font("Resources/Fonts/UbuntuMono-Regular.ttf", 20, 0);
    Ubuntu22R = al_load_ttf_font("Resources/Fonts/UbuntuMono-Regular.ttf", 22, 0);
    Ubuntu24R = al_load_ttf_font("Resources/Fonts/UbuntuMono-Regular.ttf", 24, 0);
}

void StaticFonts::FreeFonts()
{
    al_destroy_font(Ubuntu12R);
    al_destroy_font(Ubuntu14R);
    al_destroy_font(Ubuntu16R);
    al_destroy_font(Ubuntu18R);
    al_destroy_font(Ubuntu20R);
    al_destroy_font(Ubuntu22R);
    al_destroy_font(Ubuntu24R);
}