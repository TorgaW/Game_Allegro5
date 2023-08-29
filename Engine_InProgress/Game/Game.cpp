#include "Game.hpp"

void Game::InitGame()
{
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_primitives_addon();
    

    // fixing directory issue
    ALLEGRO_PATH *p = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_change_directory(al_path_cstr(p, ALLEGRO_NATIVE_PATH_SEP));
    al_destroy_path(p);

    game_timer = al_create_timer(1.0 / 5000.0);
    game_event_queue = al_create_event_queue();
    al_set_new_display_flags(ALLEGRO_PROGRAMMABLE_PIPELINE | ALLEGRO_OPENGL | ALLEGRO_FULLSCREEN_WINDOW);
    al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_SUGGEST); //disable vsync
    // al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 4, ALLEGRO_SUGGEST);
    // al_set_new_display_option(ALLEGRO_SAMPLES, 16, ALLEGRO_SUGGEST);
    // al_set_new_display_option(ALLEGRO_RENDER_METHOD, 1, ALLEGRO_SUGGEST);
    // al_set_new_display_option(ALLEGRO_SUPPORT_NPOT_BITMAP, 1, ALLEGRO_SUGGEST);
    game_display = al_create_display(1920, 1080);

    al_register_event_source(game_event_queue, al_get_keyboard_event_source());
    al_register_event_source(game_event_queue, al_get_mouse_event_source());
    al_register_event_source(game_event_queue, al_get_display_event_source(game_display));
    al_register_event_source(game_event_queue, al_get_timer_event_source(game_timer));

    Render::Init();
    EngineFonts::InitEngineFonts();
    InputManager::Init();
    EngineDebugger::Init();
    SceneManager::Init();

    InputManager::CreateKeyInputAction("MoveUp", ALLEGRO_KEY_W);
    InputManager::CreateKeyInputAction("MoveDown", ALLEGRO_KEY_S);
    InputManager::CreateKeyInputAction("MoveRight", ALLEGRO_KEY_D);
    InputManager::CreateKeyInputAction("MoveLeft", ALLEGRO_KEY_A);
    InputManager::CreateKeyInputAction("ZoomIn", ALLEGRO_KEY_Z);
    InputManager::CreateKeyInputAction("ZoomOut", ALLEGRO_KEY_X);

    ShaderManager::LoadShader("MossyCobblestone", "Resources/Shaders/MossyCobblestone.glsl", ALLEGRO_SHADER_GLSL, ALLEGRO_PIXEL_SHADER);
    ShaderManager::LoadShader("Grass", "Resources/Shaders/Grass.glsl", ALLEGRO_SHADER_GLSL, ALLEGRO_PIXEL_SHADER);
    ShaderManager::LoadShader("Water", "Resources/Shaders/Water.glsl", ALLEGRO_SHADER_GLSL, ALLEGRO_PIXEL_SHADER);
    ShaderManager::LoadShader("Dirt", "Resources/Shaders/Dirt.glsl", ALLEGRO_SHADER_GLSL, ALLEGRO_PIXEL_SHADER);
    ShaderManager::LoadShader("TerrainBlending", "Resources/Shaders/TerrainBlending.glsl", ALLEGRO_SHADER_GLSL, ALLEGRO_PIXEL_SHADER);
    ShaderManager::LoadShader("ChunkGroundMaskGenerator", "Resources/Shaders/ChunkGroundMaskGenerator.glsl", ALLEGRO_SHADER_GLSL, ALLEGRO_PIXEL_SHADER);
    ShaderManager::LoadShader("ChunkGroundGenerator", "Resources/Shaders/ChunkGroundGenerator.glsl", ALLEGRO_SHADER_GLSL, ALLEGRO_PIXEL_SHADER);
    // ShaderManager::LoadShader("Terrain", "Resources/Shaders/Terrain.glsl", ALLEGRO_SHADER_GLSL, ALLEGRO_PIXEL_SHADER);

    // Render::SetGameWindowBounds({1920, 1080});
    Render::SetGameDisplay(game_display);
    game_is_setup = true;
}

void Game::StartGame()
{
    if(al_is_system_installed() && game_is_setup)
    {
        LoopGame();
    }
}

void Game::LoopGame()
{
    ALLEGRO_EVENT current_event;
    bool redraw_screen = true;
    double delta_time = 0.0;
    al_start_timer(game_timer);

    while (true)
    {
        al_wait_for_event(game_event_queue, &current_event);
        if (current_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        if(current_event.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
        {
            al_acknowledge_resize(game_display);
            Render::SetGameWindowBounds({current_event.display.width, current_event.display.height});
        }
        if (current_event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw_screen = true;
        }
        else if (current_event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (current_event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                EndGame();
                break;
            }
            InputManager::UpdateInputKeyDown(current_event.keyboard.keycode);
            InputManager::UpdateKeyActions();
        }
        else if (current_event.type == ALLEGRO_EVENT_KEY_UP)
        {
            InputManager::UpdateInputKeyUp(current_event.keyboard.keycode);
            InputManager::UpdateKeyActions();
        }
        else if(current_event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(current_event.mouse.button != 0)
            {
                if(current_event.mouse.button == 1)
                    InputManager::UpdateInputKeyDown(BC_MOUSE_LKEY);
                else if (current_event.mouse.button == 2)
                    InputManager::UpdateInputKeyDown(BC_MOUSE_RKEY);
                else if (current_event.mouse.button == 3)
                    InputManager::UpdateInputKeyDown(BC_MOUSE_MIDKEY);
                
                InputManager::UpdateKeyActions();
            }
        }
        else if(current_event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            if(current_event.mouse.button != 0)
            {
                if(current_event.mouse.button == 1)
                    InputManager::UpdateInputKeyUp(BC_MOUSE_LKEY);
                else if (current_event.mouse.button == 2)
                    InputManager::UpdateInputKeyUp(BC_MOUSE_RKEY);
                else if (current_event.mouse.button == 3)
                    InputManager::UpdateInputKeyUp(BC_MOUSE_MIDKEY);
                
                InputManager::UpdateKeyActions();
            }
        }
        else if(current_event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            InputManager::UpdateMouseState(current_event.mouse, game_display);
        }


        if (redraw_screen && al_is_event_queue_empty(game_event_queue))
        {
            al_clear_to_color(al_map_rgb(0,0,0));
            delta_time = Render::UpdateDeltaTime();
            SceneManager::UpdateSceneObjects();
            WidgetManager::UpdateWidgets();

            EngineDebugger::Update(delta_time);
            EngineDebugger::ShowFPS(delta_time);
            MemoryPool::DebugMemory();
            al_flip_display();
            redraw_screen = false;
            InputManager::UpdateInputKeysDuringRender();
            InputManager::UpdateKeyActions();
        }
    }
}

void Game::EndGame()
{
    al_destroy_timer(game_timer);
    al_destroy_event_queue(game_event_queue);
    al_destroy_display(game_display);
    al_use_shader(nullptr);
    MemoryPool::ClearMemory();
}
