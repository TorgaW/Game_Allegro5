#ifndef D5E6C210_76AC_46A0_9BE9_3670C617CD86
#define D5E6C210_76AC_46A0_9BE9_3670C617CD86

#include "../STD_DefaultInclude.hpp"
#include "../Object/Object.hpp"
#include "../Memory/Memory.hpp"

// enum ObjectFindMode
// {
//     _Name = 0,
//     _Class = 1,
//     _Both = 2,
// };

class ObjectManager
{
private:
    inline static uint64_t obj_last_id = 0;
public:
    ObjectManager(){};
    ~ObjectManager(){};

    template<class T>
    static Ref<T> CreateObject(const std::string& name, const std::string& obj_class)
    {
        if(!MemoryPool::IsSpaceAvailable(obj_class)) 
            return Ref<T>();
        obj_last_id++;
        uint64_t timestamp = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        ObjectSignature sg(name, timestamp, obj_last_id);

        T *p = new(obj_class) T(obj_class, sg);
        if(p == nullptr)
            return Ref<T>();
        MemoryPool::SetupObject(p);
        return MemoryPool::CreateRef<T>(p);
    }

    template<class T>
    static Ref<T> CopyObject(Ref<T> candidate, std::string name)
    {
        if(!MemoryPool::IsSpaceAvailable(candidate.GetObjPtr()->GetClass())) 
            return Ref<T>();
        obj_last_id++;
        uint64_t timestamp = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        ObjectSignature sg(name, timestamp, obj_last_id);

        T *p = new(candidate.GetObjPtr()->GetClass()) T(*(candidate.GetObjPtr()));
        if(p == nullptr)
            return Ref<T>();
        MemoryPool::SetupObject(p);
        p->SetSignature(sg);
        return MemoryPool::CreateRef<T>(p);
    }

    // template<class T>
    // static Ref<T> FindObject(ObjectFindMode mode, std::string name = "", std::string obj_class = "")
    // {
        // switch (mode)
        // {
        // case ObjectFindMode::Name:
        //     return GarbageCollector::FindByName<T>(name);
        // case ObjectFindMode::Class:
        //     return GarbageCollector::FindByClass<T>(obj_class);
        // case ObjectFindMode::Both:
        //     return GarbageCollector::FindByNameAndClass<T>(name, obj_class);
        // default:
        //     return Ref<T>(nullptr, nullptr);
        // }
    //     return Ref<T>(nullptr, nullptr);
    // }

    template<class T>
    static inline bool DestroyObject(Ref<T> candidate)
    {   
        // candidate->MarkPendingKill();
        // return MemoryPool::FreeObject(candidate.GetObjPtr());
        if(candidate.IsValidStrict())
        {
            auto t = candidate->DeepCollectObjectChildren();
            for (size_t i = 0; i < t.size(); i++)
            {
                MemoryPool::FreeObject(t[i].GetObjPtr());
            }
            MemoryPool::FreeObject(candidate.GetObjPtr());
            return true;
        }
        return false;
    };
};


#endif /* D5E6C210_76AC_46A0_9BE9_3670C617CD86 */
