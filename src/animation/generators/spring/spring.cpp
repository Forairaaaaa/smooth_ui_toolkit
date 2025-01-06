/**
 * @file spring.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-06
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "spring.h"
#include <cmath>
#include <algorithm>

using namespace smooth_ui_toolkit;

void Spring::init()
{
    _undamped_angular_freq = std::sqrt(springOptions.stiffness / springOptions.mass);
    _damping_ratio = springOptions.damping / (2 * std::sqrt(springOptions.stiffness * springOptions.mass));

    float initialDelta = animationOptions.end - animationOptions.start;

    // 根据阻尼比选择不同的公式
    if (_damping_ratio < 1) {
        float angularFreq = calc_angular_freq(_undamped_angular_freq, _damping_ratio);

        // 欠阻尼
        // Underdamped spring
        _resolve_spring = [=](float t) {
            float envelope = std::exp(-_damping_ratio * _undamped_angular_freq * t);

            return (animationOptions.end -
                    envelope * (((springOptions.velocity + _damping_ratio * _undamped_angular_freq * initialDelta) /
                                 angularFreq) *
                                    std::sin(angularFreq * t) +
                                initialDelta * std::cos(angularFreq * t)));
        };
    } else if (_damping_ratio == 1) {
        // 临界阻尼
        // Critically damped spring
        _resolve_spring = [=](float t) {
            return animationOptions.end -
                   std::exp(-_undamped_angular_freq * t) *
                       (initialDelta + (springOptions.velocity + _undamped_angular_freq * initialDelta) * t);
        };
    } else {
        // 过阻尼
        // Overdamped spring
        float dampedAngularFreq = _undamped_angular_freq * std::sqrt(_damping_ratio * _damping_ratio - 1);
        _resolve_spring = [=](float t) {
            float envelope = std::exp(-_damping_ratio * _undamped_angular_freq * t);

            // When performing sinh or cosh values can hit Infinity so we cap them here
            float freqForT = std::min(dampedAngularFreq * t, 300.0f);

            return (animationOptions.end -
                    (envelope * ((springOptions.velocity + _damping_ratio * _undamped_angular_freq * initialDelta) *
                                     std::sinh(freqForT) +
                                 dampedAngularFreq * initialDelta * std::cosh(freqForT))) /
                        dampedAngularFreq);
        };
    }
}

const AnimationState_t& Spring::next(const float& t)
{
    if (_animation_state.done) {
        return _animation_state;
    }

    // 根据当前时间计算弹簧的值
    _animation_state.value = _resolve_spring(t);

    // 检查是否接近静止
    float currentVelocity = calc_velocity(t);
    bool isBelowVelocityThreshold = std::abs(currentVelocity) <= springOptions.restSpeed;
    bool isBelowDisplacementThreshold =
        std::abs(animationOptions.end - _animation_state.value) <= springOptions.restDelta;
    _animation_state.done = isBelowVelocityThreshold && isBelowDisplacementThreshold;

    return _animation_state;
}

float Spring::calc_velocity(const float& t)
{
    // 简单近似速度计算
    const float dt = 1e-5; // 微小时间增量
    return (_resolve_spring(t + dt) - _resolve_spring(t)) / dt;
}

float Spring::calc_angular_freq(float undampedFreq, float dampingRatio)
{
    return undampedFreq * std::sqrt(1 - dampingRatio * dampingRatio);
}
