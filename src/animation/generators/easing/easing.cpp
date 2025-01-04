/**
 * @file easing.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-03-29
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "easing.h"

using namespace smooth_ui_toolkit;

void Easing::init()
{
    done = false;
    value = start;
}

void Easing::retarget(const float& start, const float& end)
{
    this->start = start;
    this->end = end;
    done = false;
}

bool Easing::next(const float& t)
{
    if (done) {
        return done;
    }

    float progress = t / easingOptions.duration;
    if (progress >= 1.0f) {
        value = end;
        done = true;
    } else {
        value = start + (end - start) * easingOptions.easingFunction(progress);
    }

    return done;
}
