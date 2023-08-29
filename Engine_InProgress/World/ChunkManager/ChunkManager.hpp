#ifndef D3852824_B6A9_4460_846A_556477194421
#define D3852824_B6A9_4460_846A_556477194421

#include "../../STD_DefaultInclude.hpp"
#include "../../ALLEGRO_DefaultInclude.hpp"
#include "../../Transforms/Transform.hpp"
#include "../../SceneManager/SceneManager.hpp"
#include "../Chunk/Chunk.hpp"

class ChunkManager : public SceneObject
{
private:
    // std::vector<Ref<Chunk>> loaded_chunks;
    int chunks_draw_distance = 3;
    int chunks_in_square_line = 0;
    float far_chunks_distance_mul = 2.0f;
    std::map<Vec2i, Ref<Chunk>, Vec2MapComprasion> loaded_chunks;
    std::map<Vec2i, Ref<Chunk>, Vec2MapComprasion> pre_loaded_chunks;
    std::map<Vec2i, Ref<Chunk>, Vec2MapComprasion> visible_chunks;
    std::vector<Vec2i> chunk_generation_queue;
    uint16_t chunks_per_frame_generation = 1;
    uint16_t last_draw_chunk_counter = 0;
    Vec2 camera_last_position = {1000, 1000};
    int frames_past = 0;
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

private:

    void UpdateChunksVisibility();
    void DrawBufferedChunks();

public:
    ChunkManager(const std::string& _obj_class, const ObjectSignature& obj_sign) : 
    SceneObject(_obj_class, obj_sign)
    {};
    virtual ~ChunkManager(){};
};


#endif /* D3852824_B6A9_4460_846A_556477194421 */
