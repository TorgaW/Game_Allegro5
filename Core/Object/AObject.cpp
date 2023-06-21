#include "AObject.h"

AObject::AObject(uint32_t id, uint64_t timestamp, std::string name, std::string static_class_name)
{
    Id = id;
    TimeStamp = timestamp;
    Name = name;
    StaticClassName = static_class_name;
    bDestroyed = false;
}

AObject::~AObject()
{
}

void AObject::Begin()
{
}

void AObject::End()
{
}

void AObject::GTick(float delta_time)
{
}

void AObject::Tick(float delta_time)
{
    CurrentDeltaTime = delta_time;
}