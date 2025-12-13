/**
 * @file animate_value.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-08
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "../animate/animate.hpp"

namespace smooth_ui_toolkit {

class AnimateValue : public Animate {
public:
    AnimateValue();
    AnimateValue(float defaultValue);
    ~AnimateValue() {}

    // Enable move constructor and move assignment operator
    AnimateValue(AnimateValue&& other) noexcept;
    AnimateValue& operator=(AnimateValue&& other) noexcept;

    // Override assignment operator
    AnimateValue& operator=(float newValue);

    // Override type conversion
    operator float();

    /**
     * @brief Begin value animation
     *
     */
    void begin();

    /**
     * @brief Stop value animation
     *
     */
    void stop();

    /**
     * @brief Set to a new value immediately
     *
     */
    void teleport(float newValue);

    /**
     * @brief Move to a new value
     *
     * @param newValue
     */
    void move(float newValue);

    /**
     * @brief Current value
     *
     * @return float
     */
    float value();

    /**
     * @brief Get current value without trigger auto update
     *
     * @return float
     */
    float directValue();

private:
    bool _is_begin = false;
    float _default_value = 0.0f;
};

} // namespace smooth_ui_toolkit
