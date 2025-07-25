/**
 * @file animate.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "animate.h"
#include "utils/hal/hal.h"
#include <functional>

using namespace smooth_ui_toolkit;

EasingOptions_t& Animate::easingOptions()
{
    animationType = animation_type::easing;
    return static_cast<Easing&>(get_key_frame_generator()).easingOptions;
}

SpringOptions_t& Animate::springOptions()
{
    animationType = animation_type::spring;
    return static_cast<Spring&>(get_key_frame_generator()).springOptions;
}

void Animate::init()
{
    // Setup key frame generator
    get_key_frame_generator().start = start;
    get_key_frame_generator().end = end;
    get_key_frame_generator().init();
}

void Animate::play()
{
    if (_playing_state == animate_playing_state::playing) {
        return;
    }

    // If paused, add pause time to start time, resume animation
    if (_playing_state == animate_playing_state::paused) {
        _start_time += ui_hal::get_tick_s() - _pause_time;
    }
    // If not, reset repeat count and start time, start animation
    else {
        _repeat_count = repeat;
        _start_time = ui_hal::get_tick_s();
    }

    _playing_state = animate_playing_state::playing;
    get_key_frame_generator().done = false;
}

void Animate::pause()
{
    if (_playing_state == animate_playing_state::playing) {
        _playing_state = animate_playing_state::paused;
        _orchestration_state = animate_orchestration_state::on_delay;
        _pause_time = ui_hal::get_tick_s();
    }
}

void Animate::complete()
{
    if (_playing_state == animate_playing_state::completed) {
        return;
    }
    _playing_state = animate_playing_state::completed;
    _orchestration_state = animate_orchestration_state::on_delay;
    get_key_frame_generator().done = false;
    get_key_frame_generator().value = end;
}

void Animate::cancel()
{
    if (_playing_state == animate_playing_state::cancelled) {
        return;
    }
    _playing_state = animate_playing_state::cancelled;
    _orchestration_state = animate_orchestration_state::on_delay;
    get_key_frame_generator().done = false;
    get_key_frame_generator().value = start;
}

void Animate::retarget(const float& start, const float& end)
{
    get_key_frame_generator().retarget(start, end);
    if (_playing_state != animate_playing_state::paused) {
        _playing_state = animate_playing_state::idle;
        play();
    }
}

void Animate::update()
{
    const float currentTime = ui_hal::get_tick_s();
    update(currentTime);
}

void Animate::update(const float& currentTime)
{
    update_orchestration_state_fsm(currentTime);
}

void Animate::update_playing_state_fsm(const float& currentTime)
{
    if (done()) {
        return;
    }
    if (_playing_state == animate_playing_state::idle || _playing_state == animate_playing_state::paused) {
        return;
    }

    // If called complete or cancel method
    if (_playing_state == animate_playing_state::completed || _playing_state == animate_playing_state::cancelled) {
        get_key_frame_generator().done = true;
        if (_on_update) {
            _on_update(value());
        }
        return;
    }

    // Update key frame
    get_key_frame_generator().next(currentTime - _start_time);
    if (_on_update) {
        _on_update(value());
    }

    // Update playing state
    if (_playing_state == animate_playing_state::playing && done()) {
        _playing_state = animate_playing_state::completed;
        if (_on_complete) {
            _on_complete();
        }
    }
}

void Animate::update_orchestration_state_fsm(const float& currentTime)
{
    // Handle on delay
    if (_orchestration_state == animate_orchestration_state::on_delay) {
        if (_playing_state != animate_playing_state::idle && _playing_state != animate_playing_state::paused) {
            // Invoke callback
            if (_on_update) {
                _on_update(value());
            }
            // Check delay timeout
            if (currentTime - _start_time >= delay) {
                _orchestration_state = animate_orchestration_state::on_playing;
                _start_time = currentTime;
            }
        }
    }

    // Handle on playing
    else if (_orchestration_state == animate_orchestration_state::on_playing) {
        update_playing_state_fsm(currentTime);
        if (done() && _repeat_count != 0) {
            // Decrement repeat count
            if (_repeat_count > 0) {
                _repeat_count--;
            }
            _orchestration_state = animate_orchestration_state::on_repeat_delay;
            _start_time = currentTime;
        }
    }

    // Handle on repeat delay
    else {
        // Check repeat delay timeout
        if (currentTime - _start_time >= repeatDelay) {
            // Reset animation
            if (repeatType == animate_repeat_type::reverse) {
                std::swap(start, end);
            }
            init();
            _playing_state = animate_playing_state::playing;
            _orchestration_state = animate_orchestration_state::on_delay;
            _start_time = currentTime;
        }
    }
}

// Lazy loading, default spring
KeyFrameGenerator& Animate::get_key_frame_generator()
{
    if (_key_frame_generator) {
        if (_key_frame_generator->type() != animationType) {
            _key_frame_generator.reset();
        }
    }
    if (!_key_frame_generator) {
        if (animationType == animation_type::spring) {
            _key_frame_generator = std::make_shared<Spring>();
        } else if (animationType == animation_type::easing) {
            _key_frame_generator = std::make_shared<Easing>();
        }
    }
    return *_key_frame_generator;
}
