/**
 * @file smooth_drag.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-12-31
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "smooth_drag.h"

using namespace SmoothUIToolKit;

void SmoothDrag::drag(const int& x, const int& y)
{
    if (_data.is_dragging)
    {
        // If locked some shit
        if (_config.lockXOffset || _config.lockYOffset)
        {
            _data.target_buffer.x =
                _config.lockXOffset ? _data.drag_start_offset.x : _data.drag_start_offset.x + x - _data.drag_start_point.x;
            _data.target_buffer.y =
                _config.lockYOffset ? _data.drag_start_offset.y : _data.drag_start_offset.y + y - _data.drag_start_point.y;
        }
        else
        {
            _data.target_buffer.x = _data.drag_start_offset.x + x - _data.drag_start_point.x;
            _data.target_buffer.y = _data.drag_start_offset.y + y - _data.drag_start_point.y;
        }

        // If not allow to dragging out of limit
        if (!_config.allowDraggingOutOfLimit)
        {
            _data.target_buffer.x = Clamp(_data.target_buffer.x, _config.xOffsetLimit);
            _data.target_buffer.y = Clamp(_data.target_buffer.y, _config.yOffsetLimit);
        }

        // Update dragging offset
        moveTo(_data.target_buffer.x, _data.target_buffer.y);
        return;
    }

    // Start dragging
    _data.is_dragging = true;
    _data.drag_start_point.x = x;
    _data.drag_start_point.y = y;
    _data.drag_start_offset = getValue();

    // Update to drag transition path
    Transition2D::setTransitionPath(_config.dragTransitionPath);
}

void SmoothDrag::drop()
{
    _data.is_dragging = false;

    // Auto reset offset
    if (_config.autoReset)
    {
        // Update to drag transition path
        Transition2D::setTransitionPath(_config.resetTransitionPath);
        moveTo(0, 0);
        return;
    }

    if (_config.offsetLimit)
    {
        int new_x = Clamp(getTargetPoint().x, _config.xOffsetLimit, _data.is_in_range);
        if (!_data.is_in_range)
        {
            Transition2D::setTransitionPath(_config.resetTransitionPath);
        }
        int new_y = Clamp(getTargetPoint().y, _config.yOffsetLimit, _data.is_in_range);
        if (!_data.is_in_range)
        {
            Transition2D::setTransitionPath(_config.resetTransitionPath);
        }
        moveTo(new_x, new_y);
    }
}
