#ifndef CF4624D5_9A8A_40E0_B2C0_8FF70A7B9D26
#define CF4624D5_9A8A_40E0_B2C0_8FF70A7B9D26

#include "../../ALLEGRO_DefaultInclude.hpp"

class EngineFonts
{
public:
    static inline ALLEGRO_FONT *Ubuntu12R{nullptr};
    static inline ALLEGRO_FONT *Ubuntu14R{nullptr};
    static inline ALLEGRO_FONT *Ubuntu18R{nullptr};
    static inline ALLEGRO_FONT *Ubuntu22R{nullptr};
    static inline ALLEGRO_FONT *Ubuntu26R{nullptr};
    static inline ALLEGRO_FONT *Ubuntu30R{nullptr};

    static inline void InitEngineFonts()
    {
        Ubuntu12R = al_load_ttf_font("Resources/FontsSource/UbuntuMono-Regular.ttf", 12, 0);
        Ubuntu14R = al_load_ttf_font("Resources/FontsSource/UbuntuMono-Regular.ttf", 14, 0);
        Ubuntu18R = al_load_ttf_font("Resources/FontsSource/UbuntuMono-Regular.ttf", 18, 0);
        Ubuntu22R = al_load_ttf_font("Resources/FontsSource/UbuntuMono-Regular.ttf", 22, 0);
        Ubuntu26R = al_load_ttf_font("Resources/FontsSource/UbuntuMono-Regular.ttf", 26, 0);
        Ubuntu30R = al_load_ttf_font("Resources/FontsSource/UbuntuMono-Regular.ttf", 30, 0);
    }

    EngineFonts(){};
    ~EngineFonts(){};
};

#endif /* CF4624D5_9A8A_40E0_B2C0_8FF70A7B9D26 */
