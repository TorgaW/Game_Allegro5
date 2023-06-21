#include "Render.h"

int Render::GetDisplayWidth()
{
    ALLEGRO_MONITOR_INFO info;
    al_get_monitor_info(0, &info);
    return info.x2 - info.x1;
}

int Render::GetDisplayHeight()
{
    ALLEGRO_MONITOR_INFO info;
    al_get_monitor_info(0, &info);
    return info.y2 - info.y1;
}

Rectangle2D Render::GetDisplayBoundsInWorldCoordinates()
{
    float mw = GetDisplayWidth();
    float mh = GetDisplayHeight();
    Rectangle2D t(Vector2D(CameraTransform.Position.X - (mw/2.0) * (1.0/CameraTransform.Scale.X), 
                             CameraTransform.Position.Y - (mh/2.0) * (1.0/CameraTransform.Scale.Y)),
                             Vector2D(mw * (1.0/CameraTransform.Scale.X), mh * (1.0/CameraTransform.Scale.Y)));
    return t;
}

void Render::DrawScreen(std::vector<ASceneObject*> *objects, Viewport *viewport)
{
    SetViewportAsRenderTarget();
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_use_transform(&SceneTransform);

    Rectangle2D mbounds = GetDisplayBoundsInWorldCoordinates();
    for (size_t i = 0; i < objects->size(); i++)
    {
        if(objects->at(i)->IgnoreDrawBounds)
            TBuffer.push_back(objects->at(i));
        else if(objects->at(i)->GetAbsoluteDrawBounds().IntersectsWith(mbounds))
            TBuffer.push_back(objects->at(i));
    }

    std::sort(TBuffer.begin(), TBuffer.end(), [](ASceneObject *a, ASceneObject *b){
        if(a->Layer == b->Layer)
            return a->Transform.Position.Y < b->Transform.Position.Y;
        return a->Layer < b->Layer;
        });
    for (size_t i = 0; i < TBuffer.size(); i++)
    {
        TBuffer[i]->GTick(DeltaTime);
    }

    TBuffer.clear();

    std::stringstream strs;
    strs.precision(2);
    strs << "FPS: " << std::fixed << 1.0f/DeltaTime << "; " << DeltaTime*1000.0f << " ms;";
    Game::Get().GetProfiler()->PrintDebugMessage(strs.str(), al_map_rgb(255, 255, 255), 0.0f);
    viewport->Update();
}
