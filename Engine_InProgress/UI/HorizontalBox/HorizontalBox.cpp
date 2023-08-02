#include "HorizontalBox.hpp"

void HorizontalBox::Draw(float delta)
{
    al_draw_filled_rounded_rectangle(
        widget_transform.position.x - widget_transform.size.x * widget_pivot_point.x,
        widget_transform.position.y - widget_transform.size.y * widget_pivot_point.y,
        widget_transform.position.x + widget_transform.size.x * (1.0f - widget_pivot_point.x),
        widget_transform.position.y + widget_transform.size.y * (1.0f - widget_pivot_point.y),
        border_radius,
        border_radius,
        background_color);

    al_draw_rounded_rectangle(
        widget_transform.position.x - widget_transform.size.x / 2.0f,
        widget_transform.position.y - widget_transform.size.y / 2.0f,
        widget_transform.position.x + widget_transform.size.x / 2.0f,
        widget_transform.position.y + widget_transform.size.y / 2.0f,
        border_radius,
        border_radius,
        border_color,
        border_thickness);

    al_draw_circle(
        widget_transform.position.x - widget_transform.size.x / 2.0f,
        widget_transform.position.y,
        20.f,
        border_color,
        border_thickness);
}

void HorizontalBox::SetElementsGap(float new_elements_gap_x)
{
    elements_gap_x = new_elements_gap_x;
}

void HorizontalBox::SetElementsAlignment(Alignment new_container_alignment)
{
    container_alignment = new_container_alignment;
    requestAlignmentRender = true;
}

void HorizontalBox::SetBackgroundColor(ALLEGRO_COLOR new_background_color)
{
    background_color = new_background_color;
}

void HorizontalBox::SetBorderRadius(float new_border_radius)
{
    border_radius = new_border_radius;
}

void HorizontalBox::SetBorderThickness(float new_border_thickness)
{
    border_thickness = new_border_thickness;
}

void HorizontalBox::SetBorderColor(ALLEGRO_COLOR new_border_color)
{
    border_color = new_border_color;
}

void HorizontalBox::Update(float delta)
{
    if (requestAlignmentRender)
    {
        switch (container_alignment)
        {
        case Alignment::UpperLeft:
        {
            const float containerWidth = widget_transform.size.x;

            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x = widget_transform.position.x - containerWidth / 2.0f + widget_children[0]->widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y = widget_transform.position.y - widget_transform.size.y / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f;
            }
            else if (widget_children.size() > 1)
            {
                // Initial values
                float currentX = widget_transform.position.x - containerWidth / 2.0f;
                float currentY = widget_transform.position.y - widget_transform.size.y / 2.0f;
        
                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    // Position the widget in the current row.
                    widget_children[i]->widget_transform.position.x = currentX + widget_children[i]->widget_transform.size.x / 2.0f;
                    widget_children[i]->widget_transform.position.y = currentY + widget_children[i]->widget_transform.size.y / 2.0f;
                    // Move the currentX position to the right for the next widget in the row.
                    currentX += elements_gap_x + widget_children[i]->widget_transform.size.x;
                }
            };

            requestAlignmentRender = false;
            break;
        };

        case Alignment::UpperCenter:
        {
            const float containerWidth = widget_transform.size.x;

            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x = widget_transform.position.x;
                widget_children[0]->widget_transform.position.y = widget_transform.position.y - widget_transform.size.y / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f;
            }
            else if (widget_children.size() > 1)
            {
                // Count total elements width with gaps to set them in the center
                float totalElementsWidth{0.f};
                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    totalElementsWidth += widget_children[i]->widget_transform.size.x;
                }
                totalElementsWidth += (widget_children.size() - 1) * elements_gap_x;

                // Initial values
                float currentX = widget_transform.position.x - containerWidth / 2.0f + (containerWidth - totalElementsWidth) / 2.0f;
                float currentY = widget_transform.position.y - widget_transform.size.y / 2.0f;

                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    // Position the widget in the current row.
                    widget_children[i]->widget_transform.position.x = currentX + widget_children[i]->widget_transform.size.x / 2.0f;
                    widget_children[i]->widget_transform.position.y = currentY + widget_children[i]->widget_transform.size.y / 2.0f;
                    // Move the currentX position to the right for the next widget in the row.
                    currentX += elements_gap_x + widget_children[i]->widget_transform.size.x;
                }
            };

            requestAlignmentRender = false;
            break;
        };

        case Alignment::UpperRight:
        {
            const float containerWidth = widget_transform.size.x;

            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x = widget_transform.position.x + containerWidth / 2.0f - widget_children[0]->widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y = widget_transform.position.y - widget_transform.size.y / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f;
            }
            else if (widget_children.size() > 1)
            {
                // Count total elements width with gaps to set them in the right corner
                float totalElementsWidth{0.f};
                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    totalElementsWidth += widget_children[i]->widget_transform.size.x;
                }
                totalElementsWidth += (widget_children.size() - 1) * elements_gap_x;

                // Initial values
                float currentX = widget_transform.position.x - containerWidth / 2.0f + (containerWidth - totalElementsWidth);
                float currentY = widget_transform.position.y - widget_transform.size.y / 2.0f;

                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    // Position the widget in the current row.
                    widget_children[i]->widget_transform.position.x = currentX + widget_children[i]->widget_transform.size.x / 2.0f;
                    widget_children[i]->widget_transform.position.y = currentY + widget_children[i]->widget_transform.size.y / 2.0f;
                    // Move the currentX position to the right for the next widget in the row.
                    currentX += elements_gap_x + widget_children[i]->widget_transform.size.x;
                }
            };

            requestAlignmentRender = false;
            break;
        };

        case Alignment::MiddleLeft:
        {
            const float containerWidth = widget_transform.size.x;

            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x = widget_transform.position.x - containerWidth / 2.0f + widget_children[0]->widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y = widget_transform.position.y;
            }
            else if (widget_children.size() > 1)
            {
                // Initial values
                float currentX = widget_transform.position.x - containerWidth / 2.0f;
                float currentY = widget_transform.position.y;

                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    // Position the widget in the current row.
                    widget_children[i]->widget_transform.position.x = currentX + widget_children[i]->widget_transform.size.x / 2.0f;
                    widget_children[i]->widget_transform.position.y = currentY;
                    // Move the currentX position to the right for the next widget in the row.
                    currentX += elements_gap_x + widget_children[i]->widget_transform.size.x;
                }
            };

            requestAlignmentRender = false;
            break;
        };

        default:
            break;
        }
    }
}