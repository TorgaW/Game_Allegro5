#include "QuadTree.hpp"

QT_Rect::QT_Rect(Rect2 source)
{
    center = source.GetCenter();
    half_size = source.GetWidth() / 2.0f;
    left = center.x - half_size;
    right = center.x + half_size;
    top = center.y - half_size;
    bottom = center.y + half_size;
}

QT_Rect::QT_Rect(Vec2 _center, float _half_size)
{
    center = _center;
    half_size = _half_size;
    left = center.x - half_size;
    right = center.x + half_size;
    top = center.y - half_size;
    bottom = center.y + half_size;
}

void QT_Rect::SetFromRect2(Rect2 source)
{
    center = source.GetCenter();
    half_size = source.GetWidth() / 2.0f;
    left = center.x - half_size;
    right = center.x + half_size;
    top = center.y - half_size;
    bottom = center.y + half_size;
}

Rect2 QT_Rect::ToRect2()
{
    return Rect2({center.x - half_size, center.y - half_size},{half_size});
}

bool QT_Rect::ContainsPoint(Vec2 p)
{
    return (left <= p.x && 
            p.x <= right &&
            top <= p.y &&
            p.y <= bottom);
}

bool QT_Rect::IntersectsWithRect(QT_Rect other_rect)
{
    return !(right < other_rect.left ||
            other_rect.right < left ||
            bottom < other_rect.bottom ||
            other_rect.bottom < bottom);
}

void QuadTree::Subdivide()
{
    north_west = new QuadTree({{boundary.center.x - boundary.half_size/2.0f, 
                                boundary.center.y - boundary.half_size/2.0f}, 
                                boundary.half_size/2.0f});

    north_east = new QuadTree({{boundary.center.x + boundary.half_size/2.0f, 
                                boundary.center.y - boundary.half_size/2.0f}, 
                                boundary.half_size/2.0f});

    south_west = new QuadTree({{boundary.center.x - boundary.half_size/2.0f, 
                                boundary.center.y + boundary.half_size/2.0f}, 
                                boundary.half_size/2.0f});

    south_east = new QuadTree({{boundary.center.x + boundary.half_size/2.0f, 
                                boundary.center.y + boundary.half_size/2.0f}, 
                                boundary.half_size/2.0f});

    is_subdivided = true;
}

bool QuadTree::InsertPoint(Vec2 point)
{
    if(!boundary.ContainsPoint(point)) return false;

    if(points.size() < qt_capacity && north_west == nullptr)
    {
        points.push_back(point);
        return true;
    }

    if(north_west == nullptr) Subdivide();

    if(north_west->InsertPoint(point)) return true;
    if(north_east->InsertPoint(point)) return true;
    if(south_west->InsertPoint(point)) return true;
    if(south_east->InsertPoint(point)) return true;

    return false;
}

void QuadTree::RemoveInRange(QT_Rect range)
{
    if(north_west != nullptr)
    {
        north_west->RemoveInRange(range);
        north_east->RemoveInRange(range);
        south_west->RemoveInRange(range);
        south_east->RemoveInRange(range);
    }

    points.erase(std::remove_if(points.begin(), points.end(),
    [&](Vec2 p)
    {
        return range.ContainsPoint(p);
    }), points.end());
}

void QuadTree::RemoveInRange(Rect2 range)
{
    QT_Rect r(range);
    RemoveInRange(r);
}

void QuadTree::RemovePoint(Vec2 point)
{
    auto f = std::find(points.begin(), points.end(), point);
    if(f != points.end())
    {
        points.erase(f);
        return;
    }
    else if(north_west != nullptr)
    {
        north_west->RemovePoint(point);
        north_east->RemovePoint(point);
        south_west->RemovePoint(point);
        south_east->RemovePoint(point);
    }
}

std::vector<Vec2> QuadTree::Query(QT_Rect range)
{   
    std::vector<Vec2> points_in_range;
    if(!range.IntersectsWithRect(range)) return points_in_range;

    for (size_t i = 0; i < points.size(); i++)
    {
        if(range.ContainsPoint(points[i])) 
            points_in_range.push_back(points[i]);
    }
    
    if(north_west == nullptr)
        return points_in_range;

    std::vector<Vec2> t = north_west->Query(range);
    points_in_range.insert(points_in_range.end(), t.begin(), t.end());
    t = north_east->Query(range);
    points_in_range.insert(points_in_range.end(), t.begin(), t.end());
    t = south_west->Query(range);
    points_in_range.insert(points_in_range.end(), t.begin(), t.end());
    t = south_east->Query(range);
    points_in_range.insert(points_in_range.end(), t.begin(), t.end());

    return points_in_range;
}

std::vector<Vec2> QuadTree::Query(Rect2 range)
{   
    QT_Rect r(range);
    return Query(r);
}

void QuadTree::Clear()
{
    if(is_cleared) return;
    if(north_west != nullptr)
    {
        north_west->Clear();
        north_east->Clear();
        south_west->Clear();
        south_east->Clear();
    }
    delete north_west;
    delete north_east;
    delete south_west;
    delete south_east;
    is_cleared = true;
}

void QuadTree::DebugQuadTree()
{
    al_draw_rectangle(boundary.GetP00().x, boundary.GetP00().y, boundary.GetP11().x, boundary.GetP11().y, EngineColors::magenta, 3.0f);
    if(is_subdivided)
    {
        north_west->DebugQuadTree();
        north_east->DebugQuadTree();
        south_west->DebugQuadTree();
        south_east->DebugQuadTree();
    }
}

QuadTree::~QuadTree()
{
    Clear();
}
