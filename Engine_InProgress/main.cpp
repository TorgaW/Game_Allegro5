// #include "Scene/Scene.hpp"
// #include "SceneManager/SceneManager.hpp"
#include "Engine.hpp"

int main(int argc, char const *argv[])
{
    Game g;
    g.InitGame();

    //create canvas
    auto canvas = WidgetManager::CreateWidget<CanvasWidget>("Widget_1", "class_widget_DefaultWidget");
    //set canvas properties
    canvas->widget_transform.size = {100, 100};
    //add to viewport
    WidgetManager::AddToViewport(canvas);


    g.StartGame();
    return 0;
}
