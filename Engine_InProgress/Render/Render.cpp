#include "Render.hpp"

// void Render::DrawScene()
// {
//     for (auto const& [key, val] : rd_target_scene->scene_map_object_buffer)
//     {
//         /* code */
//     }
// }

Rect2 Render::GetDisplayBoundsInWorldCoordinates()
{
    // std::cout << camera_transform.position;
    Vec2i wb = GetGameWindowBounds();
    float mw = wb.x;
    float mh = wb.y;
    // EngineDebugger::PrintDebugMessage(std::to_string(wb.x), al_map_rgb_f(1.0f,1.0f,1.0f), 0.0f);
    Rect2 t(Vec2(camera_transform.position.x - (mw/2.0) * (1.0/camera_transform.scale.x), 
                             camera_transform.position.y - (mh/2.0) * (1.0/camera_transform.scale.y)),
                             Vec2(mw * (1.0/camera_transform.scale.x), mh * (1.0/camera_transform.scale.y)));
    return t;
}

void Render::DrawUI(std::vector<Ref<Widget>> &widgets)
{
    al_use_transform(&ui_transform);
    for (size_t i = 0; i < widgets.size(); i++)
    {
        widgets[i]->PropagateDraw(delta_time);
    }
}

void Render::DrawScene(std::vector<Ref<SceneObject>> *objects)
{
    SetViewportAsRenderTarget();
    al_use_transform(&camera_offset_transform);
    for (size_t i = 0; i < objects->size(); i++)
    {
        (*objects)[i]->Draw(delta_time);
    }
}
