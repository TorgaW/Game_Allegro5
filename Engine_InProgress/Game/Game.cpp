#include "Game.hpp"

void Game::InitGame()
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

    game_timer = al_create_timer(1.0 / 5000.0);
    game_event_queue = al_create_event_queue();
    al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_SUGGEST);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    game_display = al_create_display(1920, 1080);

    al_register_event_source(game_event_queue, al_get_keyboard_event_source());
    al_register_event_source(game_event_queue, al_get_mouse_event_source());
    al_register_event_source(game_event_queue, al_get_display_event_source(game_display));
    al_register_event_source(game_event_queue, al_get_timer_event_source(game_timer));

    EngineFonts::InitEngineFonts();
    InputManager::Init();
    EngineDebugger::Init();

    InputManager::CreateKeyboardInputAction("test_input", ALLEGRO_KEY_W);

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
    al_start_timer(game_timer);

    while (true)
    {
        al_wait_for_event(game_event_queue, &current_event);
        if (current_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
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
            InputManager::UpdateKeyboardKeyDown(current_event.keyboard.keycode);
            InputManager::UpdateKeyboardActions();
        }
        else if (current_event.type == ALLEGRO_EVENT_KEY_UP)
        {
            InputManager::UpdateKeyboardKeyUp(current_event.keyboard.keycode);
            InputManager::UpdateKeyboardActions();
        }


        if (redraw_screen && al_is_event_queue_empty(game_event_queue))
        {

            al_clear_to_color(al_map_rgb(0,0,0));
            double delta_time = Render::UpdateDeltaTime();
            WidgetManager::UpdateWidgets();
            
            EngineDebugger::Update(delta_time);
            EngineDebugger::ShowFPS(delta_time);
            al_flip_display();
            redraw_screen = false;
            InputManager::UpdateKeyboardKeysDuringRender();
            InputManager::UpdateKeyboardActions();
        }
    }
}

void Game::EndGame()
{
    al_destroy_timer(game_timer);
    al_destroy_event_queue(game_event_queue);
    al_destroy_display(game_display);
    al_use_shader(nullptr);
}
