#ifndef F16E0D86_ED49_4873_9BD2_5E18096D90D4
#define F16E0D86_ED49_4873_9BD2_5E18096D90D4

#include <allegro5/allegro5.h>
#include <string>
#include "../../Defines/Defines.h"
#include "../../BitmapLoader/BitmapLoader.h"

class AAnimation
{
private:
    ALLEGRO_BITMAP *Bitmap = nullptr;
    std::string Name = "";
    uint16_t SizeX = 0, SizeY = 0;
    uint16_t CellsNumX = 0, CellsNumY = 0;
    uint16_t CellSizeX = 0, CellSizeY = 0;
    uint16_t StartPositionX = 0, StartPositionY = 0;
    uint16_t EndPositionX = 0, EndPositionY = 0;
    float FPS = 10.0f;
    float AnimationSpeed = 1.0f;

    uint16_t CurrentX = 0, CurrentY = 0;
    float FramesCounter = 0.0f, FrameDelta = 0.1f;
public:
    AAnimation(std::string name);
    ~AAnimation();
public:
    inline ALLEGRO_BITMAP *GetBitmap() { return Bitmap; };
    inline Vector2D GetCurrentFrame() { return Vector2D(CurrentX, CurrentY); };
    inline Vector2D GetCellSize() { return Vector2D(CellSizeX, CellSizeY); };
    inline void SetAnimationSpeed(float new_speed) { AnimationSpeed = (new_speed >= 0.0f ? new_speed:0.0f); };
    inline void SetFPS(float new_fps)
    {
        FPS = new_fps >= 1.0f ? new_fps:1.0f;
        FrameDelta = 1.0f / FPS;
    }
    inline std::string GetName() { return Name; };
    inline void SetAnimationBounds(uint16_t startX, uint16_t endX, uint16_t endY = 0, uint16_t startY = 0)
    {
        StartPositionX = startX;
        StartPositionY = startY;
        EndPositionX = endX;
        EndPositionY = endY;
        CurrentX = startX;
        CurrentY = startY;
    }
public:
    bool LoadBitmap(std::string path_to_image, uint16_t columns_num, uint16_t rows_num);
    void Update(float delta);
};

#endif /* F16E0D86_ED49_4873_9BD2_5E18096D90D4 */
