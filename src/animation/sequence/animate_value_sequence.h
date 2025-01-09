/**
 * @file animate_value_sequence.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-09
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "../animate_value/animate_value.h"
#include <memory>
#include <vector>

namespace smooth_ui_toolkit {

class AnimateValueSequence {
public:
    AnimateValueSequence();
    ~AnimateValueSequence() {}

    // Override assignment operator
    AnimateValueSequence& operator=(const std::vector<float>& valueSequence);

    // Override type conversion
    operator float();

    void play();
    void pause();
    void update();

    void setSequence(const std::vector<float>& valueSequence);

    float value();

private:
    float _current_value = 0.0f;
    int _current_index = 0;

    std::vector<float> _value_sequence;
    std::shared_ptr<AnimateValue> _animate_value;
};

} // namespace smooth_ui_toolkit
