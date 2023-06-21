#ifndef BB819111_7C4C_4C98_92EF_4C599DEAD8C3
#define BB819111_7C4C_4C98_92EF_4C599DEAD8C3

#include <allegro5/allegro5.h>
#include <iostream>
#include <string>
#include <vector>
#include "../../Core/Animations/AnimationsManager/AnimationsManager.h"


class AnimationComponent
{
private:
    std::vector<AAnimation*> AnimationsList;
    AAnimation *CurrentAnimation = nullptr;
    bool Playing = false;
public:
    int AnimationFlag = 0;
    AnimationComponent(){};
    ~AnimationComponent(){};

public:
    void AddAnimation(AAnimation *anim);
    void PlayAnimation(std::string anim_name);
    inline void PauseAnimation() {  Playing = false; };
    inline AAnimation *GetCurrentAnimation() { return CurrentAnimation; };
    void Update(float delta_time);
    void Draw(Transform2D transform, ALLEGRO_COLOR tint);
};


#endif /* BB819111_7C4C_4C98_92EF_4C599DEAD8C3 */
