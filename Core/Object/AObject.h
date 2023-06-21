#ifndef AOBJECT_H
#define AOBJECT_H

#include <cstdint>
#include <string>
class AObject
{
protected:
    uint32_t Id;
    uint64_t TimeStamp;
    std::string Name;
    std::string StaticClassName;
    bool bDestroyed;
    float CurrentDeltaTime;
public:
    AObject(uint32_t id, uint64_t timestamp, std::string name, std::string static_class_name);
    virtual ~AObject();

    virtual void Begin();
    virtual void End();
    virtual void GTick(float delta_time);
    virtual void Tick(float delta_time);

    inline uint32_t GetId(){ return Id; }
    inline uint64_t GetTimeStamp() { return TimeStamp; }
    inline std::string GetName() { return Name; }
    inline std::string GetStaticClassName() { return StaticClassName; }
    inline void DestroyObject()
    {
        if(!bDestroyed)
        {
            bDestroyed = true;
            End();
        }
    }
    inline bool isDestroyed() { return bDestroyed; }
};

#endif