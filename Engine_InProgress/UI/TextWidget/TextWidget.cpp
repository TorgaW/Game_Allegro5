#include "TextWidget.hpp"

void TextWidget::Draw(float delta)
{
    al_draw_text(
        text_font,
        text_color,
        widget_transform.position.x,
        widget_transform.position.y - al_get_font_line_height(text_font) / 2.0f,
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