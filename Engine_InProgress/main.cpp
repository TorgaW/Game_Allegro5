// #include "Scene/Scene.hpp"
// #include "SceneManager/SceneManager.hpp"
#include "Engine.hpp"

int main(int argc, char const *argv[])
{
    Game g;
    g.InitGame();

    //create canvas
    auto canvas = WidgetManager::CreateWidget<CanvasWidget>("Widget_1", "class_CanvasWidget");

    //create another canvas
    auto canv_child = WidgetManager::CopyWidget<CanvasWidget>(canvas, "Widget_2");

    //set canvas properties
    canvas->widget_transform.size = {100, 100};
    canvas->max_width = 1000.f;
    canvas->min_width = 50.f;

    //set child props
    canv_child->widget_transform.size = {50, 50};
    canv_child->max_width = 950.f;
    canv_child->min_width = 0.f;

    //attch as child widget (calls Begin() method for canv_child)
    canvas->AttachChild(canv_child);

    //add to viewport (calls Begin() method for canvas)
    WidgetManager::AddToViewport(canvas);

    g.StartGame();
    return 0;
}
