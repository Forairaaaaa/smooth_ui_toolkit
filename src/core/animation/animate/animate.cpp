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
#include "core/hal/hal.hpp"
#include <functional>
#include <memory>

using namespace smooth_ui_toolkit;

EasingOptions_t& Animate::easingOptions()
{
    if (animationType != AnimationType::Easing) {
        animationType = AnimationType::Easing;
        _generator_dirty = true;
    }
    return static_cast<Easing&>(get_key_frame_generator()).easingOptions;
}

SpringOptions_t& Animate::springOptions()
{
    if (animationType != AnimationType::Spring) {
        animationType = AnimationType::Spring;
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
    if (_playing_state == AnimateState::Playing) {
        return;
    }

    // If paused, resume
    if (_playing_state == AnimateState::Paused) {
        _playing_state = _saved_state;
        _last_tick = ui_hal::get_tick_s();
    }
    // If not, reset repeat count and start time, start animation
    else {
        _repeat_count = repeat;
        _current_duration = 0.0f;
        _playing_state = delay > 0 ? AnimateState::Delaying : AnimateState::Playing;
        get_key_frame_generator().done = false;
        _last_tick = ui_hal::get_tick_s();
    }
}

void Animate::pause()
{
    if (_playing_state == AnimateState::Playing || _playing_state == AnimateState::Delaying ||
        _playing_state == AnimateState::RepeatDelaying) {
        _saved_state = _playing_state;
        _playing_state = AnimateState::Paused;
    }
}

void Animate::complete()
{
    if (_playing_state == AnimateState::Completed) {
        return;
    }
    _playing_state = AnimateState::Completed;
    get_key_frame_generator().done = false;
    get_key_frame_generator().value = end;
}

void Animate::cancel()
{
    if (_playing_state == AnimateState::Cancelled) {
        return;
    }
    _playing_state = AnimateState::Cancelled;
    get_key_frame_generator().done = false;
    get_key_frame_generator().value = start;
}

void Animate::retarget(float start, float end)
{
    this->start = start;
    this->end = end;
    get_key_frame_generator().retarget(start, end);
    if (_playing_state != AnimateState::Paused) {
        _playing_state = AnimateState::Idle;
        play();
    }
}

void Animate::update()
{
    const float currentTime = ui_hal::get_tick_s();
    update(currentTime);
}

void Animate::update(float currentTime)
{
    float dt = currentTime - _last_tick;
    _last_tick = currentTime;
    if (dt < 0) {
        dt = 0;
    }
    update_state_machine(dt);
}

void Animate::updateWithDelta(float dt)
{
    update_state_machine(dt);
}

void Animate::update_state_machine(float dt)
{
    if (_playing_state == AnimateState::Completed || _playing_state == AnimateState::Cancelled) {
        get_key_frame_generator().done = true;
        if (_on_update) {
            _on_update(value());
        }
        return;
    }

    if (_playing_state == AnimateState::Idle || _playing_state == AnimateState::Paused) {
        return;
    }

    _current_duration += dt;

    // Handle delay state
    if (_playing_state == AnimateState::Delaying) {
        // Invoke callback with current value
        if (_on_update) {
            _on_update(value());
        }
        // Check delay timeout
        if (_current_duration >= delay) {
            float overflow = _current_duration - delay;
            _playing_state = AnimateState::Playing;
            _current_duration = overflow;
        } else {
            return;
        }
    }

    // Handle playing state
    if (_playing_state == AnimateState::Playing) {
        if (done()) {
            return;
        }

        // Update key frame
        get_key_frame_generator().next(_current_duration);
        if (_on_update) {
            _on_update(value());
        }

        // Check if animation is done
        if (done()) {
            _playing_state = AnimateState::Completed;
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
                    _playing_state = AnimateState::RepeatDelaying;
                    _current_duration = 0;
                } else {
                    // Reset animation immediately
                    if (repeatType == AnimateRepeatType::Reverse) {
                        std::swap(start, end);
                    }
                    init();

                    if (delay > 0) {
                        _playing_state = AnimateState::Delaying;
                        _current_duration = 0;
                    } else {
                        _playing_state = AnimateState::Playing;
                        _current_duration = 0;
                    }
                }
            }
        }
        return;
    }

    // Handle repeat delay state
    if (_playing_state == AnimateState::RepeatDelaying) {
        // Check repeat delay timeout
        if (_current_duration >= repeatDelay) {
            float overflow = _current_duration - repeatDelay;
            // Reset animation
            if (repeatType == AnimateRepeatType::Reverse) {
                std::swap(start, end);
            }
            init();

            if (delay > 0) {
                _playing_state = AnimateState::Delaying;
                _current_duration = overflow;
            } else {
                _playing_state = AnimateState::Playing;
                _current_duration = overflow;
            }
        }
        return;
    }
}

// Lazy loading, default spring
KeyFrameGenerator& Animate::get_key_frame_generator()
{
    if (_generator_dirty || !_key_frame_generator) {
        _key_frame_generator.reset();
        if (animationType == AnimationType::Spring) {
            _key_frame_generator = std::make_unique<Spring>();
        } else if (animationType == AnimationType::Easing) {
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
      _last_tick(other._last_tick),
      _current_duration(other._current_duration),
      _repeat_count(other._repeat_count),
      _generator_dirty(other._generator_dirty),
      _saved_state(other._saved_state)
{
    // Reset other object to default state
    other._playing_state = AnimateState::Idle;
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
        _last_tick = other._last_tick;
        _current_duration = other._current_duration;
        _repeat_count = other._repeat_count;
        _generator_dirty = other._generator_dirty;
        _saved_state = other._saved_state;

        // Reset other object to default state
        other._playing_state = AnimateState::Idle;
        other._generator_dirty = true;
    }
    return *this;
}
