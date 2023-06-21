#include "Core/CoreInclude.h"
#include "SceneObjects/SceneInclude.h"
#include "Core/Math/MathInclude.h"

int main(int argc, char const *argv[])
{
    InputManager::Get().CreateInputAction("MoveForward", ALLEGRO_KEY_W);
    InputManager::Get().CreateInputAction("MoveLeft", ALLEGRO_KEY_A);
    InputManager::Get().CreateInputAction("MoveBack", ALLEGRO_KEY_S);
    InputManager::Get().CreateInputAction("MoveRight", ALLEGRO_KEY_D);
    InputManager::Get().CreateInputAction("ZoomIn", ALLEGRO_KEY_P);
    InputManager::Get().CreateInputAction("ZoomOut", ALLEGRO_KEY_O);
    InputManager::Get().CreateMouseInputAction("MouseX", BC_MOUSE_AXES_X);
    InputManager::Get().CreateMouseInputAction("MouseY", BC_MOUSE_AXES_Y);
    InputManager::Get().CreateMouseInputAction("MouseZ", BC_MOUSE_AXES_Z);
    InputManager::Get().CreateMouseInputAction("UI_Mouse_Click", BC_MOUSE_LKEY);
    Game::Get().Init();
    Game::Get().Start();
    
    return 0;
}
