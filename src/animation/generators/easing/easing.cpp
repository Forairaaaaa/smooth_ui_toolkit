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
    _range = end - start;                          // 预计算差值
    _inv_duration = 1.0f / easingOptions.duration; // 预计算持续时间倒数
}

void Easing::retarget(const float& start, const float& end)
{
    this->start = start;
    this->end = end;
    _range = end - start; // 重新计算差值
    done = false;
}

bool Easing::next(const float& t)
{
    if (done) {
        return done;
    }

    float progress = t * _inv_duration;
    if (progress >= 1.0f) {
        value = end;
        done = true;
        return done; // 早期退出，避免后续计算
    }

    value = start + _range * easingOptions.easingFunction(progress);
    return done;
}
