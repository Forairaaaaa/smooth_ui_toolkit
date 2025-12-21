/**
 * @file generators.hpp
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

enum class AnimationType {
    Spring = 0,
    Easing,
};

class KeyFrameGenerator {
public:
    KeyFrameGenerator() {}
    virtual ~KeyFrameGenerator() {}

    float start = 0.0f;
    float end = 0.0f;
    float value = 0.0f;
    bool done = false;

    virtual void init() {}

    virtual void retarget(float start, float end) {}

    virtual bool next(float t)
    {
        return done;
    }

    virtual AnimationType type() const = 0;
};

} // namespace smooth_ui_toolkit
