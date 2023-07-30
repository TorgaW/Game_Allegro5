#include "CanvasWidget.hpp"

void CanvasWidget::Begin()
{
    target_width = max_width;
    // canvas_input.AddKeyboardActionBinding("test_input", KeyboardEventType::Down, this, &CanvasWidget::TestInput);
}

void CanvasWidget::Update(float delta)
{
    canvas_input.ListenToInput();
}

void CanvasWidget::Draw(float delta)
{
    // resize widget
    widget_transform.size.x += delta * resize_speed;

    // check target width
    if (target_width > min_width)
    {
        if (widget_transform.size.x >= target_width)
        {
            // set target size to 0
            target_width = min_width;
            // reverse speed
            resize_speed *= -1.f;
        }
    }
    else // if target width is 0
    {
        if (widget_transform.size.x <= target_width)
        {
            // set target size back to max_width
            target_width = max_width;
            // reverse speed again
            resize_speed *= -1.f;
        }
    }

    // center widget position
    widget_transform.position = {
        Render::GetMonitorWidth() / 2.0f - widget_transform.size.x / 2.0f,
        Render::GetMonitorHeight() / 2.0f - widget_transform.size.y / 2.0f};

<<<<<<< Updated upstream
    //draw primitive rectangle
    al_draw_rectangle(  widget_transform.position.x, widget_transform.position.y, 
                        widget_transform.position.x + widget_transform.size.x,
                        widget_transform.position.y + widget_transform.size.y,
                        canvas_border_color,
                        canvas_border_thickness);
}

void CanvasWidget::TestInput()
{
    EngineDebugger::PrintDebugMessage("Hello!!", al_map_rgb_f(1.f, 1.f, 1.f), 10.0f);
}
||||||| Stash base
    //draw primitive rectangle
    al_draw_rectangle(  widget_transform.position.x, widget_transform.position.y, 
                        widget_transform.position.x + widget_transform.size.x,
                        widget_transform.position.y + widget_transform.size.y,
                        canvas_border_color,
                        canvas_border_thickness);
}
=======
    // draw primitive rectangle
    al_draw_rectangle(widget_transform.position.x, widget_transform.position.y,
                      widget_transform.position.x + widget_transform.size.x,
                      widget_transform.position.y + widget_transform.size.y,
                      canvas_border_color,
                      canvas_border_thickness);
}
>>>>>>> Stashed changes
