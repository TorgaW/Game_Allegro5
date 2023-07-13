#ifndef E2038523_372C_4CC2_88A6_FA2D2941877C
#define E2038523_372C_4CC2_88A6_FA2D2941877C

#include "../ObjectManager/ObjectManager.hpp"
#include "../Lib/Transform/Transform.hpp"

class SceneObject : public Object
{
public:
    //constructor
    SceneObject(std::string name, uint64_t timestamp, uint64_t id, std::string base_class) : 
    Object(name, timestamp, id, base_class)
    {};
    //must be virtual destructor
    virtual ~SceneObject(){};

public:
    Transform transform {};
    bool IsHiddenInGame {false};

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
    virtual void Update(double delta){};

    /**
     * @brief called every frame after Update() function.
     * 
     * @param delta time between frames.
     */
    virtual void Draw(double delta){};

    /**
     * @brief called once when object marked as pending kill. in other words - before destruction.
     */
    virtual void End(){};
};


#endif /* E2038523_372C_4CC2_88A6_FA2D2941877C */
