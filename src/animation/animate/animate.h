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
#include "../generators/easing/easing.h"
#include <functional>
#include <memory>

namespace smooth_ui_toolkit {

namespace animate_repeat_type {
enum Type_t {
    loop = 0, // Repeats the animation from the start
    reverse,  // Alternates between forward and backwards playback
};
}

namespace animate_playing_state {
enum State_t {
    idle = 0,
    playing,
    paused,
    completed,
    cancelled,
};
}

namespace animate_orchestration_state {
enum State_t {
    on_delay = 0,
    on_playing,
    on_repeat_delay,
};
}

class Animate {
public:
    Animate() {}
    virtual ~Animate() {}

    // Disable copy constructor and copy assignment operator
    Animate(const Animate&) = delete;
    Animate& operator=(const Animate&) = delete;

    // 参数参考：https://motion.dev/docs/animate#options

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
    // Animation type
    animation_type::Type_t animationType = animation_type::spring;
    // Easing animation options, call this method will set animation type to easing
    EasingOptions_t& easingOptions();
    // Spring animation options, call this method will set animation type to spring
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

    /**
     * @brief Init animation
     *
     */
    void init();

    /**
     * @brief Start playing animation, If an animation is paused, it will resume from its current time, If animation has
     * finished, it will restart
     *
     */
    void play();

    /**
     * @brief Pauses the animation until resumed with play()
     *
     */
    void pause();

    /**
     * @brief Immediately completes the animation, running it to the end state
     *
     */
    void complete();

    /**
     * @brief Cancels the animation, reverting it to the initial state
     *
     */
    void cancel();

    /**
     * @brief Reset start and end value dynamically, spring animation will animate to new value with current velocity
     *
     * @param start
     * @param end
     */
    void retarget(const float& start, const float& end);

    /**
     * @brief Update animation, keep calling this method to update animation, callbacks will be invoked in this method
     *
     */
    void update();

    /**
     * @brief Update animation with explicit current time, more efficient for batch updates
     *
     * @param currentTime Current time in seconds
     */
    void update(const float& currentTime);

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

    inline animate_playing_state::State_t currentPlayingState()
    {
        return _playing_state;
    }

protected:
    std::function<void(const float&)> _on_update;
    std::function<void()> _on_complete;
    std::unique_ptr<KeyFrameGenerator> _key_frame_generator;
    KeyFrameGenerator& get_key_frame_generator();
    animate_playing_state::State_t _playing_state = animate_playing_state::idle;
    animate_orchestration_state::State_t _orchestration_state = animate_orchestration_state::on_delay;
    float _start_time = 0.0f;
    float _pause_time = 0.0f;
    int _repeat_count = 0;
    bool _generator_dirty = true;

    void update_playing_state_fsm(const float& currentTime);
    void update_orchestration_state_fsm(const float& currentTime);
};

} // namespace smooth_ui_toolkit
