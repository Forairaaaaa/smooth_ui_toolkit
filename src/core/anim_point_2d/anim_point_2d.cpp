/**
 * @file anim_point_2d.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-12-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "anim_point_2d.h"


using namespace SMOOTH_UI_TK;


AnimPoint2D::AnimPoint2D(int startX, int startY)
{
    // Start point 
    _move_to_no_anim(startX, startY);
}


void AnimPoint2D::moveTo(int x, int y)
{
    // Set target and flag on 
    _data.target_point.reset(x, y);
    _data.is_target_changed = true;
}


void AnimPoint2D::update(uint32_t currentTime)
{
    // If moved 
    if (_data.is_target_changed)
    {
        _data.is_target_changed = false;
        
        // Reset anim 
        _data.anim_x.setAnim(_config.anim_path_x, _data.anim_x.getValue(currentTime), _data.target_point.x, _config.anim_time_x);
        _data.anim_y.setAnim(_config.anim_path_y, _data.anim_y.getValue(currentTime), _data.target_point.y, _config.anim_time_y);

        // Reset time offset 
        _data.anim_x.resetTime(currentTime);
        _data.anim_y.resetTime(currentTime);
    }

    // Update current point 
    _data.current_point.x = _data.anim_x.getValue(currentTime);
    _data.current_point.y = _data.anim_y.getValue(currentTime);
}


void AnimPoint2D::_move_to_no_anim(int x, int y)
{
    _data.is_target_changed = false;
    _data.anim_x.setAnim(_config.anim_path_x, x, x, 0);
    _data.anim_x.setAnim(_config.anim_path_y, y, y, 0);
    _data.current_point.reset(x, y);
    _data.target_point.reset(x, y);
}


