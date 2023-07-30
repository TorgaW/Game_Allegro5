#include "Container.hpp"

void Container::SetElementsAlignment(Alignment elements_alignment)
{
}

void Container::SetBackgroundColor(ALLEGRO_COLOR background_color)
{
    background_color = background_color;
}

void Container::SetBorderRadius(float border_radius)
{
    border_radius = border_radius;
}

void Container::SetBorderThickness(float border_thickness)
{
    border_thickness = border_thickness;
}

void Container::SetBorderColor(ALLEGRO_COLOR color)
{
    border_color = color;
}

void Container::Update(float delta)
{
    switch (elements_alignment)
    {
    case Alignment::RowUpperLeft:
        // on every step we move the next element, excluding the first one

        if (widget_children.size() == 1)
        {
            widget_children[0]->widget_transform.position.x += widget_transform.position.x - widget_transform.size.x / 2.0f;
        }
        else if (widget_children.size() > 1)
        {
            widget_children[0]->widget_transform.position.x += widget_transform.position.x - widget_transform.size.x / 2.0f;
            widget_children[0]->widget_transform.position.y += widget_transform.position.y - widget_transform.size.y / 2.0f;

            for (size_t i = 1; i < widget_children.size(); i++)
            {
                widget_children[i + 1]->widget_transform.position.x += widget_children[i]->widget_transform.position.x - widget_transform.size.x / 2.0f;
                widget_children[i + 1]->widget_transform.position.y -= widget_transform.size.y / 2.0f;
            };
        }

        // text_position.x = widget_transform.position.x - widget_transform.size.x / 2.0f + al_get_text_width(text_font, text.c_str()) / 2.0f;
        // text_position.y = widget_transform.position.y - widget_transform.size.y / 2.0f;
        break;
    // case Alignment::RowUpperCenter:
    //     text_position.x = widget_transform.position.x;
    //     text_position.y = widget_transform.position.y - widget_transform.size.y / 2.0f;
    //     break;
    // case Alignment::RowUpperRight:
    //     text_position.x = widget_transform.position.x + widget_transform.size.x / 2.0f - al_get_text_width(text_font, text.c_str()) / 2.0f;
    //     text_position.y = widget_transform.position.y - widget_transform.size.y / 2.0f;
    //     break;
    // case Alignment::RowMiddleLeft:
    //     text_position.x = widget_transform.position.x - widget_transform.size.x / 2.0f + al_get_text_width(text_font, text.c_str()) / 2.0f;
    //     text_position.y = widget_transform.position.y - al_get_font_line_height(text_font) / 2.0f;
    //     break;
    // case Alignment::RowMiddleCenter:
    //     text_position.x = widget_transform.position.x;
    //     text_position.y = widget_transform.position.y - al_get_font_line_height(text_font) / 2.0f;
    //     break;
    // case Alignment::RowMiddleRight:
    //     text_position.x = widget_transform.position.x + widget_transform.size.x / 2.0f - al_get_text_width(text_font, text.c_str()) / 2.0f;
    //     text_position.y = widget_transform.position.y - al_get_font_line_height(text_font) / 2.0f;
    //     break;
    // case Alignment::RowLowerLeft:
    //     text_position.x = widget_transform.position.x - widget_transform.size.x / 2.0f + al_get_text_width(text_font, text.c_str()) / 2.0f;
    //     text_position.y = widget_transform.position.y + widget_transform.size.y / 2.0f - al_get_font_line_height(text_font);
    //     break;
    // case Alignment::RowLowerCenter:
    //     text_position.x = widget_transform.position.x;
    //     text_position.y = widget_transform.position.y + widget_transform.size.y / 2.0f - al_get_font_line_height(text_font);
    //     break;
    // case Alignment::RowLowerRight:
    //     text_position.x = widget_transform.position.x + widget_transform.size.x / 2.0f - al_get_text_width(text_font, text.c_str()) / 2.0f;
    //     text_position.y = widget_transform.position.y + widget_transform.size.y / 2.0f - al_get_font_line_height(text_font);
    //     break;
    // case Alignment::ColUpperLeft:
    //     text_position.x = widget_transform.position.x - widget_transform.size.x / 2.0f + al_get_text_width(text_font, text.c_str()) / 2.0f;
    //     text_position.y = widget_transform.position.y - widget_transform.size.y / 2.0f;
    //     break;
    // case Alignment::ColUpperCenter:
    //     text_position.x = widget_transform.position.x;
    //     text_position.y = widget_transform.position.y - widget_transform.size.y / 2.0f;
    //     break;
    // case Alignment::ColUpperRight:
    //     text_position.x = widget_transform.position.x + widget_transform.size.x / 2.0f - al_get_text_width(text_font, text.c_str()) / 2.0f;
    //     text_position.y = widget_transform.position.y - widget_transform.size.y / 2.0f;
    //     break;
    // case Alignment::ColMiddleLeft:
    //     text_position.x = widget_transform.position.x - widget_transform.size.x / 2.0f + al_get_text_width(text_font, text.c_str()) / 2.0f;
    //     text_position.y = widget_transform.position.y - al_get_font_line_height(text_font) / 2.0f;
    //     break;
    // case Alignment::ColMiddleCenter:
    //     text_position.x = widget_transform.position.x;
    //     text_position.y = widget_transform.position.y - al_get_font_line_height(text_font) / 2.0f;
    //     break;
    // case Alignment::ColMiddleRight:
    //     text_position.x = widget_transform.position.x + widget_transform.size.x / 2.0f - al_get_text_width(text_font, text.c_str()) / 2.0f;
    //     text_position.y = widget_transform.position.y - al_get_font_line_height(text_font) / 2.0f;
    //     break;
    // case Alignment::ColLowerLeft:
    //     text_position.x = widget_transform.position.x - widget_transform.size.x / 2.0f + al_get_text_width(text_font, text.c_str()) / 2.0f;
    //     text_position.y = widget_transform.position.y + widget_transform.size.y / 2.0f - al_get_font_line_height(text_font);
    //     break;
    // case Alignment::ColLowerCenter:
    //     text_position.x = widget_transform.position.x;
    //     text_position.y = widget_transform.position.y + widget_transform.size.y / 2.0f - al_get_font_line_height(text_font);
    //     break;
    // case Alignment::ColLowerRight:
    //     text_position.x = widget_transform.position.x + widget_transform.size.x / 2.0f - al_get_text_width(text_font, text.c_str()) / 2.0f;
    //     text_position.y = widget_transform.position.y + widget_transform.size.y / 2.0f - al_get_font_line_height(text_font);
    //     break;
    default:
        break;
    }
}