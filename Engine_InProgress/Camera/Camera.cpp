#include "Camera.hpp"

void Camera::MoveUp()
{
    transform.position.y -= 0.3f;
}

void Camera::MoveDown()
{
    transform.position.y += 0.3f;
}

void Camera::MoveRight()
{
    transform.position.x += 0.3f;
}

void Camera::MoveLeft()
{
    transform.position.x -= 0.3f;
}

void Camera::ZoomIn()
{
    camera_zoom += 0.05f;
}

void Camera::ZoomOut()
{
    camera_zoom -= 0.05f;
}

void Camera::Begin()
{
    input_component.AddKeyboardActionBinding("MoveUp", KeyboardEventType::Hold, this, &Camera::MoveUp);
    input_component.AddKeyboardActionBinding("MoveDown", KeyboardEventType::Hold, this, &Camera::MoveDown);
    input_component.AddKeyboardActionBinding("MoveRight", KeyboardEventType::Hold, this, &Camera::MoveRight);
    input_component.AddKeyboardActionBinding("MoveLeft", KeyboardEventType::Hold, this, &Camera::MoveLeft);
    input_component.AddKeyboardActionBinding("ZoomIn", KeyboardEventType::Down, this, &Camera::ZoomIn);
    input_component.AddKeyboardActionBinding("ZoomOut", KeyboardEventType::Down, this, &Camera::ZoomOut);
}

void Camera::Update(float delta)
{
    input_component.ListenToInput();

    al_identity_transform(&camera_offset_transform);
    al_translate_transform(&camera_offset_transform, Render::GetDisplayWidth()/camera_zoom/2.0, Render::GetDisplayHeight()/camera_zoom/2.0);
    al_translate_transform(&camera_offset_transform, -transform.position.x, -transform.position.y);
    al_scale_transform(&camera_offset_transform, camera_zoom, camera_zoom);
    Render::SetCameraOffsetTransform(camera_offset_transform);
    transform.scale = {camera_zoom, camera_zoom};
    Render::SetCameraTransform(transform);
}
