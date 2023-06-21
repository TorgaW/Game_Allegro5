#include "AnimationComponent.h"

void AnimationComponent::AddAnimation(AAnimation *anim)
{
    if(anim == nullptr) return;
    AnimationsList.push_back(anim);
}

void AnimationComponent::PlayAnimation(std::string anim_name)
{
    auto fa = std::find_if(AnimationsList.begin(), AnimationsList.end(), [anim_name](AAnimation *anim){
        return anim->GetName() == anim_name;
    });
    if(fa == AnimationsList.end())
        return;
    CurrentAnimation = (*fa);
    Playing = true;
}

void AnimationComponent::Update(float delta_time)
{
    if(Playing && CurrentAnimation != nullptr)
        CurrentAnimation->Update(delta_time);
}

void AnimationComponent::Draw(Transform2D transform, ALLEGRO_COLOR tint)
{
    if(CurrentAnimation == nullptr)
        return;
    Vector2D p = CurrentAnimation->GetCurrentFrame();
    Vector2D s = CurrentAnimation->GetCellSize();
    al_draw_tinted_scaled_rotated_bitmap_region(CurrentAnimation->GetBitmap(),
                                                p.X * s.X, p.Y * s.Y, s.X, s.Y,
                                                tint,
                                                s.X / 2.0f, s.Y / 2.0f,
                                                transform.Position.X, transform.Position.Y, 
                                                transform.Scale.X, transform.Scale.Y,
                                                transform.Rotation, AnimationFlag);
}
