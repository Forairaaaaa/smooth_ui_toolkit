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
    init();
    play();
}

AnimateValue& AnimateValue::operator=(int newValue)
{
    return operator=(static_cast<float>(newValue));
}

AnimateValue& AnimateValue::operator=(float newValue)
{
    if (_playing_state == animate_playing_state::idle) {
        start = newValue;
        end = newValue;
        get_key_frame_generator().value = newValue;
    } else {
        if (newValue == get_key_frame_generator().end) {
            return *this;
        }
        retarget(value(), newValue);
    }
    return *this;
}

AnimateValue& AnimateValue::operator=(double newValue)
{
    return operator=(static_cast<float>(newValue));
}

AnimateValue::operator int()
{
    return operator float();
}

AnimateValue::operator float()
{
    // Auto update
    if (_playing_state != animate_playing_state::idle) {
        update();
    }
    return value();
}

AnimateValue::operator double()
{
    return operator float();
}
