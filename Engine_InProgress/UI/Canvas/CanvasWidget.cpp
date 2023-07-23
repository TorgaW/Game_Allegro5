#include "CanvasWidget.hpp"

void CanvasWidget::Draw(float delta)
{
    //resize widget
    widget_transform.size.x += delta*resize_speed;

    //check target width
    if(target_width > 0)
    {
        if(widget_transform.size.x >= target_width)
        {
            //set target size to 0
            target_width = 0.f;
            //reverse speed
            resize_speed *= -1.f;
        }
    }
    else //if target width is 0
    {
        if(widget_transform.size.x <= target_width)
        {
            //set target size back to 1000
            target_width = 1000.f;
            //reverse speed again
            resize_speed *= -1.f;
        }
    }

    widget_transform.position = {
        Render::GetMonitorWidth()/2.0f - widget_transform.size.x/2.0f, 
        Render::GetMonitorHeight()/2.0f - widget_transform.size.y/2.0f
        };

    //draw primitive rectangle
    al_draw_rectangle(  widget_transform.position.x, widget_transform.position.y, 
                        widget_transform.position.x + widget_transform.size.x,
                        widget_transform.position.y + widget_transform.size.y,
                        canvas_border_color,
                        canvas_border_thickness);
}