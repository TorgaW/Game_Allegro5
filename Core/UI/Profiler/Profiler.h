#ifndef B3AC434F_BB22_427A_9567_6EC9F2D87DA1
#define B3AC434F_BB22_427A_9567_6EC9F2D87DA1

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <sstream>
#include <vector>
#include "../Widget/Widget.h"
#include "../Fonts/StaticFonts.h"
#include "../../Render/Render.h"

struct DebugScreenMessage
{
    std::string message;
    ALLEGRO_COLOR color;
    float time;
    DebugScreenMessage(std::string, ALLEGRO_COLOR, float);
};


class Profiler : public Widget
{
private:
    std::vector<DebugScreenMessage> Messages;
public:
    Profiler(uint32_t id, uint64_t timestamp, std::string name);

    virtual void Update();

    void PrintDebugMessage(std::string text, ALLEGRO_COLOR text_color, float duration);
};


#endif /* B3AC434F_BB22_427A_9567_6EC9F2D87DA1 */
