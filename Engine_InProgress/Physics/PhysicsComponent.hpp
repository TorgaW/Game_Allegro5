#ifndef C7C29B2F_1740_4CC9_8A52_22C813A31BB8
#define C7C29B2F_1740_4CC9_8A52_22C813A31BB8

#include "../STD_DefaultInclude.hpp"
#include "../Transforms/Transform.hpp"

template <class T>
class PhysicsComponent
{
private:
    T *ptr_parent {nullptr};
public:
    Vec2 velocity;

    //in kg
    float mass {0.0f};

    //between 0.0 and 1.0 (0.0 <= damping < 1.0)
    float damping {1.0f};

    void SetParent(T *parent)
    {
        ptr_parent = parent;
    };

    PhysicsComponent(){};
    PhysicsComponent(T *parent) : ptr_parent(parent){};
    ~PhysicsComponent(){};

    void UpdatePhysics(float delta_time)
    {
        velocity = velocity * (std::pow(1.0f - damping, delta_time * mass * 0.1f));
        ptr_parent->transform.position = ptr_parent->transform.position + velocity * delta_time * (1.0f / mass);
    }
    
    // void ApplyForce();
};


#endif /* C7C29B2F_1740_4CC9_8A52_22C813A31BB8 */
