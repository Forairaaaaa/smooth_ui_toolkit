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
    ~AnimateValue() {}

    /**
     * @brief Begin value animation
     *
     */
    void begin();

    // Override assignment operator
    AnimateValue& operator=(int newValue);
    AnimateValue& operator=(float newValue);
    AnimateValue& operator=(double newValue);

    // Override type conversion
    operator int();
    operator float();
    operator double();
};

} // namespace smooth_ui_toolkit
