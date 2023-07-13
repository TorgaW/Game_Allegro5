#include "Game.h"

void Game::GameLoop()
{
    ALLEGRO_EVENT Event;
    bool Redraw = true;
    al_start_timer(Timer);
    uint32_t counter = 0;

    // APlayer *p = ObjectManager::Get().CreateObject<APlayer>("Player #1", "APlayer");
    // Game::Get().GetWorld()->AddToWorld(p);
    // PerlinNoise pn;
    // float noise[1024][1024];
    // for (size_t i = 0; i < 1024; i++)
    // {
    //     for (size_t j = 0; j < 1024; j++)
    //     {
    //         noise[i][j] = (pn.Generate2D(Vector2D(i/64.0f, j/64.0f)) + 
    //                         pn.Generate2D(Vector2D(i/32.0f, j/32.0f))*0.5f +
    //                         pn.Generate2D(Vector2D(i/16.0f, j/16.0f))*0.25f +
    //                         pn.Generate2D(Vector2D(i/8.0f, j/8.0f))*0.125f) * 0.5f + 0.5f;
    //     }
    // }

    // AStaticObject *sto = ObjectManager::Get().CreateObject<AStaticObject>("static_0", "AStaticObject");
    // sto->Transform.Scale = Vector2D(10.0f, 10.0f);
    // GameWorld->AddToWorld(sto);

    AChunkManager *chunks = ObjectManager::Get().CreateObject<AChunkManager>("chunk_manager", "AChunkManager");
    GameWorld->AddToWorld(chunks);
    chunks->GenerateWorld();

    APlayer *player = ObjectManager::Get().CreateObject<APlayer>("main_player", "APlayer");
    GameWorld->AddToWorld(player);
    player->SetPlayerCamera(GameWorld->GetScene()->GetMainCamera());
    GameWorld->GetScene()->GetMainCamera()->SetParent(player);

    // al_set_mouse_xy(Disp, 2560/2, 1440/2);
    // al_hide_mouse_cursor(Disp);

    InputManager::Get().UIInputEnabled = false;

    // PerlinNoise pn(783654);
    // PerlinNoise pn(20062001);
    // Noise *Layer1 = pn.GenerateNoise(1024, 1024, 1, 64.0f);
    // Noise *Layer2 = pn.GenerateNoise(1024, 1024, 8, 1.0f);

    // // NoiseMath::Power(Layer2, 1.5f);
    // NoiseMath::Filter2D(Layer2, NoiseMath::EFilterKernelType::Gaussian);
    // Noise *MaskWater = NoiseMath::Filter(Layer2, [](float t){return t < 0.27f;});
    // NoiseMath::Power(MaskWater, 0.1f);
    // NoiseMath::Clamp(MaskWater);
    // // NoiseMath::Filter2D(MaskWater, NoiseMath::EFilterKernelType::Edge, 1);
    
    // ALLEGRO_BITMAP *btm = al_create_bitmap(Layer2->GetWidth(), Layer2->GetHeight());
    // al_lock_bitmap(btm, ALLEGRO_LOCK_WRITEONLY, 0);
    // al_set_target_bitmap(btm);
    // ALLEGRO_COLOR color_g = al_map_rgb(18, 117, 0);
    // ALLEGRO_COLOR color_gd = al_map_rgb(18*0.9, 117*0.9, 0);
    // ALLEGRO_COLOR color_w = al_map_rgb(14, 146, 196);
    // ALLEGRO_COLOR color_wd = al_map_rgb(11, 99, 170);
    // ALLEGRO_COLOR color_s = al_map_rgb(191, 159, 61);
    // ALLEGRO_COLOR color_sd = al_map_rgb(191*0.7, 159*0.7, 61*0.7);
    // ALLEGRO_COLOR color_m = al_map_rgb(82, 80, 73);
    // float t;
    // for (size_t i = 0; i < Layer2->GetWidth(); i++)
    // {
    //     for (size_t j = 0; j < Layer2->GetHeight(); j++)
    //     {
    //         t = Layer2->GetValueAt(i, j);
    //         // if(t > 0.6f)
    //         //     al_put_pixel(i, j, color_m);
    //         // else if(t > 0.7f)
    //         //     al_put_pixel(i, j, color_gd);
    //         // else if(t > 0.4f)
    //         //     al_put_pixel(i, j, color_g);
    //         // else if(t > 0.33f)
    //         //     al_put_pixel(i, j, color_sd);
    //         // else if(t > 0.3f)
    //         //     al_put_pixel(i, j, color_s);
    //         // else if(t > 0.28f)
    //         //     al_put_pixel(i, j, color_w);
    //         // else
    //         //     al_put_pixel(i, j, color_wd);
    //         al_put_pixel(i, j, al_map_rgb(255*t, 255*t, 255*t));
    //     }
    // }
    // al_unlock_bitmap(btm);
    // Render::Get().SetViewportAsRenderTarget();

    ALLEGRO_BITMAP *aaabbb = al_load_bitmap("Resources/Sprites/sprite_sheet_placeholder_10r_20c.png");

    while (true)
    {
        al_wait_for_event(Queue, &Event);
        if (Event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        if (Event.type == ALLEGRO_EVENT_TIMER)
        {
            Redraw = true;
        }
        else if (Event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (Event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                CloseGame();
                break;
            }
            InputManager::Get().UpdateKeyDown(Event.keyboard.keycode);
            InputManager::Get().UpdateInputActions();
        }
        else if (Event.type == ALLEGRO_EVENT_KEY_UP)
        {
            InputManager::Get().UpdateKeyReleased(Event.keyboard.keycode);
            InputManager::Get().UpdateInputActions();
        }
        else if(Event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(Event.mouse.button != 0)
            {
                if(Event.mouse.button == 1)
                    InputManager::Get().UpdateKeyDown(BC_MOUSE_LKEY);
                else if (Event.mouse.button == 2)
                    InputManager::Get().UpdateKeyDown(BC_MOUSE_RKEY);
                else if (Event.mouse.button == 3)
                    InputManager::Get().UpdateKeyDown(BC_MOUSE_MIDKEY);
                
                InputManager::Get().UpdateInputActions();
            }
        }
        else if(Event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            if(Event.mouse.button != 0)
            {
                if(Event.mouse.button == 1)
                    InputManager::Get().UpdateKeyReleased(BC_MOUSE_LKEY);
                else if (Event.mouse.button == 2)
                    InputManager::Get().UpdateKeyReleased(BC_MOUSE_RKEY);
                else if (Event.mouse.button == 3)
                    InputManager::Get().UpdateKeyReleased(BC_MOUSE_MIDKEY);
                
                InputManager::Get().UpdateInputActions();
            }
        }
        else if(Event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            InputManager::Get().UpdateMouseState(Event.mouse, Disp);
        }
        else if (Event.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY)
        {
            InputManager::Get().ResetMouseDelta();
        }
    

        if (Redraw && al_is_event_queue_empty(Queue))
        {
            InputManager::Get().UpdateKeysInRender();
            InputManager::Get().UpdateInputActions();
            InputManager::Get().UpdateMouseActions();
            // GVariables::UpdateDeltaTime();
            // HDebug::UpdateFPS();
            // al_use_transform(Render::Get().GetSceneTransform());
            //     al_draw_tinted_scaled_rotated_bitmap_region(aaabbb,
            //                                 0, 0, 16, 16,
            //                                 al_map_rgb_f(1,1,1),
            //                                 8, 8,
            //                                 100, 100, 
            //                                 4, 4,
            //                                 0, 0);
            // GraphicsRender.UpdateObjects();
            // HDebug::ShowFPS();
            // HDebug::Update();
            Render::Get().UpdateDeltaTime();
            GameWorld->UpdateScene();
            // al_draw_scaled_bitmap(btm, 0, 0, 1024, 1024, 0, 0, Layer2->GetWidth(), Layer2->GetHeight(), 0);
            // al_draw_bitmap(chunks->GetCurrentChunk(), 100, 100, 0);
            // al_draw_bitmap();
            // counter++;
            // if(counter == 1000)
            // {
            //     GameWorld->RemoveFromWorld(p);
            //     delete p;
            // }
            InputManager::Get().ResetMouseDelta();
            al_flip_display();
            Redraw = false;
        }
    }
}

void Game::CloseGame()
{
    al_destroy_timer(Timer);
    al_destroy_event_queue(Queue);
    al_destroy_display(Disp);
    al_use_shader(nullptr);
    StaticFonts::Get().FreeFonts();

    delete GameWorld;
}

void Game::Init()
{
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();

    // fixing directory issue
    ALLEGRO_PATH *p = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_change_directory(al_path_cstr(p, ALLEGRO_NATIVE_PATH_SEP));
    al_destroy_path(p);

    StaticFonts::Get().LoadFonts();

    Timer = al_create_timer(1.0 / 5000.0);
    Queue = al_create_event_queue();
    al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_SUGGEST);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    Disp = al_create_display(2560, 1440);

    al_register_event_source(Queue, al_get_keyboard_event_source());
    al_register_event_source(Queue, al_get_mouse_event_source());
    al_register_event_source(Queue, al_get_display_event_source(Disp));
    al_register_event_source(Queue, al_get_timer_event_source(Timer));

    ShaderManager *sm = new ShaderManager();
    Render::Get().SetShaders(sm);
    Render::Get().GetShaders()->LoadShader("Test #1", "Shaders/World/Perlin.glsl", ALLEGRO_SHADER_GLSL, ALLEGRO_PIXEL_SHADER);

    // ALLEGRO_SHADER *PerlinShader = al_create_shader(ALLEGRO_SHADER_GLSL);
    // al_attach_shader_source_file(PerlinShader, ALLEGRO_PIXEL_SHADER, "Shaders/World/Perlin.glsl");
    // al_build_shader(PerlinShader);
    // shader_test = PerlinShader;

    GameWorld = new World();
    Viewport *DefaultUIViewport = new Viewport();
    Camera *DefaultCamera = new Camera();

    GameWorld->GetScene()->ChangeViewport(DefaultUIViewport);
    GameWorld->GetScene()->SetMainCamera(DefaultCamera);
}

void Game::Start()
{
    if (al_is_system_installed())
        GameLoop();
}

Profiler *Game::GetProfiler()
{
    return GameWorld->GetProfiler();
}

Viewport *Game::GetViewport()
{
    return GameWorld->GetViewport();
}
