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
    if (_state == animate_state::playing) {
        return;
    }
    _state = animate_state::playing;
    get_key_frame_generator().done = false;
    _start_time = ui_hal::get_tick_s();
}

void Animate::pause()
{
    if (_state == animate_state::playing) {
        _state = animate_state::paused;
    }
}

void Animate::complete()
{
    if (_state == animate_state::completed) {
        return;
    }
    _state = animate_state::completed;
    get_key_frame_generator().done = false;
    get_key_frame_generator().value = end;
}

void Animate::cancel()
{
    if (_state == animate_state::cancelled) {
        return;
    }
    _state = animate_state::cancelled;
    get_key_frame_generator().done = false;
    get_key_frame_generator().value = start;
}

void Animate::update()
{
    if (done()) {
        return;
    }
    if (_state == animate_state::idle || _state == animate_state::paused) {
        return;
    }

    // If called complete or cancel method
    if (_state == animate_state::completed || _state == animate_state::cancelled) {
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

    // Update state
    if (_state == animate_state::playing && done()) {
        _state = animate_state::completed;
        if (_on_complete) {
            _on_complete();
        }
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
