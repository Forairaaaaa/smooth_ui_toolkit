/**
 * @file animate_value_sequence.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-09
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "animate_value_sequence.h"
#include <memory>

using namespace smooth_ui_toolkit;

AnimateValueSequence::operator float()
{
    return value();
}

void AnimateValueSequence::play()
{
    if (_animate_value) {
        _animate_value->play();
        return;
    }
    // Reset index and create animate value
    if (!_value_sequence.empty()) {
        _current_index = 0;
        _current_value = _value_sequence[_current_index];
        _animate_value = std::make_shared<AnimateValue>(_current_value);
        _repeat_count = repeat;
    }
}

void AnimateValueSequence::pause()
{
    if (_animate_value) {
        _animate_value->pause();
    }
}

void AnimateValueSequence::complete()
{
    if (!_value_sequence.empty()) {
        _current_value = _value_sequence.back();
    }
    _animate_value.reset();
}

void AnimateValueSequence::cancel()
{
    if (!_value_sequence.empty()) {
        _current_value = _value_sequence[1];
    }
    _animate_value.reset();
}

void AnimateValueSequence::update()
{
    // If animate value instance exists
    if (_animate_value) {
        _current_value = _animate_value->value();
        // If animation is done, retarget to next value
        if (_animate_value->done()) {
            int next_index = _current_index + 1;
            if (next_index < _value_sequence.size()) {
                _current_index = next_index;
                _animate_value->move(_value_sequence[_current_index]);
            }
            // If reached the end of the sequence
            else {
                // If repeat is set, repeat the sequence
                if (_repeat_count > 0) {
                    _repeat_count--;
                    // Reset animation
                    if (repeatType == animate_repeat_type::reverse) {
                        std::reverse(_value_sequence.begin(), _value_sequence.end());
                    }
                    _current_index = 0;
                    _current_value = _value_sequence[_current_index];
                    _animate_value->teleport(_current_value);
                }
            }
        }
    }
}

float AnimateValueSequence::value()
{
    update();
    return _current_value;
}
