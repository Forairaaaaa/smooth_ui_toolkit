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

AnimateValueSequence::AnimateValueSequence() {}

AnimateValueSequence& AnimateValueSequence::operator=(const std::vector<float>& valueSequence)
{
    _value_sequence = valueSequence;
    return *this;
}

AnimateValueSequence::operator float()
{
    return _current_value;
}

void AnimateValueSequence::begin()
{
    if (!_value_sequence.empty()) {
        _current_index = 0;
        _current_value = _value_sequence[_current_index];
        _animate_value = std::make_shared<AnimateValue>(_current_value);
    }
}

void AnimateValueSequence::stop() {}

void AnimateValueSequence::update()
{
    if (_animate_value) {
        if (_animate_value->done()) {
            int next_index = _current_index + 1;
            if (next_index < _value_sequence.size()) {
                _current_index = next_index;
                _animate_value->move(_value_sequence[_current_index]);
            }
        }
        _current_value = _animate_value->value();
    }
}