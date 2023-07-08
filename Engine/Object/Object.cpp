#include "Object.hpp"

void Object::MarkPendingKill()
{
    obj_pending_kill = true;
    if(obj_children.size() > 0)
    {
        for (size_t i = 0; i < obj_children.size(); i++)
            obj_children[i]->MarkPendingKill();
    }
    End();
}
