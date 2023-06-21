#include "Widget.h"

Widget::Widget(uint32_t id, uint64_t timestamp, std::string name)
{
    ID = id;
    TimeStamp = timestamp;
    Name = name;
}

Widget::~Widget()
{
    delete Parent;
    for (size_t i = 0; i < Children.size(); i++)
        delete Children[i];
}

bool Widget::ChangeParent(Widget *new_parent)
{
    if(new_parent == nullptr) return false;
    Parent = new_parent;
    return true;
}

bool Widget::AddChild(Widget *new_child)
{
    if(new_child == nullptr) return false;
    Children.push_back(new_child);
    return true;
}

bool Widget::operator==(const Widget &b) const
{
    return ID == b.ID && TimeStamp == b.TimeStamp && Name == b.Name;
}
