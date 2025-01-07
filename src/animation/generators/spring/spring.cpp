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

void Spring::setSpringOptions(float duration, float bounce, float visualDuration)
{
    // 默认质量
    springOptions.mass = 1.0f;

    // Clamp 函数，确保 bounce 在合理范围内
    auto clamp = [](float value, float min, float max) { return std::max(min, std::min(value, max)); };

    // 确保 bounce 在 0.05 到 1 之间
    bounce = clamp(bounce, 0.05f, 1.0f);

    // 根据 visualDuration 计算 stiffness 和 damping
    if (visualDuration > 0) {
        float root = (2 * M_PI) / (visualDuration * 1.2f); // 可视化周期
        springOptions.stiffness = root * root;             // 刚度
        springOptions.damping =
            2 * (1.0f - bounce) * std::sqrt(springOptions.stiffness * springOptions.mass); // 阻尼系数
    } else {
        // 如果未提供 visualDuration，使用默认的 duration 和 bounce 来推导
        springOptions.stiffness = (36 / (duration / 1000.0f) / (duration / 1000.0f)); // 刚度
        springOptions.damping =
            2 * (1.0f - bounce) * std::sqrt(springOptions.stiffness * springOptions.mass); // 阻尼系数
    }
}

void Spring::init()
{
    // If or duration or visualDuration is provided, set spring options by duration/bounce-based options
    if (springOptions.duration > 0 || springOptions.visualDuration > 0) {
        setSpringOptions(springOptions.duration, springOptions.bounce, springOptions.visualDuration);
    }

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
    if (_resolve_spring) {
        _animation_state.value = _resolve_spring(t);
    } else {
        init();
    }

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
