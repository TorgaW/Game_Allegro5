#include "SceneObject.h"

ASceneObject::ASceneObject(uint32_t id, uint64_t timestamp, std::string name, std::string static_class_name) : AObject(id, timestamp, name, static_class_name)
{
}

ASceneObject::~ASceneObject()
{
}