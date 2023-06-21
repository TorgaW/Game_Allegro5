#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <vector>
#include <chrono>
#include "../Object/AObject.h"
#include "../Statics/Statics.h"

class ObjectManager
{
public:
    static ObjectManager &Get()
    {
        static ObjectManager instance;
        return instance;
    }

private:
    ObjectManager() {
        ObjectCounter = 0;
    }                     
public:
    ObjectManager(ObjectManager const &) = delete;
    void operator=(ObjectManager const &) = delete;

    inline void DecObjCounter()
    {
        ObjectCounter--;
    }

private:
    uint32_t ObjectCounter;

public:
    template <class T>
    T *CreateObject(std::string name, std::string static_class_name)
    {
        if (std::find(Statics::StaticClassNames.begin(), Statics::StaticClassNames.end(), static_class_name) != Statics::StaticClassNames.end())
        {
            ObjectCounter++;
            uint64_t timestamp = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            T *p = new T(ObjectCounter, timestamp, name, static_class_name);
            return p;
        }
        else
        {
            return nullptr;
        }
    }
};

#endif