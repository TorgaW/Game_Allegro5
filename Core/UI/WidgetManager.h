#ifndef A8D44206_92E8_46D7_938C_33641253CD74
#define A8D44206_92E8_46D7_938C_33641253CD74

#include <allegro5/allegro5.h>
#include <vector>
#include <string>
#include <chrono>
#include "Widget/Widget.h"
#include "../Main/Game.h"

class Viewport;

class UIManager
{
private:
    UIManager(){};
    uint32_t WidgetCounter;
public:
    static UIManager &Get()
    {
        static UIManager instance;
        return instance;
    }
    UIManager(UIManager const &) = delete;
    void operator=(UIManager const &) = delete;

    template <class T>
    T *CreateWidget(std::string name)
    {
        WidgetCounter++;
        uint64_t timestamp = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        T *p = new T(WidgetCounter, timestamp, name);
        return p;
    }

    Viewport *GetViewport();
    bool AddToViewport(Widget *new_widget);
    void RemoveFromViewport(std::string name);
    void RemoveFromViewport(Widget *widget);
};


#endif /* A8D44206_92E8_46D7_938C_33641253CD74 */
