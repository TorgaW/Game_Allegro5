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

    //now we can find widget on the screen
    std::cout << (WidgetManager::FindWidgetInViewport<CanvasWidget>("Widget_1", "class_CanvasWidget"))->GetName() << "\n";

    auto A = ObjectManager::CreateObject<Object>("A", "class_Object");
    auto B = ObjectManager::CreateObject<Object>("B", "class_Object");
    auto C = ObjectManager::CreateObject<Object>("C", "class_Object");
    auto D = ObjectManager::CreateObject<Object>("D", "class_Object");
    auto E = ObjectManager::CreateObject<Object>("E", "class_Object");

    A->AttachObjectChild(B);
    A->AttachObjectChild(C);
    B->AttachObjectChild(D);
    B->AttachObjectChild(E);

    for (size_t i = 0; i < 100; i++)
    {
        D->AttachObjectChild(ObjectManager::CreateObject<Object>(std::to_string(i), "class_Object"));
    }
    
    A->AttachObjectChild(canvas);

    ObjectManager::DestroyObject(A);

    // Benchmark _bench;
    // _bench.Start();
    // auto r = A->DeepCollectObjectChildren();
    // _bench.Stop();
    // for (size_t i = 0; i < r.size(); i++)
    // {
    //     std::cout << r[i]->GetName() << "; ";
    // }
    // std::cout << "\n in time: " << _bench.GetTimeMicro() << " microseconds\n";

    g.StartGame();
    return 0;
}
