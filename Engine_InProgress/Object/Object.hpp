#ifndef B09A8BC6_B336_4159_86D4_9AE3569B6AB6
#define B09A8BC6_B336_4159_86D4_9AE3569B6AB6

#include "../STD_DefaultInclude.hpp"
#include "../Memory/Memory.hpp"
// #include "../GarbageCollector/GarbageCollector.hpp"

// class GarbageCollector;

struct ObjectSignature
{
    std::string obj_name;
    uint64_t obj_timestamp;
    uint64_t obj_id;
    size_t obj_hash {0u};
    ObjectSignature(const std::string& name, uint64_t timestamp, uint64_t id) :
    obj_name(name), obj_timestamp(timestamp), obj_id(id), obj_hash(timestamp+id)
    {};

    inline bool operator==(const ObjectSignature& b) const
    {
        return obj_name == b.obj_name && obj_hash == b.obj_hash;
    }
};

// struct ObjectMetaData
// {
//     int obj_storage_index {-1};
//     int obj_scene_index
// };

class Object
{
public:
    //constructor
    Object(const std::string& _obj_class, const ObjectSignature& obj_sign) : 
    obj_class(_obj_class), obj_signature(obj_sign)
    {};
    //must be virtual destructor
    virtual ~Object(){};

public:
    /**
     * @brief called once on object creation.
     */
    virtual void Begin(){};

    /**
     * @brief called every frame before Draw() function.
     * 
     * @param delta time between frames.
     */
    virtual void Update(float delta){};

    /**
     * @brief called once when object marked as pending kill. in other words - before destruction.
     */
    virtual void End(){};

    // LEGACY
    // /**
    //  * @brief called on garbage collector event. 
    //  * please, check all references on objects in this method, they must not be marked as pending kill. 
    //  * otherwise reference error will happen! 
    //  */
    // virtual void GarbageCollection(){};
    // LEGACY

public:
    //get object name.
    inline std::string GetName() { return obj_signature.obj_name; };
    //get object timestamp.
    inline uint64_t GetTimestamp() { return obj_signature.obj_timestamp; };
    //get object id.
    inline uint64_t GetId() { return obj_signature.obj_id; };
    //get object base class.
    inline std::string GetClass() { return obj_class; };

    inline int GetMemStorageIndex() { return obj_storage_index; };

    inline void SetMemStorageIndex(int i) { obj_storage_index = i; };

    inline size_t GetHash() { return obj_signature.obj_hash; };

    inline void SetHash(size_t hash) { obj_signature.obj_hash = hash; };

    inline void SetSignature(const ObjectSignature _new_sign) { obj_signature = _new_sign; };

public:
    
    //called to prepare object for destruction
    // void MarkPendingKill();

    // inline bool IsMarkedPendingKill() { return obj_pending_kill; };

    //do not override this method
    virtual void CallBegin()
    {
        if(begin_done) return;
        Begin();
        begin_done = true;
    };

//operators
public:
    inline bool operator==(const Object &b) const
    {
        return obj_signature == b.obj_signature && b.obj_class == obj_class &&
               b.obj_storage_index == obj_storage_index;
    }

    void *operator new(size_t n, const std::string& _obj_class)
    {
        return MemoryPool::AllocateObject(_obj_class, n);
    }

protected:
    // std::string obj_name;
    // uint64_t obj_timestamp;
    // uint64_t obj_id;
    ObjectSignature obj_signature;
    std::string obj_class;
    // Object *obj_parent {nullptr};
    // std::vector<Object*> obj_children;
    // bool obj_pending_kill{false};
    int obj_storage_index {-1};

private:
    bool begin_done {false};
};

#endif /* B09A8BC6_B336_4159_86D4_9AE3569B6AB6 */
