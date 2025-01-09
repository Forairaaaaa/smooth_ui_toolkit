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
#include "../animate/animate.h"
#include "../animate_value/animate_value.h"
#include <memory>
#include <vector>

namespace smooth_ui_toolkit {

class AnimateValueSequence {
public:
    AnimateValueSequence() {}

    AnimateValueSequence(const std::initializer_list<float>& valueSequence)
    {
        setSequence(valueSequence);
    }

    template <typename T>
    AnimateValueSequence(const std::vector<T>& valueSequence)
    {
        setSequence(valueSequence);
    }

    ~AnimateValueSequence() {}

    // Override assignment operator
    AnimateValueSequence& operator=(const std::initializer_list<float>& valueSequence)
    {
        setSequence(valueSequence);
        return *this;
    }

    template <typename T>
    AnimateValueSequence& operator=(const std::vector<T>& valueSequence)
    {
        setSequence(valueSequence);
        return *this;
    }

    // Override type conversion
    operator float();

    void setSequence(const std::initializer_list<float>& valueSequence)
    {
        _value_sequence.reserve(valueSequence.size());
        for (const auto& v : valueSequence) {
            _value_sequence.push_back(v);
        }
    }

    template <typename T>
    void setSequence(const std::vector<T>& valueSequence)
    {
        _value_sequence.reserve(valueSequence.size());
        for (const auto& v : valueSequence) {
            _value_sequence.push_back(static_cast<float>(v));
        }
    }

    int repeat = 0;
    animate_repeat_type::Type_t repeatType = animate_repeat_type::loop;

    void play();
    void pause();
    void complete();
    void cancel();
    void update();
    float value();

private:
    float _current_value = 0.0f;
    int _current_index = 0;
    int _repeat_count = 0;

    std::vector<float> _value_sequence;
    std::shared_ptr<AnimateValue> _animate_value;
};

} // namespace smooth_ui_toolkit
