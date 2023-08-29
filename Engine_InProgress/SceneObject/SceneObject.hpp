#ifndef B3E0A448_3FB6_4A41_B01B_7A33C2BA2112
#define B3E0A448_3FB6_4A41_B01B_7A33C2BA2112

#include "../Object/Object.hpp"
#include "../ALLEGRO_DefaultInclude.hpp"
#include "../Transforms/Transform.hpp"
#include "../BitmapManager/BitmapManager.hpp"

class SceneObject : public Object
{
private:
    Shader* scene_object_shader {nullptr};
    Bitmap* scene_object_bitmap {nullptr};

public:

    Transform transform;
    Rect2 bounds;

    Vec2i chain_chunk_id;
    bool in_chunk {false};

    bool is_object_hidden {false};

    bool is_affect_update {true};

    bool is_on_scene {false};

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
     * @brief called every frame after Update(). used to draw graphics.
     */
    virtual void Draw(float delta){};

    /**
     * @brief called once when object marked as pending kill. in other words - before destruction.
     */
    virtual void End(){};

public:
    SceneObject(const std::string& _obj_class, const ObjectSignature& obj_sign) : 
    Object(_obj_class, obj_sign)
    {};
    virtual ~SceneObject(){};
};


#endif /* B3E0A448_3FB6_4A41_B01B_7A33C2BA2112 */
