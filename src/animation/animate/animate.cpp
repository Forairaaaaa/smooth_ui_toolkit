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

using namespace smooth_ui_toolkit;

SpringOptions_t& Animate::springOptions()
{
    // If not spring, recreate a spring generator
    if (get_key_frame_generator().type() != KeyFrameGenerator::Type_t::Spring) {
        _key_frame_generator = std::make_unique<Spring>();
    }
    return static_cast<Spring*>(_key_frame_generator.get())->springOptions;
}

void Animate::init()
{
    get_key_frame_generator().start = start;
    get_key_frame_generator().end = end;
    get_key_frame_generator().init();
}

void Animate::play()
{
    if (_playing_state == animate_playing_state::playing) {
        return;
    }
    _playing_state = animate_playing_state::playing;
    get_key_frame_generator().done = false;
    _start_time = ui_hal::get_tick_s();
}

void Animate::pause()
{
    if (_playing_state == animate_playing_state::playing) {
        _playing_state = animate_playing_state::paused;
    }
}

void Animate::complete()
{
    if (_playing_state == animate_playing_state::completed) {
        return;
    }
    _playing_state = animate_playing_state::completed;
    get_key_frame_generator().done = false;
    get_key_frame_generator().value = end;
}

void Animate::cancel()
{
    if (_playing_state == animate_playing_state::cancelled) {
        return;
    }
    _playing_state = animate_playing_state::cancelled;
    get_key_frame_generator().done = false;
    get_key_frame_generator().value = start;
}

void Animate::update()
{
    update_orchestration_state_fsm();
}

void Animate::update_playing_state_fsm()
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
    get_key_frame_generator().next(ui_hal::get_tick_s() - _start_time);
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

void Animate::update_orchestration_state_fsm()
{
    if (_orchestration_state == animate_orchestration_state::delay) {
        if (_playing_state == animate_playing_state::playing) {
            // Invoke callback
            if (_on_update) {
                _on_update(value());
            }
            // Checkout delay timeout
            if (ui_hal::get_tick_s() - _start_time >= delay) {
                _orchestration_state = animate_orchestration_state::playing;
                _start_time = ui_hal::get_tick_s();
            }
        }
    }

    if (_orchestration_state == animate_orchestration_state::playing) {
        update_playing_state_fsm();
    }
}

// Lazy loading, default spring
KeyFrameGenerator& Animate::get_key_frame_generator()
{
    if (!_key_frame_generator) {
        _key_frame_generator = std::make_unique<Spring>();
    }
    return *_key_frame_generator;
}
