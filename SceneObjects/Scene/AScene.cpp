#include "AScene.h"

AScene::AScene()
{
}

AScene::~AScene()
{
}

void AScene::AddObject(AObject *obj)
{
    obj->Begin();
    TickBuffer.push_back(obj);
}

void AScene::AddObject(ASceneObject *obj)
{
    obj->Begin();
    TickBuffer.push_back(obj);
    GraphicsBuffer.push_back(obj);
}

void AScene::RemoveObject(AObject *obj)
{
    TickBuffer.erase(std::remove_if(TickBuffer.begin(), TickBuffer.end(), [obj](AObject *t){
        return (obj->GetId() == t->GetId() && obj->GetTimeStamp() == t->GetTimeStamp() && obj->GetName() == t->GetName() && obj->GetStaticClassName() == t->GetStaticClassName());
    }), TickBuffer.end());
    obj->DestroyObject();
    ObjectManager::Get().DecObjCounter();
}

void AScene::RemoveObject(ASceneObject *obj)
{
    TickBuffer.erase(std::remove_if(TickBuffer.begin(), TickBuffer.end(), [obj](AObject *t){
        return (obj->GetId() == t->GetId() && obj->GetTimeStamp() == t->GetTimeStamp() && obj->GetName() == t->GetName() && obj->GetStaticClassName() == t->GetStaticClassName());
    }), TickBuffer.end());
    GraphicsBuffer.erase(std::remove_if(GraphicsBuffer.begin(), GraphicsBuffer.end(), [obj](AObject *t){
        return (obj->GetId() == t->GetId() && obj->GetTimeStamp() == t->GetTimeStamp() && obj->GetName() == t->GetName() && obj->GetStaticClassName() == t->GetStaticClassName());
    }), GraphicsBuffer.end());
    obj->DestroyObject();
    ObjectManager::Get().DecObjCounter();
}

void AScene::SetMainCamera(Camera *cam)
{
    MainCamera = cam;
}

Camera *AScene::GetMainCamera()
{
    return MainCamera;
}

void AScene::UpdateScene()
{
    if(MainCamera)
        MainCamera->Tick(Render::Get().GetDeltaTime());
    for (size_t i = 0; i < TickBuffer.size(); i++)
    {
        TickBuffer[i]->Tick(Render::Get().GetDeltaTime());
    }

    Render::Get().DrawScreen(&GraphicsBuffer, UIViewPort);
}
