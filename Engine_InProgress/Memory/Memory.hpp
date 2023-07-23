#ifndef C0C80310_75D0_4942_BA31_0153B10CB3E4
#define C0C80310_75D0_4942_BA31_0153B10CB3E4

#include <memory>
#include <string>
#include <map>
#include <vector>

//special alloc options for specific classes
//{name, max_objects}
const std::map<std::string, size_t> mem_alloc_options = {
    {"class_Object", 50000u}
};

//default alloc option
const size_t mem_alloc_default_value = 100u;

/**
 * @brief Safe reference to ANY Object in game. This reference is managed by garbage collector and always will be safe to use.
 * 
 * @tparam T type
 */
template<class T>
class Ref
{
public:
    Ref()
    {
        is_obj_ptr_valid = nullptr;
        obj_ptr = nullptr;
    }

    Ref(T *ptr, bool *validation_flag_ptr, size_t _hash) :
    is_obj_ptr_valid(validation_flag_ptr), obj_ptr(ptr), hash(_hash)
    {}

    ~Ref(){};

    template<class F>
    Ref(Ref<F>& rhs)
    {
        is_obj_ptr_valid = rhs.GetValidationPtr();
        obj_ptr = static_cast<T*>(rhs.GetObjPtr());
        hash = rhs.GetHash();
    }

public:
    //returns current ref state. can be falsy positive if new object allocated on the same place in memory.
    inline bool IsValid() { return is_obj_ptr_valid == nullptr ? false : !(*is_obj_ptr_valid); };

    //returns current ref state. can not be falsy positive but a bit slower.
    inline bool IsValidStrict() { return is_obj_ptr_valid == nullptr ? false : (!(*is_obj_ptr_valid) && obj_ptr->GetHash() == hash); };

    inline size_t GetHash() { return hash; };

    //returns pointer to the stored object.
    inline T *operator->() { return obj_ptr; };

    inline bool operator==(const Ref &r) const
    {
       return (*obj_ptr) == (*(r.obj_ptr));
    };

    //disables reference. do not call this function by yourself.
    // inline void Disable() { (*is_obj_ptr_valid) = false; };
    //free stored pointers. do not call this function by yourself.
    // inline void Free()
    // {
        // delete obj_ptr;
    // };
    //returns pointer to the validation flag.
    inline bool *GetValidationPtr() { return is_obj_ptr_valid; };
    //returns pointer to the stored object.
    inline T *GetObjPtr() { return obj_ptr; };
    //returns ref count for object.
    // inline long RefCount() { return is_obj_ptr_valid.use_count(); };
    //returns true if it is unique reference.
    // inline bool IsUniqueRef() { return is_obj_ptr_valid.unique(); };
private:
    bool *is_obj_ptr_valid; //validity flag.
    T *obj_ptr; //stored object.
    size_t hash {0u};
};

/**
 * @brief Arena allocator class for every type of game object.
 * Memory allocates continiously to fit in CPU cache
 * and reduce cache misses.
 */
class ObjectMemPool
{
public:
    char *begin {nullptr}; //points to the begging of the chunk.
    char *end {nullptr}; //points to the end of the chunk.
    char *iterator {nullptr}; //can be used to iterate through chunk.
    size_t byte_size {0u}; //size of storing class in bytes.
    // std::vector<bool> b_array; //indicators for allocation.
    bool *b_array; //indicators for allocation.
    size_t max_objects {0u};
    size_t allocated {0u};
    size_t last_allocated {0u}; //index of the last allocated object
public:
    ObjectMemPool(){};
    ~ObjectMemPool(){};

    inline bool IsFull() { return allocated == max_objects; };

    //allocates memory for n objects
    void Allocate(std::string obj_class, size_t class_size);

    //get pointer to free space
    void *AllocateObject();

    //mark cell as free object
    template<class _T>
    bool FreeObject(_T *object_ptr)
    {
        if(object_ptr->GetMemStorageIndex() < 0) return false;
        b_array[object_ptr->GetMemStorageIndex()] = true;
        allocated--;
        return true;
    }

    // void *IterateForward();

    template<class _T>
    bool SetupObject(_T *obj_ptr)    
    {
        for (size_t i = 0; i < max_objects; i++)
        {
            if(!b_array[i] && *((_T*)(begin + byte_size*i)) == *obj_ptr)
            {
                obj_ptr->SetMemStorageIndex(i);
                return true;
            }
        }
        return false;
    }

    template<class _T>
    Ref<_T> CreateRef(_T *obj_ptr)
    {
        for (size_t i = 0; i < max_objects; i++)
        {
            if(!b_array[i] && *((_T*)(begin + byte_size*i)) == *obj_ptr)
            {
                return Ref<_T>(obj_ptr, b_array+i, obj_ptr->GetHash());
            }
        }
        return Ref<_T>();
    }

    void PrintData(){};
};

class MemoryPool
{
private:
    inline static std::map<std::string, ObjectMemPool> object_pools {};
public:
    MemoryPool(){};
    ~MemoryPool(){};

    static void *AllocateObject(std::string obj_class, size_t class_size)
    {
        auto mem_pool = object_pools.find(obj_class);
        if(mem_pool != object_pools.end())
        {
            return (mem_pool->second.AllocateObject());
        }
        else
        {
            object_pools.insert({obj_class, ObjectMemPool()});
            object_pools[obj_class].Allocate(obj_class, class_size);
            return (object_pools[obj_class].AllocateObject());
        }
    }

    template<class T>
    static bool FreeObject(T *obj_ptr)
    {
        auto mem_pool = object_pools.find(obj_ptr->GetClass());
        if(mem_pool != object_pools.end())
            return mem_pool->second.FreeObject(obj_ptr);
        else
            return false;
    }

    template<class T>
    static bool SetupObject(T *obj_ptr)
    {
        auto mem_pool = object_pools.find(obj_ptr->GetClass());
        if(mem_pool != object_pools.end())
            return mem_pool->second.SetupObject(obj_ptr);
        else
            return false;
    }

    template<class T>
    static Ref<T> CreateRef(T *obj_ptr)
    {
        auto mem_pool = object_pools.find(obj_ptr->GetClass());
        if(mem_pool != object_pools.end())
            return mem_pool->second.CreateRef(obj_ptr);
        else
            return Ref<T>();
    }

    static bool IsSpaceAvailable(std::string obj_class);

};

#endif /* C0C80310_75D0_4942_BA31_0153B10CB3E4 */
