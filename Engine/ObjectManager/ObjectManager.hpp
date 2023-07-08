#ifndef D5E6C210_76AC_46A0_9BE9_3670C617CD86
#define D5E6C210_76AC_46A0_9BE9_3670C617CD86

#include "../STD_DefaultInclude.hpp"
#include "../Object/Object.hpp"
#include "../GarbageCollector/GarbageCollector.hpp"

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
        T *p = new T(name, timestamp, obj_last_id, base_class);
        return GarbageCollector::CreateObjectRef<T>(p);
    }

    template<class T>
    static ObjRef<T> FindObject(std::string name, std::string base_class = "")
    {
        if(base_class == "")
            return GarbageCollector::FindByName<T>(name);
        else
            return GarbageCollector::FindByNameAndClass<T>(name, base_class);
    }

    inline static void DestroyObject(ObjRef<Object> candidate)
    {   
        candidate->MarkPendingKill();
        GarbageCollector::RegisterKillCandidate(candidate);
    };
};


#endif /* D5E6C210_76AC_46A0_9BE9_3670C617CD86 */
