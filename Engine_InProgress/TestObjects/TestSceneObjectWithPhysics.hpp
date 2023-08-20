#ifndef E1859261_D186_4D58_96F6_8AE372DE96A3
#define E1859261_D186_4D58_96F6_8AE372DE96A3

#include "../STD_DefaultInclude.hpp"
#include "../ALLEGRO_DefaultInclude.hpp"
#include "../SceneManager/SceneManager.hpp"
#include "../Physics/PhysicsComponent.hpp"

class TestSceneObjectWithPhysics : public SceneObject
{
private:
    PhysicsComponent<TestSceneObjectWithPhysics> physics;
public:
    /**
     * @brief called once on object creation.
     */
    virtual void Begin()
    {
        physics.SetParent(this);
        physics.velocity = {0.0f, 0.0f};
        physics.mass = 20.0f;
        physics.damping = 0.3f;
    };

    /**
     * @brief called every frame before Draw() function.
     * 
     * @param delta time between frames.
     */
    virtual void Update(float delta)
    {
        physics.UpdatePhysics(delta);
    };

    /**
     * @brief called every frame after Update(). used to draw graphics.
     */
    virtual void Draw(float delta)
    {
        al_draw_circle(transform.position.x, transform.position.y, 40.0f, EngineColors::cyan, 5.0f);
    };

    /**
     * @brief called once when object marked as pending kill. in other words - before destruction.
     */
    virtual void End(){};

public:
    TestSceneObjectWithPhysics(const std::string& _obj_class, const ObjectSignature& obj_sign) : 
    SceneObject(_obj_class, obj_sign)
    {};
    virtual ~TestSceneObjectWithPhysics(){};
};


#endif /* E1859261_D186_4D58_96F6_8AE372DE96A3 */
