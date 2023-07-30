#include "Container.hpp"

void Container::SetElementsAlignment(Alignment elements_alignment)
{
    container_alignment = elements_alignment;
    requestAlignmentRender = true;
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
    if (requestAlignmentRender)
    {
        switch (container_alignment)
        {
        case Alignment::RowUpperLeft:
        {
            const float containerWidth = widget_transform.size.x;

            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x = widget_transform.position.x - containerWidth * widget_pivot_point.x;
                widget_children[0]->widget_transform.position.y = widget_transform.position.y - widget_transform.size.y * widget_pivot_point.y;
            }
            else if (widget_children.size() > 1)
            {
                // Initial values of the first row are equal to the first element
                float rowHeight = widget_children[0]->widget_transform.size.y;
                float rowWidth = widget_children[0]->widget_transform.size.x;
                int currentRow = 0;
                float currentX = widget_transform.position.x - containerWidth * widget_pivot_point.x;
                float currentY = widget_transform.position.y - widget_transform.size.y * widget_pivot_point.y;

                // Position the first widget in the first row.
                widget_children[0]->widget_transform.position.x = currentX + widget_children[0]->widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y = currentY + widget_children[0]->widget_transform.size.y / 2.0f;
                currentX += elements_gap.x + widget_children[0]->widget_transform.size.x;
                for (size_t i = 1; i < widget_children.size(); i++)
                {
                    // Check if the current widget can fit in the current row.
                    if (rowWidth + elements_gap.x + widget_children[i]->widget_transform.size.x <= containerWidth)
                    {
                        // Position the widget in the current row.
                        widget_children[i]->widget_transform.position.x = currentX + widget_children[i]->widget_transform.size.x / 2.0f;
                        widget_children[i]->widget_transform.position.y = currentY + widget_children[i]->widget_transform.size.y / 2.0f;

                        // Update the row width and height.
                        rowWidth += elements_gap.x + widget_children[i]->widget_transform.size.x;
                        rowHeight = std::max(rowHeight, widget_children[i]->widget_transform.size.y);

                        // Move the currentX position to the right for the next widget in the row.
                        currentX += elements_gap.x + widget_children[i]->widget_transform.size.x;
                    }
                    else
                    {
                        // Start a new row because the current widget cannot fit in the current row.
                        currentX = widget_transform.position.x - containerWidth * widget_pivot_point.x;
                        currentY += rowHeight + elements_gap.y + widget_children[i]->widget_transform.size.y / 2.0f; // Move the currentY position to start a new row.

                        // Reset the row width and height for the new row.
                        rowWidth = widget_children[i]->widget_transform.size.x;
                        rowHeight = widget_children[i]->widget_transform.size.y;

                        // Position the widget in the new row.
                        widget_children[i]->widget_transform.position.x = currentX + widget_children[i]->widget_transform.size.x / 2.0f;
                        widget_children[i]->widget_transform.position.y = currentY + widget_children[i]->widget_transform.size.y / 2.0f;

                        // Move the currentX position to the right for the next widget in the new row.
                        currentX += widget_children[i]->widget_transform.size.x + elements_gap.x;
                    }
                }
            };

            requestAlignmentRender = false;
            break;
        };

        case Alignment::RowUpperCenter:
        {
            const float containerWidth = widget_transform.size.x;

            if (widget_children.size() == 1)
            {
                // Center the single widget horizontally and vertically within the container.
                widget_children[0]->widget_transform.position.x = widget_transform.position.x;
                widget_children[0]->widget_transform.position.y = widget_transform.position.y;
            }
            else if (widget_children.size() > 1)
            {
                // We are calculating the total width of each row before we start positioning the widgets
                // It is needed to center the widgets in each row
                float totalRowWidth = widget_children[0]->widget_transform.size.x;
                std::vector<float> totalRowsWidths;
                for (size_t i = 1; i < widget_children.size(); i++)
                {
                    if (totalRowWidth + elements_gap.x + widget_children[i]->widget_transform.size.x <= containerWidth)
                    {
                        totalRowWidth += elements_gap.x + widget_children[i]->widget_transform.size.x;
                    }
                    else
                    {
                        totalRowsWidths.push_back(totalRowWidth);
                        totalRowWidth = widget_children[i]->widget_transform.size.x;
                    }
                }
                totalRowsWidths.push_back(totalRowWidth);

                // Initial values of the first row are equal to the first element
                float rowHeight = widget_children[0]->widget_transform.size.y;
                float rowWidth = widget_children[0]->widget_transform.size.x;
                int currentRow = 0;
                float currentX = widget_transform.position.x - containerWidth * widget_pivot_point.x + (containerWidth - totalRowsWidths[0]) / 2.0f;
                float currentY = widget_transform.position.y - widget_transform.size.y * widget_pivot_point.y;

                // Position the first widget in the first row.
                widget_children[0]->widget_transform.position.x = currentX + widget_children[0]->widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y = currentY + widget_children[0]->widget_transform.size.y / 2.0f;
                currentX += elements_gap.x + widget_children[0]->widget_transform.size.x;

                for (size_t i = 1; i < widget_children.size(); i++)
                {
                    // Check if the current widget can fit in the current row.
                    if (rowWidth + elements_gap.x + widget_children[i]->widget_transform.size.x <= containerWidth)
                    {
                        // Position the widget in the current row.
                        widget_children[i]->widget_transform.position.x = currentX + widget_children[i]->widget_transform.size.x / 2.0f;
                        widget_children[i]->widget_transform.position.y = currentY + widget_children[i]->widget_transform.size.y / 2.0f;

                        // Update the row width and height.
                        rowWidth += elements_gap.x + widget_children[i]->widget_transform.size.x;
                        rowHeight = std::max(rowHeight, widget_children[i]->widget_transform.size.y);

                        // Move the currentX position to the right for the next widget in the row.
                        currentX += elements_gap.x + widget_children[i]->widget_transform.size.x;
                    }
                    else
                    {
                        // Start a new row because the current widget cannot fit in the current row.
                        currentRow++;
                        currentX = widget_transform.position.x - containerWidth * widget_pivot_point.x + (containerWidth - totalRowsWidths[currentRow]) / 2.0f;
                        currentY += rowHeight + elements_gap.y + widget_children[i]->widget_transform.size.y / 2.0f; // Move the currentY position to start a new row.

                        // Reset the row width and height for the new row.
                        rowWidth = widget_children[i]->widget_transform.size.x;
                        rowHeight = widget_children[i]->widget_transform.size.y;

                        // Position the widget in the new row.
                        widget_children[i]->widget_transform.position.x = currentX + widget_children[i]->widget_transform.size.x / 2.0f;
                        widget_children[i]->widget_transform.position.y = currentY + widget_children[i]->widget_transform.size.y / 2.0f;

                        // Move the currentX position to the right for the next widget in the new row.
                        currentX += widget_children[i]->widget_transform.size.x + elements_gap.x;
                    }
                }
            }

            requestAlignmentRender = false;
            break;
        };

        case Alignment::RowUpperRight:
            // setting only one element
            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x - widget_transform.size.x * widget_pivot_point.x + widget_children[0]->widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y - widget_transform.size.y * widget_pivot_point.y + widget_children[0]->widget_transform.size.y / 2.0f;
            }
            else if (widget_children.size() > 1)
            {
                // getting the highest element for centring all the elements
                float highest_element = 0.f;
                for (size_t i = 0; i < widget_children.size(); i++)
                {
                    if (widget_children[i]->widget_transform.size.y > highest_element)
                        highest_element = widget_children[i]->widget_transform.size.y;
                }

                // setting the first element in the left side of the container
                widget_children[0]->widget_transform.position.x += widget_transform.position.x - widget_transform.size.x * widget_pivot_point.x + widget_children[0]->widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y - widget_transform.size.y * widget_pivot_point.y + highest_element / 2.0f;

                // setting next elements according to the first one
                for (size_t i = 1; i < widget_children.size(); i++)
                {
                    widget_children[i]->widget_transform.position.x += widget_children[i - 1]->widget_transform.position.x + widget_children[i - 1]->widget_transform.size.x / 2.0f + widget_children[i]->widget_transform.size.x / 2.0f;
                    widget_children[i]->widget_transform.position.y += widget_transform.position.y - widget_transform.size.y * widget_pivot_point.y + highest_element / 2.0f;
                };
            }

            requestAlignmentRender = false;
            break;
        case Alignment::RowMiddleLeft:
            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x - widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y;
            }
            else if (widget_children.size() > 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x - widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y;

                for (size_t i = 1; i < widget_children.size(); i++)
                {
                    widget_children[i + 1]->widget_transform.position.x += widget_transform.position.x - widget_transform.size.x / 2.0f;
                    widget_children[i + 1]->widget_transform.position.y += widget_children[i]->widget_transform.position.y;
                };
            }
            requestAlignmentRender = false;
            break;
        case Alignment::RowMiddleCenter:
            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y;
            }
            else if (widget_children.size() > 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y;

                for (size_t i = 1; i < widget_children.size(); i++)
                {
                    widget_children[i + 1]->widget_transform.position.x += widget_children[i]->widget_transform.position.x;
                    widget_children[i + 1]->widget_transform.position.y += widget_children[i]->widget_transform.position.y;
                };
            }
            requestAlignmentRender = false;
            break;
        case Alignment::RowMiddleRight:
            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x + widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y;
            }
            else if (widget_children.size() > 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x + widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y;

                for (size_t i = 1; i < widget_children.size(); i++)
                {
                    widget_children[i + 1]->widget_transform.position.x += widget_children[i]->widget_transform.position.x + widget_transform.size.x / 2.0f;
                    widget_children[i + 1]->widget_transform.position.y += widget_children[i]->widget_transform.position.y;
                };
            }
            requestAlignmentRender = false;
            break;
        case Alignment::RowLowerLeft:
            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x - widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y + widget_transform.size.y / 2.0f;
            }
            else if (widget_children.size() > 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x - widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y + widget_transform.size.y / 2.0f;

                for (size_t i = 1; i < widget_children.size(); i++)
                {
                    widget_children[i + 1]->widget_transform.position.x += widget_children[i]->widget_transform.position.x - widget_transform.size.x / 2.0f;
                    widget_children[i + 1]->widget_transform.position.y += widget_children[i]->widget_transform.position.y + widget_transform.size.y / 2.0f;
                };
            }
            requestAlignmentRender = false;
            break;
        case Alignment::RowLowerCenter:
            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y + widget_transform.size.y / 2.0f;
            }
            else if (widget_children.size() > 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y + widget_transform.size.y / 2.0f;

                for (size_t i = 1; i < widget_children.size(); i++)
                {
                    widget_children[i + 1]->widget_transform.position.x += widget_children[i]->widget_transform.position.x;
                    widget_children[i + 1]->widget_transform.position.y += widget_children[i]->widget_transform.position.y + widget_transform.size.y / 2.0f;
                };
            }
            requestAlignmentRender = false;
            break;
        case Alignment::RowLowerRight:
            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x + widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y + widget_transform.size.y / 2.0f;
            }
            else if (widget_children.size() > 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x + widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y + widget_transform.size.y / 2.0f;

                for (size_t i = 1; i < widget_children.size(); i++)
                {
                    widget_children[i + 1]->widget_transform.position.x += widget_children[i]->widget_transform.position.x + widget_transform.size.x / 2.0f;
                    widget_children[i + 1]->widget_transform.position.y += widget_children[i]->widget_transform.position.y + widget_transform.size.y / 2.0f;
                };
            }
            requestAlignmentRender = false;
            break;
        case Alignment::ColUpperLeft:
            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x - widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y - widget_transform.size.y / 2.0f;
            }
            else if (widget_children.size() > 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x - widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y - widget_transform.size.y / 2.0f;

                for (size_t i = 1; i < widget_children.size(); i++)
                {
                    widget_children[i]->widget_transform.position.x += widget_children[i - 1]->widget_transform.position.x;
                    widget_children[i]->widget_transform.position.y += widget_children[i - 1]->widget_transform.position.y - widget_transform.size.y / 2.0f;
                };
            }
            requestAlignmentRender = false;
            break;
        case Alignment::ColUpperCenter:
            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y - widget_transform.size.y / 2.0f;
            }
            else if (widget_children.size() > 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y - widget_transform.size.y / 2.0f;

                for (size_t i = 1; i < widget_children.size(); i++)
                {
                    widget_children[i]->widget_transform.position.x += widget_children[i - 1]->widget_transform.position.x;
                    widget_children[i]->widget_transform.position.y += widget_children[i - 1]->widget_transform.position.y - widget_transform.size.y / 2.0f;
                };
            }
            requestAlignmentRender = false;
            break;
        case Alignment::ColUpperRight:
            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x + widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y - widget_transform.size.y / 2.0f;
            }
            else if (widget_children.size() > 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x + widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y - widget_transform.size.y / 2.0f;

                for (size_t i = 1; i < widget_children.size(); i++)
                {
                    widget_children[i]->widget_transform.position.x += widget_children[i - 1]->widget_transform.position.x;
                    widget_children[i]->widget_transform.position.y += widget_children[i - 1]->widget_transform.position.y - widget_transform.size.y / 2.0f;
                };
            }
            requestAlignmentRender = false;
            break;
        case Alignment::ColMiddleLeft:
            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x - widget_transform.size.x / 2.0f;
            }
            else if (widget_children.size() > 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x - widget_transform.size.x / 2.0f;

                for (size_t i = 1; i < widget_children.size(); i++)
                {
                    widget_children[i]->widget_transform.position.x += widget_children[i - 1]->widget_transform.position.x - widget_transform.size.x / 2.0f;
                    widget_children[i]->widget_transform.position.y += widget_children[i - 1]->widget_transform.position.y;
                };
            }
            requestAlignmentRender = false;
            break;
        case Alignment::ColMiddleCenter:
            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x;
            }
            else if (widget_children.size() > 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x;

                for (size_t i = 1; i < widget_children.size(); i++)
                {
                    widget_children[i]->widget_transform.position.x += widget_children[i - 1]->widget_transform.position.x;
                    widget_children[i]->widget_transform.position.y += widget_children[i - 1]->widget_transform.position.y;
                };
            }
            requestAlignmentRender = false;
            break;
        case Alignment::ColMiddleRight:
            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x + widget_transform.size.x / 2.0f;
            }
            else if (widget_children.size() > 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x + widget_transform.size.x / 2.0f;

                for (size_t i = 1; i < widget_children.size(); i++)
                {
                    widget_children[i]->widget_transform.position.x += widget_children[i - 1]->widget_transform.position.x + widget_transform.size.x / 2.0f;
                    widget_children[i]->widget_transform.position.y += widget_children[i - 1]->widget_transform.position.y;
                };
            }
            requestAlignmentRender = false;
            break;
        case Alignment::ColLowerLeft:
            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x - widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y + widget_transform.size.y / 2.0f;
            }
            else if (widget_children.size() > 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x - widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y + widget_transform.size.y / 2.0f;

                for (size_t i = 1; i < widget_children.size(); i++)
                {
                    widget_children[i]->widget_transform.position.x += widget_children[i - 1]->widget_transform.position.x - widget_transform.size.x / 2.0f;
                    widget_children[i]->widget_transform.position.y += widget_children[i - 1]->widget_transform.position.y + widget_transform.size.y / 2.0f;
                };
            }
            requestAlignmentRender = false;
            break;
        case Alignment::ColLowerCenter:
            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y + widget_transform.size.y / 2.0f;
            }
            else if (widget_children.size() > 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y + widget_transform.size.y / 2.0f;

                for (size_t i = 1; i < widget_children.size(); i++)
                {
                    widget_children[i]->widget_transform.position.x += widget_children[i - 1]->widget_transform.position.x;
                    widget_children[i]->widget_transform.position.y += widget_children[i - 1]->widget_transform.position.y + widget_transform.size.y / 2.0f;
                };
            }
            requestAlignmentRender = false;
            break;
        case Alignment::ColLowerRight:
            if (widget_children.size() == 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x + widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y + widget_transform.size.y / 2.0f;
            }
            else if (widget_children.size() > 1)
            {
                widget_children[0]->widget_transform.position.x += widget_transform.position.x + widget_transform.size.x / 2.0f;
                widget_children[0]->widget_transform.position.y += widget_transform.position.y + widget_transform.size.y / 2.0f;

                for (size_t i = 1; i < widget_children.size(); i++)
                {
                    widget_children[i]->widget_transform.position.x += widget_children[i - 1]->widget_transform.position.x + widget_transform.size.x / 2.0f;
                    widget_children[i]->widget_transform.position.y += widget_children[i - 1]->widget_transform.position.y + widget_transform.size.y / 2.0f;
                };
            }
            requestAlignmentRender = false;
            break;
        default:
            break;
        }
    }
}