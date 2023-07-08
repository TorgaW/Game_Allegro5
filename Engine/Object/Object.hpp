#ifndef B09A8BC6_B336_4159_86D4_9AE3569B6AB6
#define B09A8BC6_B336_4159_86D4_9AE3569B6AB6

#include "../STD_DefaultInclude.hpp"
// #include "../GarbageCollector/GarbageCollector.hpp"

// class GarbageCollector;

class Object
{
public:
    //constructor
    Object(std::string name, uint64_t timestamp, uint64_t id, std::string base_class) : 
    obj_name(name), obj_timestamp(timestamp), obj_id(id), obj_base_class(base_class) 
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
     * @brief called every frame after Update() function.
     * 
     * @param delta time between frames.
     */
    virtual void Draw(float delta){};

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
    inline std::string GetObjName() { return obj_name; };
    //get object timestamp.
    inline uint64_t GetObjTimestamp() { return obj_timestamp; };
    //get object id.
    inline uint64_t GetObjId() { return obj_id; };
    //get object base class.
    inline std::string GetObjBaseClass() { return obj_base_class; };

public:
    
    //called to prepare object for destruction
    void MarkPendingKill();

    inline bool IsMarkedPendingKill() { return obj_pending_kill; };

//operators
public:
    inline bool operator==(const Object &b) const
    {
        return b.obj_id == obj_id && b.obj_timestamp == obj_timestamp && 
               b.obj_name == b.obj_name && b.obj_base_class == obj_base_class;
    }

protected:
    std::string obj_name;
    uint64_t obj_timestamp;
    uint64_t obj_id;
    std::string obj_base_class;
    Object *obj_parent {nullptr};
    std::vector<Object*> obj_children;
    bool obj_pending_kill{false};
};

#endif /* B09A8BC6_B336_4159_86D4_9AE3569B6AB6 */
