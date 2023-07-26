#ifndef CCFCB114_92E5_49A3_8F6D_0A51B621F0EF
#define CCFCB114_92E5_49A3_8F6D_0A51B621F0EF

#include "../ALLEGRO_DefaultInclude.hpp"
#include "../STD_DefaultInclude.hpp"
#include "../EngineDebugger/EngineDebugger.hpp"
#include "../UI/WidgetManager/WidgetManager.hpp"
#include "../Input/InputManager.hpp"

class Game
{
private:
    bool game_is_setup {false};
    ALLEGRO_TIMER *game_timer;
    ALLEGRO_EVENT_QUEUE *game_event_queue;
    ALLEGRO_DISPLAY *game_display;

public:
    Game(){};
    ~Game(){};

public:
    void InitGame();
    void StartGame();
    void LoopGame();

    void EndGame();
};


#endif /* CCFCB114_92E5_49A3_8F6D_0A51B621F0EF */
