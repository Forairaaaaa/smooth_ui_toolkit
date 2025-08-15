/**
 * @file animate_vector2.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-08-15
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "utils/math/vector.h"
#include "../animate_value/animate_value.h"

namespace smooth_ui_toolkit {

class AnimateVector2 {
public:
    AnimateValue x;
    AnimateValue y;

    AnimateVector2();
    AnimateVector2(const Vector2& defaultValue);
    AnimateVector2(float defaultX, float defaultY);
    ~AnimateVector2() {}

    // Enable move constructor and move assignment operator
    AnimateVector2(AnimateVector2&& other) noexcept;
    AnimateVector2& operator=(AnimateVector2&& other) noexcept;

    // Disable copy constructor and copy assignment operator
    AnimateVector2(const AnimateVector2&) = delete;
    AnimateVector2& operator=(const AnimateVector2&) = delete;

    // Override assignment operator
    AnimateVector2& operator=(const Vector2& newValue);

    // Override type conversion
    operator Vector2();

    /**
     * @brief Begin vector animation
     *
     */
    void begin();

    /**
     * @brief Stop vector animation
     *
     */
    void stop();

    /**
     * @brief Set to a new value immediately
     *
     * @param newValue
     */
    void teleport(const Vector2& newValue);
    void teleport(float newX, float newY);

    /**
     * @brief Move to a new value
     *
     * @param newValue
     */
    void move(const Vector2& newValue);
    void move(float newX, float newY);

    /**
     * @brief Current vector value
     *
     * @return Vector2
     */
    Vector2 value();

    /**
     * @brief Get current value without trigger auto update
     *
     * @return Vector2
     */
    Vector2 directValue();
};

} // namespace smooth_ui_toolkit