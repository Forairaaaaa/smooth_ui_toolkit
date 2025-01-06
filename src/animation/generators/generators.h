/**
 * @file generators.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-06
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

namespace smooth_ui_toolkit {

struct AnimationOptions_t {
    float start = 0.0f;
    float end = 0.0f;
};

struct AnimationState_t {
    float value = 0.0f;
    bool done = false;
};

class KeyFrameGenerator {
public:
    KeyFrameGenerator() {}
    virtual ~KeyFrameGenerator() {}

    AnimationOptions_t animationOptions;

    virtual void init() {}

    virtual const AnimationState_t& next(const float& t)
    {
        return _animation_state;
    }

    virtual const AnimationState_t& getState() const
    {
        return _animation_state;
    }

protected:
    AnimationState_t _animation_state;
};

} // namespace smooth_ui_toolkit
