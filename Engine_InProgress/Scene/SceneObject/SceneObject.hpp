#ifndef CE79605F_E73D_48C3_8A6E_25D5E93A6B75
#define CE79605F_E73D_48C3_8A6E_25D5E93A6B75

#include "../../ObjectManager/ObjectManager.hpp"
#include "../../Transforms/Transform.hpp"

class SceneObject : public Object
{
public:
    Transform2 transform {};
    bool IsOnScene {false};
    bool IsHidden {false};
public:
    //constructor
    SceneObject(const std::string& base_class, ObjectSignature obj_sign) : 
    Object(base_class, obj_sign)
    {};
    //must be virtual destructor
    virtual ~SceneObject(){};

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


#endif /* CE79605F_E73D_48C3_8A6E_25D5E93A6B75 */
