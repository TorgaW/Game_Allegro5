#include "APlayer.h"

APlayer::APlayer(uint32_t id, uint64_t timestamp, std::string name, std::string static_class_name) : ASceneObject(id, timestamp, name, static_class_name)
{
}

APlayer::~APlayer()
{
}

void APlayer::Begin()
{
    Input.AddActionBinding("MoveForward", BC_KEY_HOLD, this, &APlayer::SetDirectionForward);
    Input.AddActionBinding("MoveBack", BC_KEY_HOLD, this, &APlayer::SetDirectionBackward);
    Input.AddActionBinding("MoveLeft", BC_KEY_HOLD, this, &APlayer::SetDirectionLeft);
    Input.AddActionBinding("MoveRight", BC_KEY_HOLD, this, &APlayer::SetDirectionRight);

    Input.AddActionBinding("MoveForward", BC_KEY_UP, this, &APlayer::ResetDirectionY);
    Input.AddActionBinding("MoveBack", BC_KEY_UP, this, &APlayer::ResetDirectionY);
    Input.AddActionBinding("MoveRight", BC_KEY_UP, this, &APlayer::ResetDirectionX);
    Input.AddActionBinding("MoveLeft", BC_KEY_UP, this, &APlayer::ResetDirectionX);

    AAnimation *anim_wf = AnimationsManager::Get().CreateAnimation<AAnimation>("WalkForward",
                                                                               "Resources/Sprites/Characters/Char1/Char1.png",
                                                                               3, 1);
    anim_wf->SetAnimationSpeed(0.7f);
    anim_wf->SetAnimationBounds(2, 2);
    AnimComp.AddAnimation(anim_wf);

    AAnimation *anim_wb = AnimationsManager::Get().CreateAnimation<AAnimation>("WalkBackward",
                                                                               "Resources/Sprites/Characters/Char1/Char1.png",
                                                                               3, 1);
    anim_wb->SetAnimationSpeed(0.7f);
    anim_wb->SetAnimationBounds(0, 0);
    AnimComp.AddAnimation(anim_wb);

    AAnimation *anim_wr = AnimationsManager::Get().CreateAnimation<AAnimation>("WalkRight",
                                                                               "Resources/Sprites/Characters/Char1/Char1.png",
                                                                               3, 1);
    anim_wr->SetAnimationSpeed(0.7f);
    anim_wr->SetAnimationBounds(1, 1);
    AnimComp.AddAnimation(anim_wr);

    AAnimation *anim_idle = AnimationsManager::Get().CreateAnimation<AAnimation>("IdleFace",
                                                                               "Resources/Sprites/Characters/Char1/Char1.png",
                                                                               3, 1);
    anim_idle->SetAnimationSpeed(0.1f);
    anim_idle->SetAnimationBounds(0, 0);
    AnimComp.AddAnimation(anim_idle);

    // AnimComp.PlayAnimation("WalkForward");
    Transform.Scale = {4.0f, 4.0f};
    IgnoreDrawBounds = true;

    TargetPosition = {0, 0};
    Transform.Position = TargetPosition;
    Layer = 0;
}

void APlayer::Tick(float delta)
{

    Direction.Reset();
    Input.ListenToInput();

    Direction = VMath::Normalize(Direction);
    TargetPosition.X += Direction.X * PlayerSpeed * delta;
    TargetPosition.Y += Direction.Y * PlayerSpeed * delta;

    Transform.Position = TargetPosition;

    if (Direction.X > 0.5f)
    {
        AnimComp.PlayAnimation("WalkRight");
        AnimComp.AnimationFlag = ALLEGRO_FLIP_HORIZONTAL;
    }
    else if (Direction.X < -0.5f)
    {
        AnimComp.PlayAnimation("WalkRight");
        AnimComp.AnimationFlag = 0;
    }
    else if (Direction.Y > 0.5f)
    {
        AnimComp.PlayAnimation("WalkBackward");
        AnimComp.AnimationFlag = 0;
    }
    else if (Direction.Y < -0.5f)
    {
        AnimComp.PlayAnimation("WalkForward");
        AnimComp.AnimationFlag = 0;
    }
    else
    {
        AnimComp.AnimationFlag = 0;
        AnimComp.PlayAnimation("IdleFace");
    }

    AnimComp.Update(delta);
}

void APlayer::GTick(float delta)
{
    AnimComp.Draw(Transform, al_map_rgb(255, 255, 255));
}

void APlayer::End()
{
}

void APlayer::SetDirectionForward()
{
    Direction.Y -= 1;
    Direction = VMath::Clamp(Direction, -1, 1);
}

void APlayer::SetDirectionBackward()
{
    Direction.Y += 1;
    Direction = VMath::Clamp(Direction, -1, 1);
}

void APlayer::SetDirectionRight()
{
    Direction.X += 1;
    Direction = VMath::Clamp(Direction, -1, 1);
}

void APlayer::SetDirectionLeft()
{
    Direction.X -= 1;
    Direction = VMath::Clamp(Direction, -1, 1);
}

void APlayer::ResetDirectionY()
{
    Direction.Y = 0;
}

void APlayer::ResetDirectionX()
{
    Direction.X = 0;
}
