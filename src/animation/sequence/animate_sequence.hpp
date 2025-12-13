/**
 * @file animate_sequence.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-04-04
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "../animate_value/animate_value.hpp"
#include <memory>
#include <vector>
#include <functional>

namespace smooth_ui_toolkit {

class AnimateSequence {
public:
    AnimateSequence() {}
    AnimateSequence(const std::initializer_list<float>& valueSequence)
    {
        setSequence(valueSequence);
    }
    template <typename T>
    AnimateSequence(const std::vector<T>& valueSequence)
    {
        setSequence(valueSequence);
    }
    ~AnimateSequence() {}

    // Override assignment operator
    AnimateSequence& operator=(const std::initializer_list<float>& valueSequence)
    {
        setSequence(valueSequence);
        return *this;
    }
    template <typename T>
    AnimateSequence& operator=(const std::vector<T>& valueSequence)
    {
        setSequence(valueSequence);
        return *this;
    }

    // Override type conversion
    operator float();

    // no copy constructor and copy assignment operator
    AnimateSequence(const AnimateSequence&) = delete;
    AnimateSequence& operator=(const AnimateSequence&) = delete;

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
    AnimateRepeatType repeatType = AnimateRepeatType::Loop;
    std::vector<float>& sequence()
    {
        return _value_sequence;
    }
    void onPlay(std::function<void(AnimateValue& animateValue)> onPlay)
    {
        _on_play = onPlay;
    }
    void onStep(std::function<void(AnimateValue& animateValue, std::vector<float>& sequence, int step)> onStep)
    {
        _on_step = onStep;
    }
    void onDone(std::function<void(void)> onDone)
    {
        _on_done = onDone;
    }

    void play();
    void pause();
    void complete();
    void cancel();
    void update();
    float value();
    float directValue()
    {
        return _current_value;
    }
    bool done()
    {
        return _is_done;
    }

private:
    float _current_value = 0.0f;
    int _current_index = 0;
    int _repeat_count = 0;
    bool _is_done = true;

    std::vector<float> _value_sequence;
    std::unique_ptr<AnimateValue> _animate_value;

    std::function<void(AnimateValue& animateValue)> _on_play;
    std::function<void(AnimateValue& animateValue, std::vector<float>& sequence, int step)> _on_step;
    std::function<void(void)> _on_done;
};

} // namespace smooth_ui_toolkit
