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

struct SpringOptions_t {
    float stiffness = 100.0;    // 弹性系数
    float damping = 10.0;       // 阻尼系数
    float mass = 1.0;           // 质量
    float velocity = 0.0;       // 初始速度
    float restSpeed = 0.1;      // 静止速度阈值
    float restDelta = 0.1;      // 静止位置阈值
    float duration = 0.0;       // 动画持续时间 ms
    float bounce = 0.3;         // 反弹系数 0.05~1.0
    float visualDuration = 0.0; // 可视化时间
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
    virtual bool next(const float& t) override;
    virtual Type_t type() const override
    {
        return Type_t::Spring;
    }

protected:
    float _damping_ratio;                        // 阻尼比
    float _undamped_angular_freq;                // 未阻尼角频率
    std::function<float(float)> _resolve_spring; // 动画计算公式

    float calc_velocity(const float& t);
    float calc_angular_freq(float undampedFreq, float dampingRatio);
};

} // namespace smooth_ui_toolkit
