/**
 * @file smooth_options.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-10-30
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "smooth_options.h"
#include "utils/math/vector.h"

using namespace smooth_ui_toolkit;

void SmoothOptionsMenu::addOption(void* userData)
{
    _data.option_list.emplace_back();
    _data.option_list.back().userData = userData;
    _data.keyframe_list.emplace_back();
}

void SmoothOptionsMenu::goLast()
{
    if (_data.option_list.size() == 0) {
        return;
    }

    // Update selected index
    _data.selected_option_index--;
    if (_data.selected_option_index < 0) {
        _data.selected_option_index = _data.option_list.size() - 1;
    }

    // Set update flag
    _data.is_changed = true;

    // Callback
    onGoLast();
}

void SmoothOptionsMenu::goNext()
{
    if (_data.option_list.size() == 0) {
        return;
    }

    // Update selected index
    _data.selected_option_index++;
    if (_data.selected_option_index >= _data.option_list.size()) {
        _data.selected_option_index = 0;
    }

    // Set update flag
    _data.is_changed = true;

    // Callback
    onGoNext();
}

void SmoothOptionsMenu::moveTo(int optionIndex)
{
    if (optionIndex < 0 || optionIndex > (_data.option_list.size() - 1)) {
        return;
    }

    // Update transition target
    _data.selected_option_index = optionIndex;
    _data.is_changed = true;
}

void SmoothOptionsMenu::jumpTo(int optionIndex)
{
    if (optionIndex < 0 || optionIndex > (_data.option_list.size() - 1)) {
        return;
    }

    // Update transition target
    _data.selected_option_index = optionIndex;
    _update_option_keyframe(true);
}

void SmoothOptionsMenu::press(const Vector4& pressedKeyframe)
{
    _data.is_pressing = true;

    // Update transition target
    int selected_index = getMatchingOptionIndex(0);
    _data.option_list[selected_index].position.move(pressedKeyframe.x, pressedKeyframe.y);
    _data.option_list[selected_index].shape.move(pressedKeyframe.width, pressedKeyframe.height);

    // Callback
    onPress();
}

void SmoothOptionsMenu::release()
{
    // Set update flag, let _update_option_keyframe to change it back
    _data.is_changed = true;
    _data.was_released = true;

    // Callback
    onRelease();
}

void SmoothOptionsMenu::open(const Vector4& pressedKeyframe)
{
    // Update transition target
    int selected_index = getMatchingOptionIndex(0);
    _data.option_list[selected_index].position.move(pressedKeyframe.x, pressedKeyframe.y);
    _data.option_list[selected_index].shape.move(pressedKeyframe.width, pressedKeyframe.height);

    _data.is_opening = true;
    _data.was_opened = true;
}

void SmoothOptionsMenu::close()
{
    _data.is_changed = true;
    _data.is_opening = false;
}

void SmoothOptionsMenu::update(const uint32_t& currentTime)
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
        _update_option_keyframe();
    }
    _invoke_option_update(currentTime);

    // Render callback
    if (currentTime - _data.render_time_count > _config.renderInterval) {
        onRender();
        _data.render_time_count = currentTime;
    }

    // On click callback
    if (_data.was_released) {
        // Check if transition is done
        int matching_index = getMatchingOptionIndex(0);
        if (getOption(matching_index).position.done() && getOption(matching_index).shape.done()) {
            _data.was_released = false;
            _data.is_pressing = false;
            onClick();
        }
    }

    // On open end callback
    if (_data.was_opened) {
        // Check if transition is done
        int matching_index = getMatchingOptionIndex(0);
        if (getOption(matching_index).position.done() && getOption(matching_index).shape.done()) {
            _data.was_opened = false;
            onOpenEnd();
        }
    }
}

int SmoothOptionsMenu::getMatchingOptionIndex(const int& keyframeIndex)
{
    int matched_option_index = keyframeIndex + _data.selected_option_index;
    // If out of limit, connect to back
    if (matched_option_index >= _data.keyframe_list.size()) {
        matched_option_index = matched_option_index - _data.keyframe_list.size();
    }

    return matched_option_index;
}

void SmoothOptionsMenu::_update_option_keyframe(bool isJump)
{
    int matching_index = 0;
    for (int i = 0; i < _data.keyframe_list.size(); i++) {
        matching_index = getMatchingOptionIndex(i);

        // Update transition target
        if (isJump) {
            _data.option_list[matching_index].position.teleport(_data.keyframe_list[i].x, _data.keyframe_list[i].y);
            _data.option_list[matching_index].shape.teleport(_data.keyframe_list[i].width,
                                                             _data.keyframe_list[i].height);
        } else {
            _data.option_list[matching_index].position.move(_data.keyframe_list[i].x, _data.keyframe_list[i].y);
            _data.option_list[matching_index].shape.move(_data.keyframe_list[i].width, _data.keyframe_list[i].height);
        }
    }
}

void SmoothOptionsMenu::_invoke_option_update(const uint32_t& currentTime)
{
    // Invoke transition update
    float current_time_s = currentTime / 1000.0f;
    for (auto& i : _data.option_list) {
        i.position.update(current_time_s);
        i.shape.update(current_time_s);
    }
}
