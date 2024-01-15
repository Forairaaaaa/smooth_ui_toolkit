/**
 * @file base.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-04
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "base.h"
using namespace SmoothUIToolKit::SmoothWidget;

void WidgetBase::update(const std::uint32_t& currentTime)
{
    // Self update
    onUpdate(currentTime);
    // Children update
    _invoke_children_update(currentTime);
}

void WidgetBase::hover(const int& x, const int& y)
{
    if (_is_on_widget(x, y))
    {
        // If already hovering
        if (_data.is_hovering)
            onHovering(x, y);

        // If on hover
        else
        {
            _data.is_hovering = true;
            onHover();
        }

        _invoke_children_hover(x, y);
    }
    // If on hover leave
    else if (_data.is_hovering)
    {
        _data.is_hovering = false;
        onHoverEnd();

        // One last kick to tell children the hover is gone
        _invoke_children_hover(x, y);
    }
}

void WidgetBase::drag(const int& x, const int& y)
{
    // If already dragging
    if (_data.is_dragging)
    {
        onDragging(x, y);
        _invoke_children_drag(x, y);
    }

    // If on drag (just start dragging)
    else if (_is_on_widget(x, y))
    {
        _data.is_dragging = true;
        onDrag();
        _invoke_children_drag(x, y);
    }
}

void WidgetBase::drop()
{
    // On drop
    if (_data.is_dragging)
    {
        _data.is_dragging = false;
        onDrop();
        _invoke_children_drop();
    }
}

void WidgetBase::addChild(WidgetBase* child)
{
    if (child != nullptr && isChild(child))
        _children.push_back(child);
}

bool WidgetBase::isChild(WidgetBase* child)
{
    for (const auto& i : _children)
    {
        if (child == i)
            return true;
    }
    return false;
}

bool WidgetBase::_is_on_widget(const int& x, const int& y)
{
    if (x < _position.x || x > _position.x + _size.width)
        return false;
    if (y < _position.y || y > _position.y + _size.height)
        return false;
    return true;
}

void WidgetBase::_invoke_children_update(const std::uint32_t& currentTime)
{
    for (const auto i : _children)
        i->update(currentTime);
}

void WidgetBase::_invoke_children_hover(const int& x, const int& y)
{
    for (const auto i : _children)
        i->hover(x, y);
}

void WidgetBase::_invoke_children_drag(const int& x, const int& y)
{
    for (const auto i : _children)
        i->drag(x, y);
}

void WidgetBase::_invoke_children_drop()
{
    for (const auto i : _children)
        i->drop();
}
