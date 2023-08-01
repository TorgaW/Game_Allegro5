#include "Transform.hpp"

float VecMath::Distance(Vec2 a, Vec2 b)
{
    return (a-b).Length();
}

float VecMath::Distance(Transform a, Transform b)
{
    return (a.position - b.position).Length();
}
