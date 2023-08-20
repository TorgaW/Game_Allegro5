#ifndef A35E4B27_DFFE_4AB2_A1CF_C6E89A5848C5
#define A35E4B27_DFFE_4AB2_A1CF_C6E89A5848C5

#include "../../STD_DefaultInclude.hpp"
#include "../../ALLEGRO_DefaultInclude.hpp"
#include "../Chunk/Chunk.hpp"
#include "../../SceneManager/SceneManager.hpp"

class WorldLoader : public SceneObject
{
private:
    // std::vector<Chunk> local_chunks {};
    std::map<Vec2i, Chunk*, Vec2MapComprasion> loaded_chunks {};
    // std::vector<Chunk*> unloaded_chunks {};
    std::map<Vec2i, Chunk*, Vec2MapComprasion> visible_chunks {};
    int chunks_draw_distance {3};
    float far_chunks_mult {2.0f};
    int chunk_square_axis_size {0}; //how many chunks in horizontal line
    static inline float chunk_size {512.0f};
    static inline float chunk_draw_scale {4.0f};

    Vec2 last_spotted_camera_position {100000.0f, 100000.0f};
    float camera_max_delta_trigger = 256.0f; // 1/4 of the chunk

    std::vector<Ref<SceneObject>> objects_buffer;
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
    virtual void Draw(float delta);

    /**
     * @brief called once when object marked as pending kill. in other words - before destruction.
     */
    virtual void End(){};

public:
    void DebugChunks();

    static Vec2i GetChunkId(Vec2 position);

    void AddObjectToWorld(Ref<SceneObject> object);

public:
    WorldLoader(const std::string& _obj_class, const ObjectSignature& obj_sign) : 
    SceneObject(_obj_class, obj_sign)
    {};
    virtual ~WorldLoader(){};
};


#endif /* A35E4B27_DFFE_4AB2_A1CF_C6E89A5848C5 */
