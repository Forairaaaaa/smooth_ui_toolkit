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

namespace animation_type {
enum Type_t {
    spring = 0,
    easing,
};
} // namespace animation_type

class KeyFrameGenerator {
public:
    KeyFrameGenerator() {}
    virtual ~KeyFrameGenerator() {}

    float start = 0.0f;
    float end = 0.0f;
    float value = 0.0f;
    bool done = false;

    virtual void init() {}

    virtual void retarget(const float& start, const float& end) {}

    virtual bool next(const float& t)
    {
        return done;
    }

    virtual animation_type::Type_t type() const = 0;
};

} // namespace smooth_ui_toolkit
