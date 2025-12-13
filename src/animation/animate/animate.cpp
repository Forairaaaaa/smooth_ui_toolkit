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
#include "animate.hpp"
#include "utils/hal/hal.hpp"
#include <functional>
#include <memory>

using namespace smooth_ui_toolkit;

EasingOptions_t& Animate::easingOptions()
{
    if (animationType != animation_type::easing) {
        animationType = animation_type::easing;
        _generator_dirty = true;
    }
    return static_cast<Easing&>(get_key_frame_generator()).easingOptions;
}

SpringOptions_t& Animate::springOptions()
{
    if (animationType != animation_type::spring) {
        animationType = animation_type::spring;
        _generator_dirty = true;
    }
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
    if (_playing_state == animate_state::playing) {
        return;
    }

    // If paused, add pause time to start time, resume animation
    if (_playing_state == animate_state::paused) {
        _start_time += ui_hal::get_tick_s() - _pause_time;
    }
    // If not, reset repeat count and start time, start animation
    else {
        _repeat_count = repeat;
        _start_time = ui_hal::get_tick_s();
    }

    _playing_state = delay > 0 ? animate_state::delaying : animate_state::playing;
    get_key_frame_generator().done = false;
}

void Animate::pause()
{
    if (_playing_state == animate_state::playing || _playing_state == animate_state::delaying) {
        _playing_state = animate_state::paused;
        _pause_time = ui_hal::get_tick_s();
    }
}

void Animate::complete()
{
    if (_playing_state == animate_state::completed) {
        return;
    }
    _playing_state = animate_state::completed;
    get_key_frame_generator().done = false;
    get_key_frame_generator().value = end;
}

void Animate::cancel()
{
    if (_playing_state == animate_state::cancelled) {
        return;
    }
    _playing_state = animate_state::cancelled;
    get_key_frame_generator().done = false;
    get_key_frame_generator().value = start;
}

void Animate::retarget(const float& start, const float& end)
{
    get_key_frame_generator().retarget(start, end);
    if (_playing_state != animate_state::paused) {
        _playing_state = animate_state::idle;
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
    update_state_machine(currentTime);
}

void Animate::update_state_machine(const float& currentTime)
{
    // Handle delay state
    if (_playing_state == animate_state::delaying) {
        // Invoke callback with current value
        if (_on_update) {
            _on_update(value());
        }
        // Check delay timeout
        if (currentTime - _start_time >= delay) {
            _playing_state = animate_state::playing;
            _start_time = currentTime;
        }
        return;
    }

    // Handle playing state
    if (_playing_state == animate_state::playing) {
        if (done()) {
            return;
        }

        // Update key frame
        get_key_frame_generator().next(currentTime - _start_time);
        if (_on_update) {
            _on_update(value());
        }

        // Check if animation is done
        if (done()) {
            _playing_state = animate_state::completed;
            if (_on_complete) {
                _on_complete();
            }

            // Handle repeat
            if (_repeat_count != 0) {
                // Decrement repeat count
                if (_repeat_count > 0) {
                    _repeat_count--;
                }

                // Check if we need repeat delay
                if (repeatDelay > 0) {
                    _playing_state = animate_state::repeat_delaying;
                    _start_time = currentTime;
                } else {
                    // Reset animation immediately
                    if (repeatType == AnimateRepeatType::Reverse) {
                        std::swap(start, end);
                    }
                    init();
                    _playing_state = delay > 0 ? animate_state::delaying : animate_state::playing;
                    _start_time = currentTime;
                }
            }
        }
        return;
    }

    // Handle repeat delay state
    if (_playing_state == animate_state::repeat_delaying) {
        // Check repeat delay timeout
        if (currentTime - _start_time >= repeatDelay) {
            // Reset animation
            if (repeatType == AnimateRepeatType::Reverse) {
                std::swap(start, end);
            }
            init();
            _playing_state = delay > 0 ? animate_state::delaying : animate_state::playing;
            _start_time = currentTime;
        }
        return;
    }

    // Handle completed/cancelled states
    if (_playing_state == animate_state::completed || _playing_state == animate_state::cancelled) {
        get_key_frame_generator().done = true;
        if (_on_update) {
            _on_update(value());
        }
        return;
    }
}

// Lazy loading, default spring
KeyFrameGenerator& Animate::get_key_frame_generator()
{
    if (_generator_dirty || !_key_frame_generator) {
        _key_frame_generator.reset();
        if (animationType == animation_type::spring) {
            _key_frame_generator = std::make_unique<Spring>();
        } else if (animationType == animation_type::easing) {
            _key_frame_generator = std::make_unique<Easing>();
        }
        _generator_dirty = false;
    }
    return *_key_frame_generator;
}

Animate::Animate(Animate&& other) noexcept
    : start(other.start),
      end(other.end),
      delay(other.delay),
      repeat(other.repeat),
      repeatType(other.repeatType),
      repeatDelay(other.repeatDelay),
      animationType(other.animationType),
      _on_update(std::move(other._on_update)),
      _on_complete(std::move(other._on_complete)),
      _key_frame_generator(std::move(other._key_frame_generator)),
      _playing_state(other._playing_state),
      _start_time(other._start_time),
      _pause_time(other._pause_time),
      _repeat_count(other._repeat_count),
      _generator_dirty(other._generator_dirty)
{
    // Reset other object to default state
    other._playing_state = animate_state::idle;
    other._generator_dirty = true;
}

Animate& Animate::operator=(Animate&& other) noexcept
{
    if (this != &other) {
        start = other.start;
        end = other.end;
        delay = other.delay;
        repeat = other.repeat;
        repeatType = other.repeatType;
        repeatDelay = other.repeatDelay;
        animationType = other.animationType;
        _on_update = std::move(other._on_update);
        _on_complete = std::move(other._on_complete);
        _key_frame_generator = std::move(other._key_frame_generator);
        _playing_state = other._playing_state;
        _start_time = other._start_time;
        _pause_time = other._pause_time;
        _repeat_count = other._repeat_count;
        _generator_dirty = other._generator_dirty;

        // Reset other object to default state
        other._playing_state = animate_state::idle;
        other._generator_dirty = true;
    }
    return *this;
}
