/**
 * @file easing.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-03-29
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "../generators.hpp"
#include "../../../core/easing/ease.hpp"
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
        _inv_duration = 1.0f / duration; // 更新持续时间倒数
    }
    inline void setEasingOptions(const EasingOptions_t& options)
    {
        easingOptions = options;
        _inv_duration = 1.0f / options.duration; // 更新持续时间倒数
    }

    virtual void init() override;
    virtual void retarget(const float& start, const float& end) override;
    virtual bool next(const float& t) override;
    virtual AnimationType type() const override
    {
        return AnimationType::Easing;
    }

private:
    float _range = 0.0f;        // 缓存 end - start 的计算结果
    float _inv_duration = 1.0f; // 缓存 1.0f / duration 的计算结果
};

} // namespace smooth_ui_toolkit
