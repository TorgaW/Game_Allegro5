#ifndef D12574FD_AEB1_4040_823C_5669334A1920
#define D12574FD_AEB1_4040_823C_5669334A1920

#include "../../STD_DefaultInclude.hpp"
#include "../../ALLEGRO_DefaultInclude.hpp"
#include "../../Transforms/Transform.hpp"
#include "../../SceneManager/SceneManager.hpp"
#include "../../ShaderManager/ShaderManager.hpp"

#define CHUNK_TILE_SIZE 16 //tile size in pixels
#define CHUNK_TILES_NUM 32 //num of tiles
#define CHUNK_SIZE_PIXELS CHUNK_TILES_NUM*CHUNK_TILE_SIZE //number of tiles * tile size in pixel
#define CHUNK_DRAW_SCALE 4 //draw scale for chunk
#define MAX_CHUNK_INDEX_VALUE 2147483640
#define MIN_CHUNK_INDEX_VALUE -2147483640

struct Tile
{
    Vec2i index;
    Tile(){};
    Tile(Vec2i idx) : index(idx){};
};

class Chunk : public SceneObject
{
private:
    std::array<Tile, CHUNK_TILES_NUM*CHUNK_TILES_NUM> chunk_tiles;
    Bitmap *chunk_ground_mask = nullptr;
    Bitmap *chunk_final_bitmap = nullptr;
    Bitmap *chunk_temp_final_bitmap = nullptr;
    Bitmap *chunk_temp_map = nullptr;
    Shader *chunk_ground_mask_generator_shader = nullptr;
    Shader *chunk_ground_generator_shader = nullptr;

    float t_chunk_index[2];
public:
    Vec2i chunk_position;
    Vec2 chunk_center_position;
    Rect2 chunk_bounds;
    Vec2i chunk_index {MAX_CHUNK_INDEX_VALUE, MAX_CHUNK_INDEX_VALUE};
    bool chunk_is_loaded = false;
    bool chunk_is_visible = false;
    int chunk_seed = 0;

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
    virtual void Update(float delta){};

    /**
     * @brief called every frame after Update(). used to draw graphics.
     */
    virtual void Draw(float delta);

    /**
     * @brief called once when object marked as pending kill. in other words - before destruction.
     */
    virtual void End(){};

    void GenerateChunk();

    void SetChunkIndex(Vec2i idx);

    void UnloadChunk();

public:
    Chunk(const std::string& _obj_class, const ObjectSignature& obj_sign) : 
    SceneObject(_obj_class, obj_sign)
    {};
    virtual ~Chunk(){};
};

#endif /* D12574FD_AEB1_4040_823C_5669334A1920 */
