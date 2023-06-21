#ifndef D4D99941_8FD9_4982_94DF_03C1E5FD4E9B
#define D4D99941_8FD9_4982_94DF_03C1E5FD4E9B

// #include "../../Components/SpriteSheetComponent/SpriteSheetComponent.h"
#include "../../SceneObjects/SceneObject/SceneObject.h"
// #include "../../Components/AnimationComponent/AnimationComponent.h"

class AStaticObject : public ASceneObject
{
private:
    // AnimationComponent AnimComponent;
public:
    AStaticObject(uint32_t id, uint64_t timestamp, std::string name, std::string static_class_name) : ASceneObject(id, timestamp, name, static_class_name) {};
    virtual ~AStaticObject(){};

    virtual void Begin() override;
    virtual void End() override;
    virtual void GTick(float delta_time) override;
    virtual void Tick(float delta_time) override;
};


#endif /* D4D99941_8FD9_4982_94DF_03C1E5FD4E9B */
