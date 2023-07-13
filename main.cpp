#include "Core/CoreInclude.h"
#include "SceneObjects/SceneInclude.h"
#include "Core/Math/MathInclude.h"

// #include "Engine/System/Game/GameSystem.hpp"
// #include <iostream>
// #include "Engine/Engine.hpp"

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

    // EngineLog logger;
    // logger.Log("hello!", "test", BC_LOG_STATUS_SUCCESS);
    // logger.Log("hello 2!", "test", BC_LOG_STATUS_SUCCESS);
    
    // for (size_t i = 0; i < 10000; i++)
    // {
    //     ObjRef<Object> test = ObjectManager::CreateObject<Object>("Aboba", "class_Fedora");
    //     ObjectManager::DestroyObject(test);
    // }
    // std::cout << "cc test: " << test.GetValidationPtr().use_count() << "\n";
    // ObjRef<SceneObject> test2 = ObjectManager::CreateObject<SceneObject>("Aboba", "class_Fedora");
    // std::cout << test->GetObjId() << "\n";
    // std::cout << test2->GetObjId() << "\n";
    // auto s1 = std::chrono::high_resolution_clock::now();
    // ObjRef<Object> test = ObjectManager::CreateObject<Object>("Aboba", "class_Fedora");
    // std::cout << "users: " << test.RefCount() << "\n";
    // ObjectManager::DestroyObject(test);
    // GarbageCollector::CheckGarbage();
    // std::cout << "is unique: " << test.IsUniqueRef() << "\n";
    // std::cout << "name: " << ObjectManager::FindObject<Object>(ObjectFindMode::Class, "", "class_Fedora")->GetObjName() << "\n";
    // auto s2 = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(s2 - s1);
    // std::cout << duration.count() << " microseconds";
    // std::cout << test.IsUniqueRef() << "\n";
    // ObjRef<Object> find_test = ObjectManager::FindObject<Object>("Aboba");
    // std::cout << find_test->GetObjName() << "\n";
    // ObjRef<Object> test = ObjectManager::CreateObject<Object>("SubAboba", "class_SubAboba");
    // std::cout << test->GetObjName() << "\n";
    // ObjRef<SubObject> test_find = ObjectManager::FindObject<SubObject>("SubAboba");
    // std::cout << test_find->sub_field << "\n";
    return 0;
}
