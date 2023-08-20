// #include "Scene/Scene.hpp"
// #include "SceneManager/SceneManager.hpp"
#include "Engine.hpp"


int main(int argc, char const *argv[])
{
    Game g;
    g.InitGame();

    auto wl = SceneManager::CreateSceneObject<WorldLoader>("WorldLoader_1", "class_WorldLoader");
    auto cam = SceneManager::CreateSceneObject<Camera>("Camera_1", "class_Camera");
    auto ph = SceneManager::CreateSceneObject<TestSceneObjectWithPhysics>("Test_phys", "class_TestSceneObjectWithPhysics");
    

    for (size_t i = 0; i < 60; i++)
    {
        auto t = SceneManager::CreateSceneObject<SceneObject>("aboba", "class_SceneObject");
        t->transform.position.x += 10*i;
        t->transform.position.y += 10*i;
        wl->AddObjectToWorld(t);
    }
    


    // ph->transform.position = {200.f, 200.f};

    // auto r = SceneManager::CreateSceneObject<SceneObject>("Test", "class_SceneObject");
    // r->transform.position = {500, 500};

    //create canvas
    // Benchmark _bench;
    // _bench.Start();
    // auto canvas = WidgetManager::CreateWidget<CanvasWidget>("Widget_1", "class_CanvasWidget");
    // _bench.Stop();
    // std::cout << _bench.GetTimeMicro() << " microseconds\n";

    // create canvas
    //  Benchmark _bench;
    //  _bench.Start();
    //  auto canvas = WidgetManager::CreateWidget<CanvasWidget>("Widget_1", "class_CanvasWidget");
    //  _bench.Stop();
    //  std::cout << _bench.GetTimeMicro() << " microseconds\n";

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

    // add to viewport (calls Begin() method for canvas)
    //  WidgetManager::AddToViewport(canvas);

    // auto container = WidgetManager::CreateWidget<HorizontalBox>("Container_1", "class_Container");
    // container->SetPosition({Render::GetMonitorWidth() / 2.0f,
    //                         Render::GetMonitorHeight() / 2.0f});
    // container->SetSize({1440, Render::GetMonitorHeight() / 2.0f});
    // container->SetElementsGap(100.f);
    // container->SetBackgroundColor(al_map_rgba(100, 100, 100, 20));
    // container->SetBorderRadius(20.f);
    // container->SetPivotPoint({0.5f, 0.5f});
    // container->SetElementsAlignment(Alignment::UpperLeft);

    // auto text1 = WidgetManager::CreateWidget<TextWidget>("TextWidget_1", "class_TextWidget");
    // text1->SetFont(EngineFonts::Ubuntu30R);
    // text1->SetText("Dasha");
    // text1->SetPivotPoint({0.5f, 0.5f});
    // text1->SetSize({200, 100});

    // auto text2 = WidgetManager::CreateWidget<TextWidget>("TextWidget_2", "class_TextWidget");
    // text2->SetFont(EngineFonts::Ubuntu30R);
    // text2->SetText("Dasha");
    // text2->SetPivotPoint({0.5f, 0.5f});
    // text2->SetSize({200, 80});

    // auto text3 = WidgetManager::CreateWidget<TextWidget>("TextWidget_3", "class_TextWidget");
    // text3->SetFont(EngineFonts::Ubuntu30R);
    // text3->SetText("Dasha");
    // text3->SetPivotPoint({0.5f, 0.5f});
    // text3->SetSize({200, 600});

    // auto text4 = WidgetManager::CreateWidget<TextWidget>("TextWidget_3", "class_TextWidget");
    // text4->SetFont(EngineFonts::Ubuntu30R);
    // text4->SetText("Dasha");
    // text4->SetPivotPoint({0.5f, 0.5f});
    // text4->SetSize({200, 50});

    // container->AttachChild(text1);
    // container->AttachChild(text2);
    // container->AttachChild(text3);
    // container->AttachChild(text4);

    // WidgetManager::AddToViewport(container);

    // now we can find widget on the screen
    //  std::cout << (WidgetManager::FindWidgetInViewport<CanvasWidget>("Widget_1", "class_CanvasWidget"))->GetName() << "\n";

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
