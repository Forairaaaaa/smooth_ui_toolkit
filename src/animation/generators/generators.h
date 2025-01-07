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

class KeyFrameGenerator {
public:
    KeyFrameGenerator() {}
    virtual ~KeyFrameGenerator() {}

    float start = 0.0f;
    float end = 0.0f;
    float value = 0.0f;
    bool done = false;

    virtual void init() {}

    virtual bool next(const float& t)
    {
        return done;
    }
};

} // namespace smooth_ui_toolkit
