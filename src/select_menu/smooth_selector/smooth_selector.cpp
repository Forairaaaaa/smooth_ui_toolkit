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
    if (_data.option_list.size() == 0)
        return;

    _data.selected_option_index--;
    if (_data.selected_option_index < 0)
        _data.selected_option_index = _config.moveInLoop ? _data.option_list.size() - 1 : 0;
    _data.is_changed = true;

    // Callback
    onGoLast();
}

void SmoothSelector::goNext()
{
    if (_data.option_list.size() == 0)
        return;

    _data.selected_option_index++;
    if (_data.selected_option_index >= _data.option_list.size())
        _data.selected_option_index = _config.moveInLoop ? 0 : _data.option_list.size() - 1;
    _data.is_changed = true;

    // Callback
    onGoNext();
}

void SmoothSelector::moveTo(int optionIndex)
{
    if (optionIndex < 0 || optionIndex > (_data.option_list.size() - 1))
        return;

    // Update tarnsition target
    _data.selected_option_index = optionIndex;
    _data.selector_postion.moveTo(_data.option_list[optionIndex].keyframe.x, _data.option_list[optionIndex].keyframe.y);
    _data.selector_shape.reshapeTo(_data.option_list[optionIndex].keyframe.w, _data.option_list[optionIndex].keyframe.h);
}

void SmoothSelector::jumpTo(int optionIndex)
{
    if (optionIndex < 0 || optionIndex > (_data.option_list.size() - 1))
        return;

    // Update tarnsition target
    _data.selected_option_index = optionIndex;
    _data.selector_postion.jumpTo(_data.option_list[optionIndex].keyframe.x, _data.option_list[optionIndex].keyframe.y);
    _data.selector_shape.resizeTo(_data.option_list[optionIndex].keyframe.w, _data.option_list[optionIndex].keyframe.h);
}

void SmoothSelector::press(const Vector4D_t& pressedKeyframe)
{
    _data.is_pressing = true;

    // Update tarnsition target
    _data.selector_postion.moveTo(pressedKeyframe.x, pressedKeyframe.y);
    _data.selector_shape.reshapeTo(pressedKeyframe.w, pressedKeyframe.h);

    // Callback
    onPress();
}

void SmoothSelector::release()
{
    // Let update to change it back
    _data.is_changed = true;
    _data.was_released = true;

    // Callback
    onRelease();
}

void SmoothSelector::open(const Vector4D_t& pressedKeyframe)
{
    _data.is_opening = true;
    _data.was_opened = true;

    // Update tarnsition target
    _data.selector_postion.moveTo(pressedKeyframe.x, pressedKeyframe.y);
    _data.selector_shape.reshapeTo(pressedKeyframe.w, pressedKeyframe.h);
}

void SmoothSelector::close()
{
    _data.is_changed = true;
    _data.is_opening = false;
}

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
        // Check if transition is done
        if (_data.selector_postion.isFinish() && _data.selector_shape.isFinish())
        {
            _data.was_released = false;
            _data.is_pressing = false;
            onClick();
        }
    }

    // On open end callback
    if (_data.was_opened)
    {
        // Check if transition is done
        if (_data.selector_postion.isFinish() && _data.selector_shape.isFinish())
        {
            _data.was_opened = false;
            onOpenEnd();
        }
    }
}

void SmoothSelector::_update_selector_keyframe()
{
    if (_data.option_list.size() == 0)
        return;

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
        new_x_offset = getSelectedKeyframe().x + getSelectedKeyframe().w - _config.cameraSize.width;

    // Top
    if (getSelectedKeyframe().y < new_y_offset)
        new_y_offset = getSelectedKeyframe().y;

    // Bottom
    else if (getSelectedKeyframe().y + getSelectedKeyframe().h > new_y_offset + _config.cameraSize.height)
        new_y_offset = getSelectedKeyframe().y + getSelectedKeyframe().h - _config.cameraSize.height;

    _data.camera_offset.moveTo(new_x_offset, new_y_offset);
}
