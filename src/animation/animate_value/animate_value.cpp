/**
 * @file animate_value.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-08
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "animate_value.h"

using namespace smooth_ui_toolkit;

AnimateValue::AnimateValue()
{
    begin();
}

AnimateValue::AnimateValue(float defaultValue) : _default_value(defaultValue)
{
    begin();
}

AnimateValue& AnimateValue::operator=(float newValue)
{
    // If not begin yet, set to default value
    if (!_is_begin) {
        _default_value = newValue;
        return *this;
    }
    // If same value, do nothing
    if (newValue == get_key_frame_generator().end) {
        return *this;
    }
    // Else, retarget to new value
    retarget(value(), newValue);
    return *this;
}

AnimateValue::operator float()
{
    if (!_is_begin) {
        return _default_value;
    }
    update();
    return value();
}

void AnimateValue::begin()
{
    if (_is_begin) {
        return;
    }
    _is_begin = true;
    start = _default_value;
    end = _default_value;
    get_key_frame_generator().value = _default_value;
    init();
    play();
}

void AnimateValue::stop()
{
    if (!_is_begin) {
        return;
    }
    _is_begin = false;
    _default_value = value();
}

void AnimateValue::teleport(float newValue)
{
    bool is_begin = _is_begin;
    stop();
    _default_value = newValue;
    if (is_begin) {
        begin();
    }
}
