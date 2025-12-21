/**
 * @file smooth_selector.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-08-16
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "smooth_selector.hpp"
#include "core/math/vector.hpp"

using namespace smooth_ui_toolkit;

void SmoothSelectorMenu::goLast()
{
    if (_data.option_list.size() == 0) {
        return;
    }

    _data.selected_option_index--;
    if (_data.selected_option_index < 0) {
        _data.selected_option_index = _config.moveInLoop ? _data.option_list.size() - 1 : 0;
    }
    _data.is_changed = true;

    // Callback
    onGoLast();
}

void SmoothSelectorMenu::goNext()
{
    if (_data.option_list.size() == 0) {
        return;
    }

    _data.selected_option_index++;
    if (_data.selected_option_index >= _data.option_list.size()) {
        _data.selected_option_index = _config.moveInLoop ? 0 : _data.option_list.size() - 1;
    }
    _data.is_changed = true;

    // Callback
    onGoNext();
}

void SmoothSelectorMenu::moveTo(int optionIndex)
{
    if (optionIndex < 0 || optionIndex > (_data.option_list.size() - 1)) {
        return;
    }

    // Update tarnsition target
    _data.selected_option_index = optionIndex;
    _data.selector_postion.move(_data.option_list[optionIndex].keyframe.x, _data.option_list[optionIndex].keyframe.y);
    _data.selector_shape.move(_data.option_list[optionIndex].keyframe.width,
                              _data.option_list[optionIndex].keyframe.height);
}

void SmoothSelectorMenu::jumpTo(int optionIndex)
{
    if (optionIndex < 0 || optionIndex > (_data.option_list.size() - 1)) {
        return;
    }

    // Update tarnsition target
    _data.selected_option_index = optionIndex;
    _data.selector_postion.move(_data.option_list[optionIndex].keyframe.x, _data.option_list[optionIndex].keyframe.y);
    _data.selector_shape.move(_data.option_list[optionIndex].keyframe.width,
                              _data.option_list[optionIndex].keyframe.height);
}

void SmoothSelectorMenu::press(const Vector4& pressedKeyframe)
{
    _data.is_pressing = true;

    // Update tarnsition target
    _data.selector_postion.move(pressedKeyframe.x, pressedKeyframe.y);
    _data.selector_shape.move(pressedKeyframe.width, pressedKeyframe.height);

    // Callback
    onPress();
}

void SmoothSelectorMenu::release()
{
    // Let update to change it back
    _data.is_changed = true;
    _data.was_released = true;

    // Callback
    onRelease();
}

void SmoothSelectorMenu::open(const Vector4& pressedKeyframe)
{
    _data.is_opening = true;
    _data.was_opened = true;

    // Update tarnsition target
    _data.selector_postion.move(pressedKeyframe.x, pressedKeyframe.y);
    _data.selector_shape.move(pressedKeyframe.width, pressedKeyframe.height);
}

void SmoothSelectorMenu::close()
{
    _data.is_changed = true;
    _data.is_opening = false;
}

void SmoothSelectorMenu::update(uint32_t currentTime)
{
    // No option, no talk
    if (_data.option_list.size() == 0) {
        return;
    }

    // Callback
    onUpdate(currentTime);

    // Read input callback
    if (currentTime - _data.read_input_time_count > _config.readInputInterval) {
        onReadInput();
        _data.read_input_time_count = currentTime;
    }

    // Update
    if (_data.is_changed) {
        _data.is_changed = false;
        _update_selector_keyframe();
        _update_camera_keyframe();
    }
    float current_time_s = currentTime / 1000.0f;
    _data.selector_postion.update(current_time_s);
    _data.selector_shape.update(current_time_s);
    _data.camera_offset.update(current_time_s);

    // Render callback
    if (currentTime - _data.render_time_count > _config.renderInterval) {
        onRender();
        _data.render_time_count = currentTime;
    }

    // On click callback
    if (_data.was_released) {
        // Check if transition is done
        if (_data.selector_postion.done() && _data.selector_shape.done()) {
            _data.was_released = false;
            _data.is_pressing = false;
            onClick();
        }
    }

    // On open end callback
    if (_data.was_opened) {
        // Check if transition is done
        if (_data.selector_postion.done() && _data.selector_shape.done()) {
            _data.was_opened = false;
            onOpenEnd();
        }
    }
}

void SmoothSelectorMenu::_update_selector_keyframe()
{
    if (_data.option_list.size() == 0) {
        return;
    }

    _data.selector_postion.move(_data.option_list[_data.selected_option_index].keyframe.x,
                                _data.option_list[_data.selected_option_index].keyframe.y);
    _data.selector_shape.move(_data.option_list[_data.selected_option_index].keyframe.width,
                              _data.option_list[_data.selected_option_index].keyframe.height);
}

void SmoothSelectorMenu::_update_camera_keyframe()
{
    if (_config.cameraSize.width == 0 && _config.cameraSize.height == 0) {
        return;
    }

    // Check if selector's target frame is inside of camera
    int new_x_offset = getCameraOffset().x;
    int new_y_offset = getCameraOffset().y;
    Vector4 selector_keyframe = getSelectedKeyframe();
    Vector4i selector_keyframe_i(
        selector_keyframe.x, selector_keyframe.y, selector_keyframe.width, selector_keyframe.height);

    // Left
    if (selector_keyframe_i.x < new_x_offset) {
        new_x_offset = selector_keyframe_i.x;
    }

    // Right
    else if (selector_keyframe_i.x + selector_keyframe_i.width > new_x_offset + _config.cameraSize.width) {
        new_x_offset = selector_keyframe_i.x + selector_keyframe_i.width - _config.cameraSize.width;
    }

    // Top
    if (selector_keyframe_i.y < new_y_offset) {
        new_y_offset = selector_keyframe_i.y;
    }

    // Bottom
    else if (selector_keyframe_i.y + selector_keyframe_i.height > new_y_offset + _config.cameraSize.height) {
        new_y_offset = selector_keyframe_i.y + selector_keyframe_i.height - _config.cameraSize.height;
    }

    _data.camera_offset.move(new_x_offset, new_y_offset);
}
