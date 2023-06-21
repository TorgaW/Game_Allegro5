#include "Viewport.h"

bool Viewport::AddWidget(Widget *widget)
{
    if(widget == nullptr) return false;
    ScreenWidgets.push_back(widget);
    return true;
}

Viewport::Viewport()
{
    al_identity_transform(&UITransform);
    DebugScreenMessages = UIManager::Get().CreateWidget<Profiler>("BC_DefaultProfiler");
}

void Viewport::Update()
{
    al_use_transform(&UITransform);
    for (size_t i = 0; i < ScreenWidgets.size(); i++)
    {
        ScreenWidgets[i]->Update();
    }
    DebugScreenMessages->Update();
}

void Viewport::RemoveWidget(std::string name)
{
    ScreenWidgets.erase(std::remove_if(ScreenWidgets.begin(), ScreenWidgets.end(), [name](Widget *w){
        return w->GetName() == name;
    }), ScreenWidgets.end());
}

void Viewport::RemoveWidget(Widget *widget)
{
    ScreenWidgets.erase(std::remove_if(ScreenWidgets.begin(), ScreenWidgets.end(), [widget](Widget *w){
        return *w == *widget;
    }), ScreenWidgets.end());
}
