#ifndef D5E6C210_76AC_46A0_9BE9_3670C617CD86
#define D5E6C210_76AC_46A0_9BE9_3670C617CD86

#include "../STD_DefaultInclude.hpp"
#include "../Object/Object.hpp"
#include "../Memory/Memory.hpp"

enum ObjectFindMode
{
    Name = 0,
    Class = 1,
    Both = 2,
};

class ObjectManager
{
private:
    inline static uint64_t obj_last_id = 0;
public:
    ObjectManager(){};
    ~ObjectManager(){};

    template<class T>
    static ObjRef<T> CreateObject(std::string name, std::string base_class)
    {
        obj_last_id++;
        uint64_t timestamp = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        if(!MemoryPool::IsSpaceAvailable(base_class)) 
            return ObjRef<T>();
        T *p = new(base_class) T(name, timestamp, obj_last_id, base_class);
        if(p == nullptr)
            return ObjRef<T>();
        MemoryPool::SetupObject(p);
        return MemoryPool::CreateRef<T>(p);
    }

    template<class T>
    static ObjRef<T> FindObject(ObjectFindMode mode, std::string name = "", std::string base_class = "")
    {
        // switch (mode)
        // {
        // case ObjectFindMode::Name:
        //     return GarbageCollector::FindByName<T>(name);
        // case ObjectFindMode::Class:
        //     return GarbageCollector::FindByClass<T>(base_class);
        // case ObjectFindMode::Both:
        //     return GarbageCollector::FindByNameAndClass<T>(name, base_class);
        // default:
        //     return ObjRef<T>(nullptr, nullptr);
        // }
        return ObjRef<T>(nullptr, nullptr);
    }

    inline static void DestroyObject(ObjRef<Object> candidate)
    {   
        // candidate->MarkPendingKill();
        MemoryPool::FreeObject(candidate.GetObjPtr());
    };
};


#endif /* D5E6C210_76AC_46A0_9BE9_3670C617CD86 */