#include "TextWidget.hpp"

void TextWidget::Draw(float delta)
{
    // al_draw_filled_rounded_rectangle(
    //     widget_transform.position.x - widget_transform.size.x * widget_pivot_point.x,
    //     widget_transform.position.y - widget_transform.size.y * widget_pivot_point.y,
    //     widget_transform.position.x + widget_transform.size.x * (1.0f - widget_pivot_point.x),
    //     widget_transform.position.y + widget_transform.size.y * (1.0f - widget_pivot_point.y),
    //     widget_border_radius,
    //     widget_border_radius,
    //     widget_background_color);

    // al_draw_rounded_rectangle(
    //     widget_transform.position.x - widget_transform.size.x / 2.0f,
    //     widget_transform.position.y - widget_transform.size.y / 2.0f,
    //     widget_transform.position.x + widget_transform.size.x / 2.0f,
    //     widget_transform.position.y + widget_transform.size.y / 2.0f,
    //     widget_border_radius,
    //     widget_border_radius,
    //     widget_border_color,
    //     widget_border_thickness);

    al_draw_text(
        text_font,
        text_color,
        widget_transform.position.x,
        widget_transform.position.y,
        ALLEGRO_ALIGN_CENTER,
        text.c_str());
}

void TextWidget::Begin()
{

}

void TextWidget::Update(float delta)
{
}

void TextWidget::SetText(const std::string &new_text)
{
    text = new_text;
}

void TextWidget::SetFont(ALLEGRO_FONT *new_font)
{
    text_font = new_font;
}

void TextWidget::SetTextColor(ALLEGRO_COLOR new_color)
{
    text_color = new_color;
}