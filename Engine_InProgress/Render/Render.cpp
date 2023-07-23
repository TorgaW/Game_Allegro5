#include "Render.hpp"

void Render::DrawScene()
{
    for (auto const& [key, val] : rd_target_scene->scene_map_object_buffer)
    {
        /* code */
    }
}

void Render::DrawUI(std::vector<Ref<Widget>> &widgets)
{
    for (size_t i = 0; i < widgets.size(); i++)
    {
        widgets[i]->PropagateDraw(delta_time);
    }
}
