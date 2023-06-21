#ifndef AF66B130_C618_43D2_9D79_212A59EA4A2E
#define AF66B130_C618_43D2_9D79_212A59EA4A2E

#include <allegro5/allegro5.h>
#include "Profiler/Profiler.h"
#include "WidgetManager.h"
#include <vector>

class Profiler;

class Viewport
{
private:
    std::vector<Widget*> ScreenWidgets;
    Profiler *DebugScreenMessages;
    ALLEGRO_TRANSFORM UITransform;
public:
    Viewport();
    bool AddWidget(Widget *widget);
    void RemoveWidget(std::string name);
    void RemoveWidget(Widget *widget);

    void Update();

    inline Profiler *GetProfiler()
    {
        return DebugScreenMessages;
    }
};


#endif /* AF66B130_C618_43D2_9D79_212A59EA4A2E */
