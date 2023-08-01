#include "SceneManager.hpp"

void SceneManager::Init()
{
    current_scene = new Scene(last_scene_id, "default_scene");
    last_scene_id++;
}

void SceneManager::UpdateSceneObjects()
{
    if(current_scene != nullptr)
    {
        auto t = current_scene->GetBuffer();
        for (size_t i = 0; i < t->size(); i++)
        {
            (*t)[i]->Update(Render::GetDeltaTime());
        }
        Render::DrawScene(t);
    }
}
