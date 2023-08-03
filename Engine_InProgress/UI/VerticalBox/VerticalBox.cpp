#include "VerticalBox.hpp"

void VerticalBox::Draw(float delta)
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
}

void VerticalBox::Update(float delta)
{
    if (requestAlignmentRender)
    {
        switch (container_alignment)
        {
        case Alignment::UpperLeft:
        {
            const float containerWidth = widget_transform.size.x;
            const float containerHeight = widget_transform.size.y;

            if (widget_children.size() == 1)
            {
                // Set X coordinates
                if (widget_children[0]->widget_transform.size.x >= (containerWidth - padding.x - padding.z))
                {
                    widget_children[0]->widget_transform.size.x = containerWidth - padding.x - padding.z;
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x - containerWidth / 2.0f + widget_children[0]->widget_transform.size.x / 2.0f + padding.x;
                }
                else if (horizontal_stretch)
                {
                    widget_children[0]->widget_transform.size.x += containerWidth - widget_children[0]->widget_transform.size.x - padding.x - padding.z;
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x;
                }
                else
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x - containerWidth / 2.0f + widget_children[0]->widget_transform.size.x / 2.0f + padding.x;

                // Set Y coordinates
                if (widget_children[0]->widget_transform.size.y >= (containerHeight - padding.y - padding.w))
                {
                    widget_children[0]->widget_transform.size.y = containerHeight - padding.y - padding.w;
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - containerHeight / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
                }
                else if (vertical_stretch)
                {
                    widget_children[0]->widget_transform.size.y += containerHeight - widget_children[0]->widget_transform.size.y - padding.y - padding.w;
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - widget_transform.size.y / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
                }
                else
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - widget_transform.size.y / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
            }
            else if (widget_children.size() > 1)
            {
                // Count total elements width with gaps to set them in the center
                float totalElementsHeight{0.f};
                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    totalElementsHeight += widget_children[i]->widget_transform.size.y;
                }
                totalElementsHeight += (widget_children.size() - 1) * elements_gap_y;

                // Counting additional size in order to stretch all the elements or reduce their height
                float heightToAddToElement = 0.f;
                float heightToReduceFromElement = 0.f;

                // Initial values
                float currentX = widget_transform.position.x - containerWidth / 2.0f + padding.x;
                float currentY = widget_transform.position.y - widget_transform.size.y / 2.0f + padding.y;

                if (totalElementsHeight >= (containerHeight - padding.y - padding.w))
                {
                    heightToReduceFromElement = (containerHeight - padding.y - padding.w - totalElementsHeight) / widget_children.size();
                }
                else if (vertical_stretch)
                    heightToAddToElement = (containerHeight - padding.y - padding.w - totalElementsHeight) / widget_children.size();

                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    // It may stretch all the elements up or reduce their height
                    widget_children[i]->widget_transform.size.y += heightToAddToElement + heightToReduceFromElement;

                    // Stretch the elements on the horizontal axis
                    if (widget_children[i]->widget_transform.size.x >= (containerWidth - padding.x - padding.z))
                    {
                        widget_children[i]->widget_transform.size.x = containerWidth - padding.x - padding.z;
                    }
                    else if (horizontal_stretch)
                        widget_children[i]->widget_transform.size.x += containerWidth - padding.x - padding.z - widget_children[i]->widget_transform.size.x;

                    // Position the widget in the current row.
                    widget_children[i]->widget_transform.position.x = currentX + widget_children[i]->widget_transform.size.x / 2.0f;
                    widget_children[i]->widget_transform.position.y = currentY + widget_children[i]->widget_transform.size.y / 2.0f;

                    // Move the currentY position to the right for the next widget in the row.
                    currentY += elements_gap_y + widget_children[i]->widget_transform.size.y;
                }
            };

            requestAlignmentRender = false;
            break;
        };

        case Alignment::UpperCenter:
        {
            const float containerWidth = widget_transform.size.x;
            const float containerHeight = widget_transform.size.y;

            if (widget_children.size() == 1)
            {
                // Set X coordinates
                if (widget_children[0]->widget_transform.size.x >= (containerWidth - padding.x - padding.z))
                {
                    widget_children[0]->widget_transform.size.x = containerWidth - padding.x - padding.z;
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x - containerWidth / 2.0f + widget_children[0]->widget_transform.size.x / 2.0f + padding.x;
                }
                else if (horizontal_stretch)
                {
                    widget_children[0]->widget_transform.size.x += containerWidth - widget_children[0]->widget_transform.size.x - padding.x - padding.z;
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x;
                }
                else
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x;

                // Set Y coordinates
                if (widget_children[0]->widget_transform.size.y >= (containerHeight - padding.y - padding.w))
                {
                    widget_children[0]->widget_transform.size.y = containerHeight - padding.y - padding.w;
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - containerHeight / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
                }
                else if (vertical_stretch)
                {
                    widget_children[0]->widget_transform.size.y += containerHeight - widget_children[0]->widget_transform.size.y - padding.y - padding.w;
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - widget_transform.size.y / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
                }
                else
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - widget_transform.size.y / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
            }
            else if (widget_children.size() > 1)
            {
                // Count total elements width with gaps to set them in the center
                float totalElementsHeight{0.f};
                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    totalElementsHeight += widget_children[i]->widget_transform.size.y;
                }
                totalElementsHeight += (widget_children.size() - 1) * elements_gap_y;

                // Counting additional size in order to stretch all the elements or reduce their length
                float heightToAddToElement = 0.f;
                float heightToReduceFromElement = 0.f;

                // Initial values
                float currentX = widget_transform.position.x;
                float currentY = widget_transform.position.y - widget_transform.size.y / 2.0f + padding.y;

                if (totalElementsHeight >= (containerHeight - padding.y - padding.w))
                {
                    heightToReduceFromElement = (containerHeight - padding.y - padding.w - totalElementsHeight) / widget_children.size();
                }
                else if (vertical_stretch)
                {
                    heightToAddToElement = (containerHeight - padding.y - padding.w - totalElementsHeight) / widget_children.size();
                }

                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    // It may stretch all the elements up or reduce their length
                    widget_children[i]->widget_transform.size.y += heightToAddToElement + heightToReduceFromElement;

                    // Checking if the widget is longer then container.
                    if (widget_children[i]->widget_transform.size.x >= containerWidth - padding.x - padding.z)
                        widget_children[i]->widget_transform.size.x = containerWidth - padding.x - padding.z;

                    // Set all the elements vertically stretched if its needed
                    if (horizontal_stretch)
                    {
                        widget_children[i]->widget_transform.size.x += containerWidth - padding.x - padding.z - widget_children[i]->widget_transform.size.x;
                        currentX = widget_transform.position.x - containerWidth / 2.0f + widget_children[i]->widget_transform.size.x / 2.0f + padding.x;
                    }
                    // Check if the widget borders with the left padding. If it does we will move it righter
                    else if (widget_children[i]->widget_transform.size.x / 2.0f >= (containerWidth / 2.0f - padding.x))
                    {
                        currentX = widget_transform.position.x - containerWidth / 2.0f + widget_children[i]->widget_transform.size.x / 2.0f + padding.x;
                    }
                    // Check if the widget borders with the right padding. If it does we will move it lefter
                    else if (widget_children[i]->widget_transform.size.x / 2.0f >= (containerWidth / 2.0f - padding.z))
                    {
                        currentX = widget_transform.position.x - containerWidth / 2.0f + widget_children[i]->widget_transform.size.x / 2.0f + padding.z;
                    }

                    // Position the widget in the current row.
                    widget_children[i]->widget_transform.position.x = currentX;
                    widget_children[i]->widget_transform.position.y = currentY + widget_children[i]->widget_transform.size.y / 2.0f;

                    // Reset X coordinate
                    currentX = widget_transform.position.x;
                    // Move the currentY position to the right for the next widget in the row.
                    currentY += elements_gap_y + widget_children[i]->widget_transform.size.y;
                }
            };

            requestAlignmentRender = false;
            break;
        };

        case Alignment::UpperRight:
        {
            const float containerWidth = widget_transform.size.x;
            const float containerHeight = widget_transform.size.y;

            if (widget_children.size() == 1)
            {
                // Set X coordinates
                if (widget_children[0]->widget_transform.size.x >= (containerWidth - padding.x - padding.z))
                {
                    widget_children[0]->widget_transform.size.x = containerWidth - padding.x - padding.z;
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x - containerWidth / 2.0f + widget_children[0]->widget_transform.size.x / 2.0f + padding.x;
                }
                else if (horizontal_stretch)
                {
                    widget_children[0]->widget_transform.size.x += containerWidth - widget_children[0]->widget_transform.size.x - padding.x - padding.z;
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x;
                }
                else
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x + containerWidth / 2.0f - widget_children[0]->widget_transform.size.x / 2.0f - padding.z;

                // Set Y coordinates
                if (widget_children[0]->widget_transform.size.y >= (containerHeight - padding.y - padding.w))
                {
                    widget_children[0]->widget_transform.size.y = containerHeight - padding.y - padding.w;
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - containerHeight / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
                }
                else if (vertical_stretch)
                {
                    widget_children[0]->widget_transform.size.y += containerHeight - widget_children[0]->widget_transform.size.y - padding.y - padding.w;
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - widget_transform.size.y / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
                }
                else
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - widget_transform.size.y / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
            }
            else if (widget_children.size() > 1)
            {
                // Count total elements width with gaps to set them
                float totalElementsHeight{0.f};
                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    totalElementsHeight += widget_children[i]->widget_transform.size.y;
                }
                totalElementsHeight += (widget_children.size() - 1) * elements_gap_y;

                // Counting additional size in order to stretch all the elements or reduce their length
                float heightToAddToElement = 0.f;
                float heightToReduceFromElement = 0.f;

                // Initial values
                float currentX = widget_transform.position.x + containerWidth / 2.0f - padding.z;
                float currentY = widget_transform.position.y - widget_transform.size.y / 2.0f + padding.y;

                if (totalElementsHeight >= (containerHeight - padding.y - padding.w))
                {
                    heightToReduceFromElement = (containerHeight - padding.y - padding.w - totalElementsHeight) / widget_children.size();
                }
                else if (vertical_stretch)
                {

                    heightToAddToElement = (containerHeight - padding.y - padding.w - totalElementsHeight) / widget_children.size();
                }

                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    // It may stretch all the elements up or reduce their length
                    widget_children[i]->widget_transform.size.y += heightToAddToElement + heightToReduceFromElement;

                    // Stretch the elements on the horizontal axis
                    if (widget_children[i]->widget_transform.size.x >= (containerWidth - padding.x - padding.z))
                    {
                        widget_children[i]->widget_transform.size.x = containerWidth - padding.x - padding.z;
                    }
                    else if (horizontal_stretch)
                        widget_children[i]->widget_transform.size.x += containerWidth - padding.x - padding.z - widget_children[i]->widget_transform.size.x;

                    // Position the widget in the current row.
                    widget_children[i]->widget_transform.position.x = currentX - widget_children[i]->widget_transform.size.x / 2.0f;
                    widget_children[i]->widget_transform.position.y = currentY + widget_children[i]->widget_transform.size.y / 2.0f;

                    // Move the currentX position to the right for the next widget in the row.
                    currentY += elements_gap_y + widget_children[i]->widget_transform.size.y;
                }
            };

            requestAlignmentRender = false;
            break;
        };

        case Alignment::MiddleLeft:
        {
            const float containerWidth = widget_transform.size.x;
            const float containerHeight = widget_transform.size.y;

            if (widget_children.size() == 1)
            {
                // Set X coordinates
                if (widget_children[0]->widget_transform.size.x >= (containerWidth - padding.x - padding.z))
                {
                    widget_children[0]->widget_transform.size.x = containerWidth - padding.x - padding.z;
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x - containerWidth / 2.0f + widget_children[0]->widget_transform.size.x / 2.0f + padding.x;
                }
                else if (horizontal_stretch)
                {
                    widget_children[0]->widget_transform.size.x += containerWidth - widget_children[0]->widget_transform.size.x - padding.x - padding.z;
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x;
                }
                else
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x - containerWidth / 2.0f + widget_children[0]->widget_transform.size.x / 2.0f + padding.x;

                // Set Y coordinates
                if (widget_children[0]->widget_transform.size.y >= (containerHeight - padding.y - padding.w))
                {
                    widget_children[0]->widget_transform.size.y = containerHeight - padding.y - padding.w;
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - containerHeight / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
                }
                else if (vertical_stretch)
                {
                    widget_children[0]->widget_transform.size.y += containerHeight - widget_children[0]->widget_transform.size.y - padding.y - padding.w;
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - widget_transform.size.y / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
                }
                else
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y;
            }
            else if (widget_children.size() > 1)
            {
                // Count total elements width with gaps to set them in the center
                float totalElementsHeight{0.f};
                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    totalElementsHeight += widget_children[i]->widget_transform.size.y;
                }
                totalElementsHeight += (widget_children.size() - 1) * elements_gap_y;

                // Counting additional size in order to stretch all the elements or reduce their length
                float heightToAddToElement = 0.f;
                float heightToReduceFromElement = 0.f;

                // Initial values
                float currentX = widget_transform.position.x - containerWidth / 2.0f + padding.x;
                float currentY = widget_transform.position.y - containerHeight / 2.0f + (containerHeight - totalElementsHeight) / 2.0f + padding.y;

                if (totalElementsHeight >= (containerHeight - padding.y - padding.w))
                {
                    currentY = widget_transform.position.y - containerHeight / 2.0f + padding.y;
                    heightToReduceFromElement = (containerHeight - padding.y - padding.w - totalElementsHeight) / widget_children.size();
                }
                else if (vertical_stretch)
                {
                    currentY = widget_transform.position.y - containerHeight / 2.0f + padding.y;
                    heightToAddToElement = (containerHeight - padding.y - padding.w - totalElementsHeight) / widget_children.size();
                }

                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    // It may stretch all the elements up or reduce their length
                    widget_children[i]->widget_transform.size.y += heightToAddToElement + heightToReduceFromElement;

                    // Checking if the widget is longer then container.
                    if (widget_children[i]->widget_transform.size.x >= containerWidth - padding.x - padding.z)
                        widget_children[i]->widget_transform.size.x = containerWidth - padding.x - padding.z;

                    // Set all the elements vertically stretched if its needed
                    if (horizontal_stretch)
                    {
                        widget_children[i]->widget_transform.size.x += containerWidth - padding.x - padding.z - widget_children[i]->widget_transform.size.x;
                        currentX = widget_transform.position.x - containerWidth / 2.0f + padding.x;
                    }
                    // Check if the widget borders with the left padding. If it does we will move it righter
                    else if (widget_children[i]->widget_transform.size.x / 2.0f >= (containerWidth / 2.0f - padding.x))
                    {
                        currentX = widget_transform.position.x - containerWidth / 2.0f + widget_children[i]->widget_transform.size.x / 2.0f + padding.x;
                    }
                    // Check if the widget borders with the right padding. If it does we will move it lefter
                    else if (widget_children[i]->widget_transform.size.x / 2.0f >= (containerWidth / 2.0f - padding.z))
                    {
                        currentX = widget_transform.position.x - containerWidth / 2.0f + widget_children[i]->widget_transform.size.x / 2.0f + padding.z;
                    }

                    // Position the widget in the current row.
                    widget_children[i]->widget_transform.position.x = currentX + widget_children[i]->widget_transform.size.x / 2.0f;
                    widget_children[i]->widget_transform.position.y = currentY + widget_children[i]->widget_transform.size.y / 2.0f;

                    // Reset X coordinate
                    currentX = widget_transform.position.x - containerWidth / 2.0f + padding.x;
                    // Move the currentY position to the right for the next widget in the row.
                    currentY += elements_gap_y + widget_children[i]->widget_transform.size.y;
                }
            };

            requestAlignmentRender = false;
            break;
        };

        case Alignment::MiddleCenter:
        {
            const float containerWidth = widget_transform.size.x;
            const float containerHeight = widget_transform.size.y;

            if (widget_children.size() == 1)
            {
                // Set X coordinates
                if (widget_children[0]->widget_transform.size.x >= (containerWidth - padding.x - padding.z))
                {
                    widget_children[0]->widget_transform.size.x = containerWidth - padding.x - padding.z;
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x - containerWidth / 2.0f + widget_children[0]->widget_transform.size.x / 2.0f + padding.x;
                }
                else if (horizontal_stretch)
                {
                    widget_children[0]->widget_transform.size.x += containerWidth - widget_children[0]->widget_transform.size.x - padding.x - padding.z;
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x;
                }
                else
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x;

                // Set Y coordinates
                if (widget_children[0]->widget_transform.size.y >= (containerHeight - padding.y - padding.w))
                {
                    widget_children[0]->widget_transform.size.y = containerHeight - padding.y - padding.w;
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - containerHeight / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
                }
                else if (vertical_stretch)
                {
                    widget_children[0]->widget_transform.size.y += containerHeight - widget_children[0]->widget_transform.size.y - padding.y - padding.w;
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - widget_transform.size.y / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
                }
                else
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y;
            }
            else if (widget_children.size() > 1)
            {
                // Count total elements width with gaps to set them in the center
                float totalElementsHeight{0.f};
                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    totalElementsHeight += widget_children[i]->widget_transform.size.y;
                }
                totalElementsHeight += (widget_children.size() - 1) * elements_gap_y;

                // Counting additional size in order to stretch all the elements or reduce their length
                float heightToAddToElement = 0.f;
                float heightToReduceFromElement = 0.f;

                // Initial values
                float currentX = widget_transform.position.x;
                float currentY = widget_transform.position.y - containerHeight / 2.0f + (containerHeight - totalElementsHeight) / 2.0f + padding.y;

                if (totalElementsHeight >= (containerHeight - padding.y - padding.w))
                {
                    currentY = widget_transform.position.y - containerHeight / 2.0f + padding.y;
                    heightToReduceFromElement = (containerHeight - padding.y - padding.w - totalElementsHeight) / widget_children.size();
                }
                else if (vertical_stretch)
                {
                    currentY = widget_transform.position.y - containerHeight / 2.0f + padding.y;
                    heightToAddToElement = (containerHeight - padding.y - padding.w - totalElementsHeight) / widget_children.size();
                }

                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    // It may stretch all the elements up or reduce their length
                    widget_children[i]->widget_transform.size.y += heightToAddToElement + heightToReduceFromElement;

                    // Checking if the widget is longer then container.
                    if (widget_children[i]->widget_transform.size.x >= containerWidth - padding.x - padding.z)
                        widget_children[i]->widget_transform.size.x = containerWidth - padding.x - padding.z;

                    // Set all the elements vertically stretched if its needed
                    if (horizontal_stretch)
                    {
                        widget_children[i]->widget_transform.size.x += containerWidth - padding.x - padding.z - widget_children[i]->widget_transform.size.x;
                        currentX = widget_transform.position.x - containerWidth / 2.0f + widget_children[i]->widget_transform.size.x / 2.0f + padding.x;
                    }
                    // Check if the widget borders with the left padding. If it does we will move it righter
                    else if (widget_children[i]->widget_transform.size.x / 2.0f >= (containerWidth / 2.0f - padding.x))
                    {
                        currentX = widget_transform.position.x - containerWidth / 2.0f + widget_children[i]->widget_transform.size.x / 2.0f + padding.x;
                    }
                    // Check if the widget borders with the right padding. If it does we will move it lefter
                    else if (widget_children[i]->widget_transform.size.x / 2.0f >= (containerWidth / 2.0f - padding.z))
                    {
                        currentX = widget_transform.position.x - containerWidth / 2.0f + widget_children[i]->widget_transform.size.x / 2.0f + padding.z;
                    }

                    // Position the widget in the current row.
                    widget_children[i]->widget_transform.position.x = currentX;
                    widget_children[i]->widget_transform.position.y = currentY + widget_children[i]->widget_transform.size.y / 2.0f;

                    // Reset Y coordinate
                    currentX = widget_transform.position.x;
                    // Move the currentX position to the right for the next widget in the row.
                    currentY += elements_gap_y + widget_children[i]->widget_transform.size.y;
                }
            };

            requestAlignmentRender = false;
            break;
        };

        case Alignment::MiddleRight:
        {
            const float containerWidth = widget_transform.size.x;
            const float containerHeight = widget_transform.size.y;

            if (widget_children.size() == 1)
            {
                // Set X coordinates
                if (widget_children[0]->widget_transform.size.x >= (containerWidth - padding.x - padding.z))
                {
                    widget_children[0]->widget_transform.size.x = containerWidth - padding.x - padding.z;
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x - containerWidth / 2.0f + widget_children[0]->widget_transform.size.x / 2.0f + padding.x;
                }
                else if (horizontal_stretch)
                {
                    widget_children[0]->widget_transform.size.x += containerWidth - widget_children[0]->widget_transform.size.x - padding.x - padding.z;
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x;
                }
                else
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x + containerWidth / 2.0f - widget_children[0]->widget_transform.size.x / 2.0f - padding.z;

                // Set Y coordinates
                if (widget_children[0]->widget_transform.size.y >= (containerHeight - padding.y - padding.w))
                {
                    widget_children[0]->widget_transform.size.y = containerHeight - padding.y - padding.w;
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - containerHeight / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
                }
                else if (vertical_stretch)
                {
                    widget_children[0]->widget_transform.size.y += containerHeight - widget_children[0]->widget_transform.size.y - padding.y - padding.w;
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - widget_transform.size.y / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
                }
                else
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y;
            }
            else if (widget_children.size() > 1)
            {
                // Count total elements width with gaps to set them in the center
                float totalElementsHeight{0.f};
                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    totalElementsHeight += widget_children[i]->widget_transform.size.x;
                }
                totalElementsHeight += (widget_children.size() - 1) * elements_gap_y;

                // Counting additional size in order to stretch all the elements or reduce their length
                float widthToAddToElement = 0.f;
                float heightToAddToElement = 0.f;

                float widthToReduceFromElement = 0.f;
                float heightToReduceFromElement = 0.f;

                // Initial values
                float currentX = widget_transform.position.x - containerWidth / 2.0f + (containerWidth - totalElementsHeight) - padding.z;
                float currentY = widget_transform.position.y;

                if (totalElementsHeight >= (containerWidth - padding.x - padding.z))
                {
                    currentX = widget_transform.position.x - containerWidth / 2.0f + padding.x;
                    widthToReduceFromElement = (containerWidth - padding.z - padding.x - totalElementsHeight) / widget_children.size();
                }
                else if (horizontal_stretch)
                {
                    currentX = widget_transform.position.x - containerWidth / 2.0f + padding.x;
                    widthToAddToElement = (containerWidth - padding.z - padding.x - totalElementsHeight) / widget_children.size();
                }

                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    // It may stretch all the elements up or reduce their length
                    widget_children[i]->widget_transform.size.x += widthToAddToElement + widthToReduceFromElement;

                    // Checking if the widget is higher then container.
                    if (widget_children[i]->widget_transform.size.y >= containerHeight - padding.y - padding.w)
                        widget_children[i]->widget_transform.size.y = containerHeight - padding.y - padding.w;

                    // Set all the elements vertically stretched if its needed
                    if (vertical_stretch)
                    {
                        widget_children[i]->widget_transform.size.y += containerHeight - padding.y - padding.w - widget_children[i]->widget_transform.size.y;
                        currentY = widget_transform.position.y - containerHeight / 2.0f + widget_children[i]->widget_transform.size.y / 2.0f + padding.y;
                    }
                    // Check if the widget borders with the top padding. If it does we will move it lower
                    else if (widget_children[i]->widget_transform.size.y / 2.0f >= (containerHeight / 2.0f - padding.y))
                    {
                        currentY = widget_transform.position.y - containerHeight / 2.0f + widget_children[i]->widget_transform.size.y / 2.0f + padding.y;
                    }
                    // Check if the widget borders with the bottom padding. If it does we will move it upper
                    else if (widget_children[i]->widget_transform.size.y / 2.0f >= (containerHeight / 2.0f - padding.w))
                    {
                        currentY = widget_transform.position.y - containerHeight / 2.0f + widget_children[i]->widget_transform.size.y / 2.0f + padding.w;
                    }

                    // Position the widget in the current row.
                    widget_children[i]->widget_transform.position.x = currentX + widget_children[i]->widget_transform.size.x / 2.0f;
                    widget_children[i]->widget_transform.position.y = currentY;

                    // Reset Y coordinate
                    currentY = widget_transform.position.y;
                    // Move the currentX position to the right for the next widget in the row.
                    currentX += elements_gap_y + widget_children[i]->widget_transform.size.x;
                }
            };

            requestAlignmentRender = false;
            break;
        };

        case Alignment::LowerLeft:
        {
            const float containerWidth = widget_transform.size.x;
            const float containerHeight = widget_transform.size.y;

            if (widget_children.size() == 1)
            {
                // Set X coordinates
                if (widget_children[0]->widget_transform.size.x >= (containerWidth - padding.x - padding.z))
                {
                    widget_children[0]->widget_transform.size.x = containerWidth - padding.x - padding.z;
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x - containerWidth / 2.0f + widget_children[0]->widget_transform.size.x / 2.0f + padding.x;
                }
                else if (horizontal_stretch)
                {
                    widget_children[0]->widget_transform.size.x += containerWidth - widget_children[0]->widget_transform.size.x - padding.x - padding.z;
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x;
                }
                else
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x - containerWidth / 2.0f + widget_children[0]->widget_transform.size.x / 2.0f + padding.x;

                // Set Y coordinates
                if (widget_children[0]->widget_transform.size.y >= (containerHeight - padding.y - padding.w))
                {
                    widget_children[0]->widget_transform.size.y = containerHeight - padding.y - padding.w;
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - containerHeight / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
                }
                else if (vertical_stretch)
                {
                    widget_children[0]->widget_transform.size.y += containerHeight - widget_children[0]->widget_transform.size.y - padding.y - padding.w;
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - widget_transform.size.y / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
                }
                else
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y + widget_transform.size.y / 2.0f - widget_children[0]->widget_transform.size.y / 2.0f - padding.w;
            }
            else if (widget_children.size() > 1)
            {
                // Count total elements width with gaps to set them in the center
                float totalElementsHeight{0.f};
                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    totalElementsHeight += widget_children[i]->widget_transform.size.x;
                }
                totalElementsHeight += (widget_children.size() - 1) * elements_gap_y;

                // Counting additional size in order to stretch all the elements or reduce their length
                float widthToAddToElement = 0.f;
                float heightToAddToElement = 0.f;

                float widthToReduceFromElement = 0.f;
                float heightToReduceFromElement = 0.f;

                // Initial values
                float currentX = widget_transform.position.x - containerWidth / 2.0f + padding.x;
                float currentY = widget_transform.position.y + widget_transform.size.y / 2.0f - padding.w;

                if (totalElementsHeight >= (containerWidth - padding.x - padding.z))
                {
                    widthToReduceFromElement = (containerWidth - padding.z - padding.x - totalElementsHeight) / widget_children.size();
                }
                else if (horizontal_stretch)
                    widthToAddToElement = (containerWidth - padding.z - padding.x - totalElementsHeight) / widget_children.size();

                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    // It may stretch all the elements up or reduce their length
                    widget_children[i]->widget_transform.size.x += widthToAddToElement + widthToReduceFromElement;

                    // Stretch the elements on the vertical axis
                    if (widget_children[i]->widget_transform.size.y >= (containerHeight - padding.y - padding.w))
                    {
                        widget_children[i]->widget_transform.size.y = containerHeight - padding.y - padding.w;
                    }
                    else if (vertical_stretch)
                        widget_children[i]->widget_transform.size.y += containerHeight - padding.y - padding.w - widget_children[i]->widget_transform.size.y;

                    // Position the widget in the current row.
                    widget_children[i]->widget_transform.position.x = currentX + widget_children[i]->widget_transform.size.x / 2.0f;
                    widget_children[i]->widget_transform.position.y = currentY - widget_children[i]->widget_transform.size.y / 2.0f;

                    // Move the currentX position to the right for the next widget in the row.
                    currentX += elements_gap_y + widget_children[i]->widget_transform.size.x;
                }
            };

            requestAlignmentRender = false;
            break;
        };

        case Alignment::LowerCenter:
        {
            const float containerWidth = widget_transform.size.x;
            const float containerHeight = widget_transform.size.y;

            if (widget_children.size() == 1)
            {
                // Set X coordinates
                if (widget_children[0]->widget_transform.size.x >= (containerWidth - padding.x - padding.z))
                {
                    widget_children[0]->widget_transform.size.x = containerWidth - padding.x - padding.z;
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x - containerWidth / 2.0f + widget_children[0]->widget_transform.size.x / 2.0f + padding.x;
                }
                else if (horizontal_stretch)
                {
                    widget_children[0]->widget_transform.size.x += containerWidth - widget_children[0]->widget_transform.size.x - padding.x - padding.z;
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x;
                }
                else
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x;

                // Set Y coordinates
                if (widget_children[0]->widget_transform.size.y >= (containerHeight - padding.y - padding.w))
                {
                    widget_children[0]->widget_transform.size.y = containerHeight - padding.y - padding.w;
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - containerHeight / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
                }
                else if (vertical_stretch)
                {
                    widget_children[0]->widget_transform.size.y += containerHeight - widget_children[0]->widget_transform.size.y - padding.y - padding.w;
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - widget_transform.size.y / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
                }
                else
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y + widget_transform.size.y / 2.0f - widget_children[0]->widget_transform.size.y / 2.0f - padding.w;
            }
            else if (widget_children.size() > 1)
            {
                // Count total elements width with gaps to set them in the center
                float totalElementsHeight{0.f};
                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    totalElementsHeight += widget_children[i]->widget_transform.size.x;
                }
                totalElementsHeight += (widget_children.size() - 1) * elements_gap_y;

                // Counting additional size in order to stretch all the elements or reduce their length
                float widthToAddToElement = 0.f;
                float heightToAddToElement = 0.f;

                float widthToReduceFromElement = 0.f;
                float heightToReduceFromElement = 0.f;

                // Initial values
                float currentX = widget_transform.position.x - containerWidth / 2.0f + (containerWidth - totalElementsHeight) / 2.0f;
                float currentY = widget_transform.position.y + widget_transform.size.y / 2.0f - padding.w;

                if (totalElementsHeight >= (containerWidth - padding.x - padding.z))
                {
                    currentX = widget_transform.position.x - containerWidth / 2.0f + padding.x;
                    widthToReduceFromElement = (containerWidth - padding.z - padding.x - totalElementsHeight) / widget_children.size();
                }
                else if (horizontal_stretch)
                {
                    currentX = widget_transform.position.x - containerWidth / 2.0f + padding.x;
                    widthToAddToElement = (containerWidth - padding.z - padding.x - totalElementsHeight) / widget_children.size();
                }

                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    // It may stretch all the elements up or reduce their length
                    widget_children[i]->widget_transform.size.x += widthToAddToElement + widthToReduceFromElement;

                    // Stretch the elements on the vertical axis
                    if (widget_children[i]->widget_transform.size.y >= (containerHeight - padding.y - padding.w))
                    {
                        widget_children[i]->widget_transform.size.y = containerHeight - padding.y - padding.w;
                    }
                    else if (vertical_stretch)
                        widget_children[i]->widget_transform.size.y += containerHeight - padding.y - padding.w - widget_children[i]->widget_transform.size.y;

                    // Position the widget in the current row.
                    widget_children[i]->widget_transform.position.x = currentX + widget_children[i]->widget_transform.size.x / 2.0f;
                    widget_children[i]->widget_transform.position.y = currentY - widget_children[i]->widget_transform.size.y / 2.0f;

                    // Move the currentX position to the right for the next widget in the row.
                    currentX += elements_gap_y + widget_children[i]->widget_transform.size.x;
                }
            };

            requestAlignmentRender = false;
            break;
        };

        case Alignment::LowerRight:
        {
            const float containerWidth = widget_transform.size.x;
            const float containerHeight = widget_transform.size.y;

            if (widget_children.size() == 1)
            {
                // Set X coordinates
                if (widget_children[0]->widget_transform.size.x >= (containerWidth - padding.x - padding.z))
                {
                    widget_children[0]->widget_transform.size.x = containerWidth - padding.x - padding.z;
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x - containerWidth / 2.0f + widget_children[0]->widget_transform.size.x / 2.0f + padding.x;
                }
                else if (horizontal_stretch)
                {
                    widget_children[0]->widget_transform.size.x += containerWidth - widget_children[0]->widget_transform.size.x - padding.x - padding.z;
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x;
                }
                else
                    widget_children[0]->widget_transform.position.x = widget_transform.position.x + containerWidth / 2.0f - widget_children[0]->widget_transform.size.x / 2.0f - padding.z;

                // Set Y coordinates
                if (widget_children[0]->widget_transform.size.y >= (containerHeight - padding.y - padding.w))
                {
                    widget_children[0]->widget_transform.size.y = containerHeight - padding.y - padding.w;
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - containerHeight / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
                }
                else if (vertical_stretch)
                {
                    widget_children[0]->widget_transform.size.y += containerHeight - widget_children[0]->widget_transform.size.y - padding.y - padding.w;
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y - widget_transform.size.y / 2.0f + widget_children[0]->widget_transform.size.y / 2.0f + padding.y;
                }
                else
                    widget_children[0]->widget_transform.position.y = widget_transform.position.y + widget_transform.size.y / 2.0f - widget_children[0]->widget_transform.size.y / 2.0f - padding.w;
            }
            else if (widget_children.size() > 1)
            {
                // Count total elements width with gaps to set them in the center
                float totalElementsHeight{0.f};
                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    totalElementsHeight += widget_children[i]->widget_transform.size.x;
                }
                totalElementsHeight += (widget_children.size() - 1) * elements_gap_y;

                // Counting additional size in order to stretch all the elements or reduce their length
                float widthToAddToElement = 0.f;
                float heightToAddToElement = 0.f;

                float widthToReduceFromElement = 0.f;
                float heightToReduceFromElement = 0.f;

                // Initial values
                float currentX = widget_transform.position.x - containerWidth / 2.0f + (containerWidth - totalElementsHeight) - padding.z;
                float currentY = widget_transform.position.y + widget_transform.size.y / 2.0f - padding.w;

                if (totalElementsHeight >= (containerWidth - padding.x - padding.z))
                {
                    currentX = widget_transform.position.x - containerWidth / 2.0f + padding.x;
                    widthToReduceFromElement = (containerWidth - padding.z - padding.x - totalElementsHeight) / widget_children.size();
                }
                else if (horizontal_stretch)
                {
                    currentX = widget_transform.position.x - containerWidth / 2.0f + padding.x;
                    widthToAddToElement = (containerWidth - padding.z - padding.x - totalElementsHeight) / widget_children.size();
                }

                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    // It may stretch all the elements up or reduce their length
                    widget_children[i]->widget_transform.size.x += widthToAddToElement + widthToReduceFromElement;

                    // Stretch the elements on the vertical axis
                    if (widget_children[i]->widget_transform.size.y >= (containerHeight - padding.y - padding.w))
                    {
                        widget_children[i]->widget_transform.size.y = containerHeight - padding.y - padding.w;
                    }
                    else if (vertical_stretch)
                        widget_children[i]->widget_transform.size.y += containerHeight - padding.y - padding.w - widget_children[i]->widget_transform.size.y;

                    // Position the widget in the current row.
                    widget_children[i]->widget_transform.position.x = currentX + widget_children[i]->widget_transform.size.x / 2.0f;
                    widget_children[i]->widget_transform.position.y = currentY - widget_children[i]->widget_transform.size.y / 2.0f;

                    // Move the currentX position to the right for the next widget in the row.
                    currentX += elements_gap_y + widget_children[i]->widget_transform.size.x;
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