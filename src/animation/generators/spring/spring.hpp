/**
 * @file spring.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-06
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "../generators.hpp"
// 参考：
// https://github.com/motiondivision/motion/blob/main/packages/framer-motion/src/animation/generators/spring

namespace smooth_ui_toolkit {

struct SpringOptions_t {
    float stiffness = 100.0;    // 弹性系数
    float damping = 10.0;       // 阻尼系数
    float mass = 1.0;           // 质量
    float velocity = 0.0;       // 初始速度
    float restSpeed = 0.1;      // 静止速度阈值
    float restDelta = 0.1;      // 静止位置阈值
    float duration = 0.0;       // 动画持续时间 ms
    float bounce = 0.3;         // 反弹系数 0.05~1.0
    float visualDuration = 0.0; // 可视化时间 s
};

class Spring : public KeyFrameGenerator {
public:
    Spring() {}
    ~Spring() {}

    SpringOptions_t springOptions;

    /**
     * @brief Set spring options by duration/bounce-based options
     *
     * @param duration in ms
     * @param bounce 0.05~1.0
     * @param visualDuration in seconds
     */
    void setSpringOptions(float duration = 800.0f, float bounce = 0.3f, float visualDuration = 0.3f);
    inline void setSpringOptions(const SpringOptions_t& options)
    {
        springOptions = options;
    }

    virtual void init() override;
    virtual void retarget(const float& start, const float& end) override;
    virtual bool next(const float& t) override;
    virtual AnimationType type() const override
    {
        return AnimationType::Spring;
    }

protected:
    float _damping_ratio;         // 阻尼比
    float _undamped_angular_freq; // 未阻尼角频率
    float _current_velocity;      // 当前速度

    // 移除function对象，使用内联计算
    enum class DampingType { Underdamped, Critical, Overdamped } _damping_type;

    // 预计算的常量，避免重复计算
    float _sqrt_stiffness_mass; // sqrt(stiffness * mass)
    float _damped_angular_freq; // 阻尼角频率
    float _initial_delta;       // 初始位置差

    // 速度计算相关常量
    float _velocity_c1, _velocity_c2; // 速度公式系数

    void calc_velocity(const float& t);
    void calc_velocity_analytical(const float& t);
    float calc_angular_freq(float undampedFreq, float dampingRatio);

    // 内联位置计算函数
    inline float calc_position(const float& t);
};

} // namespace smooth_ui_toolkit
