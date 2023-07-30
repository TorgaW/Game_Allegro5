// #include "Scene/Scene.hpp"
// #include "SceneManager/SceneManager.hpp"
#include "Engine.hpp"

int main(int argc, char const *argv[])
{
    Game g;
    g.InitGame();

    //create canvas
<<<<<<< Updated upstream
    // Benchmark _bench;
    // _bench.Start();
    auto canvas = WidgetManager::CreateWidget<CanvasWidget>("Widget_1", "class_CanvasWidget");
    // _bench.Stop();
    // std::cout << _bench.GetTimeMicro() << " microseconds\n";

||||||| Stash base
    auto canvas = WidgetManager::CreateWidget<CanvasWidget>("Widget_1", "class_CanvasWidget");
=======
    // auto canvas = WidgetManager::CreateWidget<CanvasWidget>("Widget_1", "class_CanvasWidget");
>>>>>>> Stashed changes

    // //create another canvas
    // auto canv_child = WidgetManager::CopyWidget<CanvasWidget>(canvas, "Widget_2");

    // //set canvas properties
    // canvas->widget_transform.size = {100, 100};
    // canvas->max_width = 200.f;
    // canvas->min_width = 50.f;

    // //set child props
    // canv_child->widget_transform.size = {50, 50};
    // canv_child->max_width = 100.f;
    // canv_child->min_width = 0.f;

    // //attch as child widget (calls Begin() method for canv_child)
    // canvas->AttachChild(canv_child);

    //add to viewport (calls Begin() method for canvas)
    // WidgetManager::AddToViewport(canvas);

    auto container = WidgetManager::CreateWidget<Container>("Container_1", "class_Container");
    container->SetPosition({Render::GetMonitorWidth() / 2.0f,
                         Render::GetMonitorHeight() / 2.0f});
    container->SetElementsAlignment(Alignment::RowUpperLeft);

    auto text1 = WidgetManager::CreateWidget<TextWidget>("TextWidget_1", "class_TextWidget");
    text1->SetFont(EngineFonts::Ubuntu30R);
    text1->SetText("I love Dasha");
    text1->SetPivotPoint({0.5f, 0.5f});
    text1->SetSize({200, 150});

    auto text2 = WidgetManager::CreateWidget<TextWidget>("TextWidget_1", "class_TextWidget");
    text2->SetFont(EngineFonts::Ubuntu30R);
    text2->SetText("AbobaAbobusovich");
    text2->SetPivotPoint({0.5f, 0.5f});
    text2->SetSize({200, 150});

    container->AttachChild(text2);
    container->AttachChild(text1);

    WidgetManager::AddToViewport(container);

    //now we can find widget on the screen
    std::cout << (WidgetManager::FindWidgetInViewport<CanvasWidget>("Widget_1", "class_CanvasWidget"))->GetName() << "\n";

    // auto A = ObjectManager::CreateObject<Object>("A", "class_Object");
    // auto B = ObjectManager::CreateObject<Object>("B", "class_Object");
    // auto C = ObjectManager::CreateObject<Object>("C", "class_Object");
    // auto D = ObjectManager::CreateObject<Object>("D", "class_Object");
    // auto E = ObjectManager::CreateObject<Object>("E", "class_Object");

    // A->AttachObjectChild(B);
    // A->AttachObjectChild(C);
    // B->AttachObjectChild(D);
    // B->AttachObjectChild(E);

    // for (size_t i = 0; i < 100; i++)
    // {
    //     D->AttachObjectChild(ObjectManager::CreateObject<Object>(std::to_string(i), "class_Object"));
    // }
    
    // A->AttachObjectChild(canvas);

    // ObjectManager::DestroyObject(A);

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
