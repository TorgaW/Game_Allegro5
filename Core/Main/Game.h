#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "../../SceneObjects/StaticObject/StaticObject.h"
#include "../Input/InputManager.h"
#include "../World.h"
#include "../../SceneObjects/Player/APlayer.h"
#include "../Math/Noise/Perlin.h"
#include "../Math/Noise/Noise.h"
#include "../Render/Render.h"
#include "../../SceneObjects/Camera/Camera.h"
#include "../UI/Viewport.h"
#include "../../WorldGeneration/ChunkManager/AChunkManager.h"

class World;
class Viewport;

class Game
{
public:
    static Game &Get()
    {
        static Game instance;
        return instance;
    }

private:
    ALLEGRO_TIMER *Timer;
    ALLEGRO_EVENT_QUEUE *Queue;
    ALLEGRO_DISPLAY *Disp;

    World *GameWorld;

private:
    Game() {}
    void GameLoop();
    void CloseGame();

public:
    // ALLEGRO_SHADER *shader_test;

public:
    Game(Game const &) = delete;
    void operator=(Game const &) = delete;
    void Init();
    void Start();
    inline World* GetWorld()
    {
        return GameWorld;
    }
    inline ALLEGRO_DISPLAY* GetDisplay()
    {
        return Disp;
    }
    Profiler *GetProfiler();
    Viewport *GetViewport();
};

#endif