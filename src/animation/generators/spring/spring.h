/**
 * @file spring.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-06
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "../generators.h"
#include <functional>
// 参考：
// https://github.com/motiondivision/motion/blob/main/packages/framer-motion/src/animation/generators/spring

namespace smooth_ui_toolkit {

struct SpringOptions {
    float stiffness = 100.0; // 弹性系数
    float damping = 10.0;    // 阻尼系数
    float mass = 1.0;        // 质量
    float velocity = 0.0;    // 初始速度
    float restSpeed = 0.1;   // 静止速度阈值
    float restDelta = 0.1;   // 静止位置阈值
};

class Spring : public KeyFrameGenerator {
public:
    Spring() {}
    ~Spring() {}

    SpringOptions springOptions;

    virtual void init() override;
    virtual const AnimationState_t& next(const float& t) override;

protected:
    float _damping_ratio;                        // 阻尼比
    float _undamped_angular_freq;                // 未阻尼角频率
    std::function<float(float)> _resolve_spring; // 动画计算公式

    float calc_velocity(const float& t);
    float calc_angular_freq(float undampedFreq, float dampingRatio);
};

} // namespace smooth_ui_toolkit
