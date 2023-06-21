#ifndef D7468E53_97B4_49BA_8E1A_E7DC119EFA1D
#define D7468E53_97B4_49BA_8E1A_E7DC119EFA1D

#include <allegro5/allegro5.h>
#include "../../Core/Math/Noise/Perlin.h"
// #include "../../SceneObjects/SceneObject/SceneObject.h"
#include "../../Core/Main/Game.h"
#include <iostream>

#include <boost/thread.hpp>
#include <boost/bind.hpp>

struct SChunk
{
    ALLEGRO_BITMAP *btm = nullptr;
    Vector2D coord = {0, 0};
    Vector2D worldPos = {0, 0};
    Vector2D offsetMapPos = {0, 0};
    SChunk(ALLEGRO_BITMAP *bitmap, Vector2D pos, Vector2D wpos, Vector2D offset);
    SChunk(){};
};

class AChunkManager : public ASceneObject
{
private:
    Noise *WorldMap;
    PerlinNoise Generator;
    ALLEGRO_BITMAP *Chunk;
    boost::mutex ChunksMutex;
    std::vector<SChunk> Chunks;
    Vector2D ChunkSize;
    Vector2D ChunkPivotPoint;
    Vector2D PreviousChunkPivotPoint;

    ALLEGRO_BITMAP *GrassTileSample;
    ALLEGRO_BITMAP *WaterTileSample;

    ALLEGRO_SHADER *sh;
public:
    AChunkManager(uint32_t id, uint64_t timestamp, std::string name, std::string static_class_name) : ASceneObject(id, timestamp, name, static_class_name) {};
    virtual ~AChunkManager();
public:
    virtual void Begin();
    // virtual void End();
    virtual void GTick(float delta_time);
    virtual void Tick(float delta_time);

    void GenerateWorld();
    inline void ChangeChunkPivot(Vector2D new_point)
    {
        PreviousChunkPivotPoint = ChunkPivotPoint;
        ChunkPivotPoint = new_point;
    };
    inline ALLEGRO_BITMAP *GetCurrentChunk() { return Chunk; };

    ALLEGRO_BITMAP *CreateBitmapChunk(uint16_t offsetX, uint16_t offsetY, uint16_t width, uint16_t height);
};

#endif /* D7468E53_97B4_49BA_8E1A_E7DC119EFA1D */
