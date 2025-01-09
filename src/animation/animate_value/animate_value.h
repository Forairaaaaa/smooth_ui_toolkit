/**
 * @file animate_value.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-08
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "../animate/animate.h"

namespace smooth_ui_toolkit {

class AnimateValue : public Animate {
public:
    AnimateValue() {}
    AnimateValue(float defaultValue) : _default_value(defaultValue) {}
    ~AnimateValue() {}

    /**
     * @brief Begin value animation
     *
     */
    void begin();

    // Override assignment operator
    AnimateValue& operator=(float newValue);

    // Override type conversion
    operator float();

private:
    float _default_value = 0.0f;
};

} // namespace smooth_ui_toolkit
