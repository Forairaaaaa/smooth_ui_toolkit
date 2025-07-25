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

    // 确保 bounce 在 0.05 到 1 之间
    bounce = std::clamp(bounce, 0.05f, 1.0f);

    // 根据 visualDuration 计算 stiffness 和 damping
    if (visualDuration > 0) {
        float period_factor = (2 * M_PI) / (visualDuration * 1.2f); // 可视化周期
        springOptions.stiffness = period_factor * period_factor;    // 刚度

        // 预计算sqrt避免重复计算
        float sqrt_stiffness_mass = period_factor; // 因为mass=1，所以sqrt(stiffness*mass) = period_factor
        springOptions.damping = 2 * (1.0f - bounce) * sqrt_stiffness_mass; // 阻尼系数
    } else {
        // 如果未提供 visualDuration，使用默认的 duration 和 bounce 来推导
        float duration_s = duration / 1000.0f;
        springOptions.stiffness = 36.0f / (duration_s * duration_s); // 刚度

        // 预计算sqrt避免重复计算
        float sqrt_stiffness_mass = 6.0f / duration_s;                     // sqrt(36/duration²) = 6/duration
        springOptions.damping = 2 * (1.0f - bounce) * sqrt_stiffness_mass; // 阻尼系数
    }
}

void Spring::init()
{
    done = false;
    value = start;

    // If or duration or visualDuration is provided, set spring options by duration/bounce-based options
    if (springOptions.duration > 0 || springOptions.visualDuration > 0) {
        setSpringOptions(springOptions.duration, springOptions.bounce, springOptions.visualDuration);
    }

    // 预计算常量 - 优化计算顺序避免重复
    _sqrt_stiffness_mass = std::sqrt(springOptions.stiffness * springOptions.mass);
    _undamped_angular_freq = _sqrt_stiffness_mass / springOptions.mass; // sqrt(k/m) = sqrt(k*m)/m
    _damping_ratio = springOptions.damping / (2 * _sqrt_stiffness_mass);
    _initial_delta = end - start;

    // 根据阻尼比选择不同的公式
    if (_damping_ratio < 1) {
        _damping_type = DampingType::Underdamped;
        _damped_angular_freq = calc_angular_freq(_undamped_angular_freq, _damping_ratio);

        // 欠阻尼 - 预计算速度公式系数
        _velocity_c1 =
            (springOptions.velocity + _damping_ratio * _undamped_angular_freq * _initial_delta) / _damped_angular_freq;
        _velocity_c2 = _initial_delta;
    } else if (_damping_ratio == 1) {
        _damping_type = DampingType::Critical;
        // 临界阻尼 - 预计算速度公式系数
        _velocity_c1 = springOptions.velocity + _undamped_angular_freq * _initial_delta;
        _velocity_c2 = _initial_delta;
    } else {
        _damping_type = DampingType::Overdamped;
        // 过阻尼 - 预计算速度公式系数
        _damped_angular_freq = _undamped_angular_freq * std::sqrt(_damping_ratio * _damping_ratio - 1);
        _velocity_c1 =
            (springOptions.velocity + _damping_ratio * _undamped_angular_freq * _initial_delta) / _damped_angular_freq;
        _velocity_c2 = _damped_angular_freq * _initial_delta;
    }
}

void Spring::retarget(const float& start, const float& end)
{
    springOptions.velocity = -_current_velocity;
    this->start = start;
    this->end = end;
    init();
}

bool Spring::next(const float& t)
{
    if (done) {
        return done;
    }

    // 使用内联计算替代function对象
    value = calc_position(t);

    // 检查是否接近静止
    calc_velocity_analytical(t);
    bool isBelowVelocityThreshold = std::abs(_current_velocity) <= springOptions.restSpeed;
    bool isBelowDisplacementThreshold = std::abs(end - value) <= springOptions.restDelta;
    done = isBelowVelocityThreshold && isBelowDisplacementThreshold;

    return done;
}

void Spring::calc_velocity_analytical(const float& t)
{
    if (_damping_ratio < 1) {
        // 欠阻尼解析速度公式
        float envelope = std::exp(-_damping_ratio * _undamped_angular_freq * t);
        float sin_term = std::sin(_damped_angular_freq * t);
        float cos_term = std::cos(_damped_angular_freq * t);

        _current_velocity =
            envelope * (_damping_ratio * _undamped_angular_freq * (_velocity_c1 * sin_term + _velocity_c2 * cos_term) -
                        _damped_angular_freq * (_velocity_c1 * cos_term - _velocity_c2 * sin_term));
    } else if (_damping_ratio == 1) {
        // 临界阻尼解析速度公式
        float envelope = std::exp(-_undamped_angular_freq * t);
        _current_velocity = envelope * (_undamped_angular_freq * (_velocity_c2 + _velocity_c1 * t) - _velocity_c1);
    } else {
        // 过阻尼解析速度公式
        float envelope = std::exp(-_damping_ratio * _undamped_angular_freq * t);
        float freqForT = std::min(_damped_angular_freq * t, 300.0f);
        float sinh_term = std::sinh(freqForT);
        float cosh_term = std::cosh(freqForT);

        _current_velocity =
            envelope *
            ((_damping_ratio * _undamped_angular_freq * (_velocity_c1 * sinh_term + _velocity_c2 * cosh_term)) /
                 _damped_angular_freq -
             (_velocity_c1 * cosh_term + _velocity_c2 * sinh_term));
    }
}

float Spring::calc_angular_freq(float undampedFreq, float dampingRatio)
{
    return undampedFreq * std::sqrt(1 - dampingRatio * dampingRatio);
}

float Spring::calc_position(const float& t)
{
    switch (_damping_type) {
        case DampingType::Underdamped: {
            float envelope = std::exp(-_damping_ratio * _undamped_angular_freq * t);
            return (end - envelope * (_velocity_c1 * std::sin(_damped_angular_freq * t) +
                                      _velocity_c2 * std::cos(_damped_angular_freq * t)));
        }
        case DampingType::Critical: {
            return end - std::exp(-_undamped_angular_freq * t) * (_velocity_c2 + _velocity_c1 * t);
        }
        case DampingType::Overdamped: {
            float envelope = std::exp(-_damping_ratio * _undamped_angular_freq * t);
            float freqForT = std::min(_damped_angular_freq * t, 300.0f);
            return (end - (envelope * (_velocity_c1 * std::sinh(freqForT) + _velocity_c2 * std::cosh(freqForT))) /
                              _damped_angular_freq);
        }
    }
    return end; // fallback
}
