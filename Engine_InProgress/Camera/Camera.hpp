#ifndef CB2FE902_7E06_4D13_8DE0_5A9A792D5880
#define CB2FE902_7E06_4D13_8DE0_5A9A792D5880

#include "../ALLEGRO_DefaultInclude.hpp"
#include "../STD_DefaultInclude.hpp"
#include "../SceneManager/SceneManager.hpp"

class Camera : public SceneObject
{
private:
    ALLEGRO_TRANSFORM camera_offset_transform;
    InputComponent<Camera> input_component;

    float camera_zoom {1.0f};

public:
    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();

    void ZoomIn();
    void ZoomOut();

public:
    /**
     * @brief called once on object creation.
     */
    virtual void Begin();

    /**
     * @brief called every frame before Draw() function.
     * 
     * @param delta time between frames.
     */
    virtual void Update(float delta);

    /**
     * @brief called every frame after Update(). used to draw graphics.
     */
    virtual void Draw(float delta) final {
        al_draw_circle(transform.position.x, transform.position.y, 5.0f, EngineColors::red, 3.0f);
    };

    /**
     * @brief called once when object marked as pending kill. in other words - before destruction.
     */
    virtual void End(){};


public:
    Camera(const std::string& _obj_class, const ObjectSignature& obj_sign) : 
    SceneObject(_obj_class, obj_sign)
    {};
    virtual ~Camera(){};
};


#endif /* CB2FE902_7E06_4D13_8DE0_5A9A792D5880 */
