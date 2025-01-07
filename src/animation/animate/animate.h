/**
 * @file animate.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "../generators/generators.h"
#include "../generators/spring/spring.h"
#include <functional>
#include <memory>

namespace smooth_ui_toolkit {

namespace animate_repeat_type {
enum Type_t {
    loop = 0, // Repeats the animation from the start
    reverse,  // Alternates between forward and backwards playback
    mirror,   // Switches animation origin and target on each iteration
};
}

namespace animate_state {
enum State_t {
    idle = 0,
    playing,
    paused,
    completed,
    cancelled,
};
}

namespace animate_playing_state {
enum State_t {
    delay = 0,
    playing,
    repeat_delay,
};
}

class Animate {
public:
    Animate() {}
    ~Animate() {}

    // Start value
    float start = 0.0f;
    // End value
    float end = 0.0f;
    // Delay the animation by this duration (in seconds)
    float delay = 0.0f;
    // The number of times to repeat the transition. Set to -1 for perpetual animation
    int repeat = 0;
    // How to repeat the animation
    animate_repeat_type::Type_t repeatType = animate_repeat_type::loop;
    // When repeating an animation, repeatDelay will set the duration of the time to wait, in seconds, between each
    // repetition
    float repeatDelay = 0.0f;
    // Spring animation options
    SpringOptions_t& springOptions();
    // On value update
    void onUpdate(std::function<void(const float&)> callback)
    {
        _on_update = callback;
    }
    // On animation complete
    void onComplete(std::function<void()> callback)
    {
        _on_complete = callback;
    }

    void init();

    void play();
    void pause();
    void complete();
    void cancel();

    void update();

    /**
     * @brief Is key frame generator done
     *
     * @return true
     * @return false
     */
    inline bool done()
    {
        return get_key_frame_generator().done;
    }

    /**
     * @brief Get key frame generator current value
     *
     * @return float
     */
    inline float value()
    {
        return get_key_frame_generator().value;
    }

private:
    std::function<void(const float&)> _on_update;
    std::function<void()> _on_complete;
    std::unique_ptr<KeyFrameGenerator> _key_frame_generator;
    KeyFrameGenerator& get_key_frame_generator();
    animate_state::State_t _state = animate_state::idle;
    animate_playing_state::State_t _playing_state = animate_playing_state::playing;
    float _start_time = 0.0f;
};

} // namespace smooth_ui_toolkit
