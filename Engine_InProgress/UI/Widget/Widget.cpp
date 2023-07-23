#include "Widget.hpp"

void Widget::SetVisibility(bool new_visibility, bool propagate_to_children)
{
    if(propagate_to_children)
    {
        widget_is_visible = new_visibility;
        for (size_t i = 0; i < widget_children.size(); i++)
            widget_children[i]->SetVisibility(new_visibility);
    }
    else
        widget_is_visible = new_visibility;
}

void Widget::SetIsActive(bool is_active, bool propagate_to_children)
{
    if(propagate_to_children)
    {
        widget_is_active = is_active;
        for (size_t i = 0; i < widget_children.size(); i++)
            widget_children[i]->SetIsActive(is_active);
    }
    else
        widget_is_active = is_active;
}

bool Widget::AttachChild(Ref<Widget> child)
{
    if(!child.IsValidStrict() || widget_is_removed) return false;
    if(child->widget_is_removed) return false;

    widget_children.emplace_back(child);
    child->widget_parent = MemoryPool::CreateRef(this);
    child->CallBegin();
    return true;
}

bool Widget::DetachChild(Ref<Widget> child)
{
    if(!child.IsValidStrict() || widget_is_removed) return false;
    if(child->widget_is_removed) return false;
    
    auto r = std::find(widget_children.begin(), widget_children.end(), child);
    if(r == widget_children.end()) return false;

    (*r)->widget_parent = Ref<Widget>();
    std::iter_swap(r, widget_children.end() - 1);
    widget_children.pop_back();

    return true;
    // widget_children.emplace_back(child);
    // child->widget_parent = std::make_shared<Widget>(this);
}

void Widget::PropagateUpdate(float delta)
{
    if(widget_is_active) Update(delta);
    for (size_t i = 0; i < widget_children.size(); i++)
    {
       widget_children[i]->PropagateUpdate(delta);
    }
    
}

void Widget::PropagateDraw(float delta)
{
    if(widget_is_active && widget_is_visible)
    {
        Draw(delta);
        for (size_t i = 0; i < widget_children.size(); i++)
        {
            widget_children[i]->PropagateDraw(delta);
        }
    }
}

