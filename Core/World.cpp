#include "World.h"

World::World()
{
    WorldScene = new AScene();
}

World::~World()
{
    delete WorldScene;
}

void World::AddToWorld(AObject *obj)
{
    WorldScene->AddObject(obj);
}

void World::AddToWorld(ASceneObject *obj)
{
    WorldScene->AddObject(obj);
}

void World::RemoveFromWorld(AObject *obj)
{
    WorldScene->RemoveObject(obj);
}

void World::RemoveFromWorld(ASceneObject *obj)
{
    WorldScene->RemoveObject(obj);
}

void World::UpdateScene()
{
    WorldScene->UpdateScene();
}

AScene *World::GetScene()
{
    return WorldScene;
}

Viewport *World::GetViewport()
{
    return WorldScene->GetViewport();
}

Profiler *World::GetProfiler()
{
    return WorldScene->GetViewport()->GetProfiler();
}
