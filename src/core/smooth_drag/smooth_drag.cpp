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
            int new_x = _config.lockXOffset ? _data.drag_start_offset.x : _data.drag_start_offset.x + x - _data.drag_start_point.x;
            int new_y = _config.lockYOffset ? _data.drag_start_offset.y : _data.drag_start_offset.y + y - _data.drag_start_point.y;
            moveTo(new_x, new_y);
            return;
        }

        // Update dragging offset 
        moveTo(
            _data.drag_start_offset.x + x - _data.drag_start_point.x,
            _data.drag_start_offset.y + y - _data.drag_start_point.y
        );
        return;
    }

    // Start dragging 
    _data.is_dragging = true;
    _data.drag_start_point.x = x;
    _data.drag_start_point.y = y;
    _data.drag_start_offset = getValue();
}


void SmoothDrag::drop()
{
    _data.is_dragging = false;

    // Auto reset offset 
    if (_config.autoReset)
    {
        moveTo(0, 0);
        return;
    }

    if (_config.offsetLimit)
    {
        int new_x = Clamp(getTargetPoint().x, _config.xOffsetLimit);
        int new_y = Clamp(getTargetPoint().y, _config.yOffsetLimit);
        moveTo(new_x, new_y);
    }
}


