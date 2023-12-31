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
}


