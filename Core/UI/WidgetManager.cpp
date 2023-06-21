#include "WidgetManager.h"

Viewport *UIManager::GetViewport()
{
    return Game::Get().GetWorld()->GetViewport();
}

bool UIManager::AddToViewport(Widget *new_widget)
{
    return GetViewport()->AddWidget(new_widget);
}

void UIManager::RemoveFromViewport(std::string name)
{
    GetViewport()->RemoveWidget(name);
}

void UIManager::RemoveFromViewport(Widget *widget)
{
    GetViewport()->RemoveWidget(widget);
}
