/**
 * @file easing.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-03-29
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "../generators.h"
#include "../../../utils/easing/ease.h"
#include <functional>

namespace smooth_ui_toolkit {

struct EasingOptions_t {
    float duration = 1.0f;                                               // 动画持续时间，单位 s
    std::function<float(float)> easingFunction = ease::ease_in_out_quad; // 缓动函数
};

class Easing : public KeyFrameGenerator {
public:
    Easing() {}
    ~Easing() {}

    EasingOptions_t easingOptions;

    inline void setEasingOptions(float duration, std::function<float(float)> easingFunction)
    {
        easingOptions.duration = duration;
        easingOptions.easingFunction = easingFunction;
    }
    inline void setEasingOptions(const EasingOptions_t& options)
    {
        easingOptions = options;
    }

    virtual void init() override;
    virtual void retarget(const float& start, const float& end) override;
    virtual bool next(const float& t) override;
    virtual animation_type::Type_t type() const override
    {
        return animation_type::easing;
    }
};

} // namespace smooth_ui_toolkit
