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

void AnimateValue::begin()
{
    start = _default_value;
    end = _default_value;
    get_key_frame_generator().value = _default_value;
    init();
    play();
}

AnimateValue& AnimateValue::operator=(float newValue)
{
    // If not begin yet, set to default value
    if (_playing_state == animate_playing_state::idle) {
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
    if (_playing_state == animate_playing_state::idle) {
        return _default_value;
    }
    update();
    return value();
}
