/**
 * @file smooth_options.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-06
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "smooth_options.h"

using namespace SmoothUIToolKit::SelectMenu;

void SmoothOptions::setPositionDuration(TimeSize_t duration)
{
    for (auto& i : _data.option_list)
        i.position.setDuration(duration);
}

void SmoothOptions::setShapeDuration(TimeSize_t duration)
{
    for (auto& i : _data.option_list)
        i.shape.setDuration(duration);
}

void SmoothOptions::setPositionTransitionPath(EasingPathPtr path)
{
    for (auto& i : _data.option_list)
        i.position.setTransitionPath(path);
}

void SmoothOptions::setShapeTransitionPath(EasingPathPtr path)
{
    for (auto& i : _data.option_list)
        i.shape.setTransitionPath(path);
}

void SmoothOptions::addOption(void* userData)
{
    _data.option_list.emplace_back();
    _data.option_list.back().userData = userData;
    _data.keyframe_list.emplace_back();
}

void SmoothOptions::goLast()
{
    // Update selected index
    _data.selected_option_index--;
    if (_data.selected_option_index < 0)
        _data.selected_option_index = _data.option_list.size() - 1;

    // Set update flag
    _data.is_changed = true;

    // Callback
    onGoLast();
}

void SmoothOptions::goNext()
{
    // Update selected index
    _data.selected_option_index++;
    if (_data.selected_option_index >= _data.option_list.size())
        _data.selected_option_index = 0;

    // Set update flag
    _data.is_changed = true;

    // Callback
    onGoNext();
}

void SmoothOptions::press(const Vector4D_t& pressedKeyframe)
{
    // Update tarnsition target
    _data.option_list[_data.selected_option_index].position.moveTo(pressedKeyframe.x, pressedKeyframe.y);
    _data.option_list[_data.selected_option_index].shape.reshapeTo(pressedKeyframe.w, pressedKeyframe.h);

    // Callback
    onPress();
}

void SmoothOptions::release()
{
    // Set update flag, let _update_option_keyframe to change it back
    _data.is_changed = true;
    _data.was_released = true;

    // Callback
    onRelease();
}

void SmoothOptions::open(const Vector4D_t& pressedKeyframe)
{
    // Update tarnsition target
    _data.option_list[_data.selected_option_index].position.moveTo(pressedKeyframe.x, pressedKeyframe.y);
    _data.option_list[_data.selected_option_index].shape.reshapeTo(pressedKeyframe.w, pressedKeyframe.h);

    _data.is_opening = true;
    _data.was_opened = true;
}

void SmoothOptions::close()
{
    _data.is_changed = true;
    _data.is_opening = false;
}

void SmoothOptions::update(const std::uint32_t& currentTime)
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
        _update_option_keyframe();
    }
    _invoke_option_update(currentTime);

    // Render callback
    if (currentTime - _data.render_time_count > _config.renderInterval)
    {
        onRender();
        _data.render_time_count = currentTime;
    }

    // On click callback
    if (_data.was_released)
    {
        int matching_index;
        getMatchingOptionIndex(0, matching_index);
        if (getOption(matching_index).position.isFinish() && getOption(matching_index).shape.isFinish())
        {
            _data.was_released = false;
            onClick();
        }
    }

    // On open end callback
    if (_data.was_opened)
    {
        int matching_index;
        getMatchingOptionIndex(0, matching_index);
        if (getOption(matching_index).position.isFinish() && getOption(matching_index).shape.isFinish())
        {
            _data.was_opened = false;
            onOpenEnd();
        }
    }
}

void SmoothOptions::getMatchingOptionIndex(const int& keyframeIndex, int& matchedOptionIndex)
{
    matchedOptionIndex = keyframeIndex + _data.selected_option_index;
    // If out of limit, connect to back
    if (matchedOptionIndex >= _data.keyframe_list.size())
        matchedOptionIndex = matchedOptionIndex - _data.keyframe_list.size();
}

void SmoothOptions::_update_option_keyframe()
{
    int matching_index = 0;
    for (int i = 0; i < _data.keyframe_list.size(); i++)
    {
        getMatchingOptionIndex(i, matching_index);

        // Update transition target
        _data.option_list[matching_index].position.moveTo(_data.keyframe_list[i].x, _data.keyframe_list[i].y);
        _data.option_list[matching_index].shape.reshapeTo(_data.keyframe_list[i].w, _data.keyframe_list[i].h);
    }
}

void SmoothOptions::_invoke_option_update(const std::uint32_t& currentTime)
{
    // Invoke transition update
    for (auto& i : _data.option_list)
    {
        i.position.update(currentTime);
        i.shape.update(currentTime);
    }
}
