#include "StaticObject.h"

void AStaticObject::Begin()
{
    // Bitmap.LoadBitmap("Resources/Sprites/sprite_sheet_placeholder_10r_20c.png", 20, 10);
    // AAnimation *a = AnimationsManager::Get().CreateAnimation<AAnimation>("Test",
    //                             "Resources/Sprites/sprite_sheet_placeholder_10r_20c.png", 
    //                             10, 20);
    // a->SetAnimationSpeed(1.5f);
    // AnimComponent.AddAnimation(a);
    // AnimComponent.PlayAnimation("Test");
    // Transform.Scale = Vector2D(5.0f, 5.0f);
    // DrawBounds = Rectangle2D(Vector2D(0,0), Vector2D(16, 16)) * 6.0f;
    // DrawBoundsOffset = Vector2D(-8, -8)*6.0f;
    // IgnoreDrawBounds = false;
}

void AStaticObject::End()
{
    
}

void AStaticObject::GTick(float delta_time)
{
    // Bitmap.Draw(Transform.Position, Transform.Scale, delta_time);
    // AnimComponent.Draw(Transform, al_map_rgb(255, 255, 255));
}

void AStaticObject::Tick(float delta_time)
{
    // AnimComponent.Update(delta_time);
}
