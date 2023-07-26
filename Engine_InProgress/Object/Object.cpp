#include "Object.hpp"

void Object::AttachObjectChild(Ref<Object> child)
{
    if(child.IsValidStrict())
    {
        obj_children.push_back(child);
        child->obj_parent = MemoryPool::CreateRef(this);
    }
}

void Object::DetachObjectChild(Ref<Object> child)
{
    auto r = std::find(obj_children.begin(), obj_children.end(), child);
    if(r != obj_children.end())
    {
        (*r)->obj_parent = Ref<Object>();
        obj_children.erase(r);
    }
}

std::vector<Ref<Object>> Object::DeepCollectObjectChildren()
{
    if(obj_children.size() == 0) return {};

    std::vector<Ref<Object>> t_children = obj_children;
    for (size_t i = 0; i < obj_children.size(); i++)
    {   
        auto r = obj_children[i]->DeepCollectObjectChildren();
        t_children.insert(t_children.end(), r.begin(), r.end());
    }
    return t_children;
}
