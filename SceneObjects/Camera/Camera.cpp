#include "Camera.h"

void Camera::Zoom(float dz)
{
    TargetZoom = VMath::Clamp(TargetZoom + 0.05f * dz, 0.1f, 1.0f);
}

Camera::Camera()
{
    // Input.AddActionBinding("MoveForward", BC_KEY_HOLD, this, &Camera::MoveForward);
    // Input.AddActionBinding("MoveLeft", BC_KEY_HOLD, this, &Camera::MoveLeft);
    // Input.AddActionBinding("MoveBack", BC_KEY_HOLD, this, &Camera::MoveBack);
    // Input.AddActionBinding("MoveRight", BC_KEY_HOLD, this, &Camera::MoveRight);
    Input.AddMouseActionBinding("MouseZ", BC_MOUSE_AXES_Z, this, &Camera::Zoom);
    // Input.AddMouseActionBinding("MouseX", BC_MOUSE_AXES_X, this, &Camera::MoveX);
    // Input.AddMouseActionBinding("MouseY", BC_MOUSE_AXES_Y, this, &Camera::MoveY);
    // Input.AddActionBinding("ZoomIn", BC_KEY_DOWN, this, &Camera::ZoomIn);
    // Input.AddActionBinding("ZoomOut", BC_KEY_UP, this, &Camera::ZoomOut);
    // Transform.Position = Vector2D(0, 0);
    Transform.Scale = Vector2D(1, 1);
    TargetZoom = Transform.Scale;
}

void Camera::UpdateCameraPosition(Vector2D newPos)
{

}

void Camera::Tick(float delta)
{
    Input.ListenToInput();

    if(Parent != nullptr)
    {
        // if(VMath::Length(Transform.Position - Parent->Transform.Position) > 100.0f)
        TargetPosition = Parent->Transform.Position;
    }

    Transform.Position = VMath::Lerp(Transform.Position, TargetPosition, delta * 15.0f);
    Transform.Scale = VMath::Lerp(Transform.Scale, TargetZoom, delta * 15.0f);
    
    al_identity_transform(&CameraTransform);
    al_translate_transform(&CameraTransform, 1280/Transform.Scale.X, 720/Transform.Scale.Y);
    al_translate_transform(&CameraTransform, -Transform.Position.X, -Transform.Position.Y);
    al_scale_transform(&CameraTransform, Transform.Scale.X, Transform.Scale.Y);

    Render::Get().SetSceneTransform(&CameraTransform);
    Render::Get().SetCameraTransform(Transform);
}
