#ifndef EA15C8F6_35CB_4CB8_BA7F_74AEF3983547
#define EA15C8F6_35CB_4CB8_BA7F_74AEF3983547

#include "../STD_DefaultInclude.hpp"
#include "../Object/Object.hpp"

//number of kill candidates that triggers clear
#define GC_CLEAN_THRESHOLD 0
//max objects to clear per frame
#define GC_MAX_CLEAN_OBJECTS_THRESHOLD 10

/**
 * @brief Safe reference to ANY Object in game. This reference is managed by garbage collector and always will be safe to use.
 * 
 * @tparam T type
 */
template<class T>
class ObjRef
{
public:
    ObjRef()
    {
        is_obj_ptr_valid = nullptr;
        obj_ptr = nullptr;
    }

    ObjRef(T *ptr, std::shared_ptr<bool> validation_flag_ptr) :
    is_obj_ptr_valid(validation_flag_ptr), obj_ptr(ptr)
    {}

    ~ObjRef(){};

public:
    //returns current ref state.
    inline bool IsValid() { return *is_obj_ptr_valid; };
    //returns pointer to the stored object.
    inline T *operator->() { return obj_ptr; }

    inline bool operator==(const ObjRef &r) const
    {
       return (*obj_ptr) == (*(r.obj_ptr));
    }

    //disables reference. do not call this function by yourself.
    inline void Disable() { (*is_obj_ptr_valid) = false; };
    //free stored pointers. do not call this function by yourself.
    inline void Free()
    {
        delete obj_ptr;
    };
    //returns pointer to the validation flag.
    inline std::shared_ptr<bool> GetValidationPtr() { return is_obj_ptr_valid; };
    //returns pointer to the stored object.
    inline T *GetObjPtr() { return obj_ptr; };
    //returns ref count for object.
    inline long RefCount() { return is_obj_ptr_valid.use_count(); };
    //returns true if it is unique reference.
    inline bool IsUniqueRef() { return is_obj_ptr_valid.unique(); };
private:
    std::shared_ptr<bool> is_obj_ptr_valid; //validity flag.
    T *obj_ptr; //stored object.
};



class GarbageCollector
{
private:
    inline static std::vector<ObjRef<Object>> gc_objects_storage = {};
    inline static std::vector<ObjRef<Object>> gc_kill_candidates = {};
public:
    GarbageCollector(){};
    ~GarbageCollector(){};

    template<class T>
    static ObjRef<T> CreateObjectRef(T *obj_ptr)
    {
        if(obj_ptr == nullptr) return ObjRef<T>(nullptr, nullptr);

        //optional! please don't use any other classes except subclasses of an Object class
        // if(dynamic_cast<Object*>(obj_ptr) == nullptr) return ObjRef<T>(nullptr, nullptr);

        std::shared_ptr<bool> t = std::make_shared<bool>(new bool(true));
        gc_objects_storage.push_back(ObjRef<Object>(obj_ptr, t));
        return ObjRef<T>(obj_ptr, t);
    }

    template<class T>
    static ObjRef<T> FindByName(std::string name)
    {
        std::vector<ObjRef<Object>>::iterator result = std::find_if(gc_objects_storage.begin(), gc_objects_storage.end(),
        [name](ObjRef<Object> item){
            return item.IsValid() && item->GetObjName() == name;
        });
        if(result != gc_objects_storage.end())
            //this is dangerous point. if this candidate was NOT a subclass BEFORE here will be an error and core dump.
            //please, be carefull.
            return ObjRef<T>(dynamic_cast<T*>(result->GetObjPtr()), result->GetValidationPtr());
        else
            return ObjRef<T>(nullptr, nullptr);
    }

    template<class T>
    static ObjRef<T> FindByNameAndClass(std::string name, std::string base_class)
    {
        std::vector<ObjRef<Object>>::iterator result = std::find_if(gc_objects_storage.begin(), gc_objects_storage.end(),
        [name, base_class](ObjRef<Object> item){
            return item.IsValid() && item->GetObjName() == name && item->GetObjBaseClass() == base_class;
        });
        if(result != gc_objects_storage.end())
            //this is dangerous point. if this candidate was NOT a subclass BEFORE here will be an error and core dump.
            //please, be carefull.
            return ObjRef<T>(dynamic_cast<T*>(result->GetObjPtr()), result->GetValidationPtr());
        else
            return ObjRef<T>(nullptr, nullptr);
    }

    static void RegisterKillCandidate(ObjRef<Object> candidate);
    // template<class T>
    // static bool KillRef(ObjRef<T> ref)
    // {
    //     ref.Disable();
    // };

    static void CheckGarbage();
};


#endif /* EA15C8F6_35CB_4CB8_BA7F_74AEF3983547 */
