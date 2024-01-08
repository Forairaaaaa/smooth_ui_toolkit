/**
 * @file smooth_selector.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "smooth_selector.h"

using namespace SmoothUIToolKit::SelectMenu;

void SmoothSelector::goLast()
{
    _data.selected_option_index--;
    if (_data.selected_option_index < 0)
        _data.selected_option_index = _config.moveInLoop ? _data.option_list.size() - 1 : 0;
    _data.is_changed = true;
}

void SmoothSelector::goNext()
{
    _data.selected_option_index++;
    if (_data.selected_option_index >= _data.option_list.size())
        _data.selected_option_index = _config.moveInLoop ? 0 : _data.option_list.size() - 1;
    _data.is_changed = true;
}

void SmoothSelector::press(const Vector4D_t& pressedKeyframe) {}
void SmoothSelector::release() {}
void SmoothSelector::open(const Vector4D_t& pressedKeyframe) {}
void SmoothSelector::close() {}

void SmoothSelector::update(const TimeSize_t& currentTime)
{
    // Callback
    onUpdate(currentTime);

    // Read input callback
    if (currentTime - _data.read_input_time_count > _config.readInputInterval)
    {
        onReadInput();
        _data.read_input_time_count = currentTime;
    }

    // Update
    if (_data.is_changed)
    {
        _data.is_changed = false;
        _update_selector_keyframe();
        _update_camera_keyframe();
    }
    _data.selector_postion.update(currentTime);
    _data.selector_shape.update(currentTime);
    _data.camera_offset.update(currentTime);

    // Render callback
    if (currentTime - _data.render_time_count > _config.renderInterval)
    {
        onRender();
        _data.render_time_count = currentTime;
    }

    // On click callback
    if (_data.was_released)
    {
        
    }
}

void SmoothSelector::_update_selector_keyframe()
{
    _data.selector_postion.moveTo(_data.option_list[_data.selected_option_index].keyframe.x,
                                  _data.option_list[_data.selected_option_index].keyframe.y);
    _data.selector_shape.reshapeTo(_data.option_list[_data.selected_option_index].keyframe.w,
                                   _data.option_list[_data.selected_option_index].keyframe.h);
}

void SmoothSelector::_update_camera_keyframe()
{
    if (_config.cameraSize.width == 0 && _config.cameraSize.height == 0)
        return;

    // Check if selector's target frame is inside of camera
    int new_x_offset = getCameraOffset().x;
    int new_y_offset = getCameraOffset().y;

    // Left
    if (getSelectedKeyframe().x < new_x_offset)
        new_x_offset = getSelectedKeyframe().x;
    // Right
    else if (getSelectedKeyframe().x + getSelectedKeyframe().w > new_x_offset + _config.cameraSize.width)
        new_x_offset = getSelectedKeyframe().x + getSelectedKeyframe().w;

    // Top
    if (getSelectedKeyframe().y < new_y_offset)
        new_y_offset = getSelectedKeyframe().y;

    // Bottom
    else if (getSelectedKeyframe().y + getSelectedKeyframe().h > new_y_offset + _config.cameraSize.height)
        new_y_offset = getSelectedKeyframe().y + getSelectedKeyframe().h;

    _data.camera_offset.moveTo(new_x_offset, new_y_offset);
}
