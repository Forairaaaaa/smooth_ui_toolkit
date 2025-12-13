/**
 * @file animate_vector4.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-08-16
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "utils/math/vector.hpp"
#include "../animate_value/animate_value.hpp"

namespace smooth_ui_toolkit {

class AnimateVector4 {
public:
    AnimateValue x;
    AnimateValue y;
    AnimateValue z;
    AnimateValue w;

    AnimateVector4();
    AnimateVector4(const Vector4& defaultValue);
    AnimateVector4(float defaultX, float defaultY, float defaultZ, float defaultW);
    ~AnimateVector4() {}

    // Enable move constructor and move assignment operator
    AnimateVector4(AnimateVector4&& other) noexcept;
    AnimateVector4& operator=(AnimateVector4&& other) noexcept;

    // Disable copy constructor and copy assignment operator
    AnimateVector4(const AnimateVector4&) = delete;
    AnimateVector4& operator=(const AnimateVector4&) = delete;

    // Override assignment operator
    AnimateVector4& operator=(const Vector4& newValue);

    // Override type conversion
    operator Vector4();

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
    void teleport(const Vector4& newValue);
    void teleport(float newX, float newY, float newZ, float newW);

    /**
     * @brief Move to a new value
     *
     * @param newValue
     */
    void move(const Vector4& newValue);
    void move(float newX, float newY, float newZ, float newW);

    /**
     * @brief Current vector value
     *
     * @return Vector4
     */
    Vector4 value();

    /**
     * @brief Get current value without trigger auto update
     *
     * @return Vector4
     */
    Vector4 directValue();

    /**
     * @brief Update animation
     *
     */
    void update();

    /**
     * @brief Update animation with explicit current time, more efficient for batch updates
     *
     * @param currentTime Current time in seconds
     */
    void update(const float& currentTime);

    /**
     * @brief Is animation done
     *
     * @return true
     * @return false
     */
    bool done();
};

} // namespace smooth_ui_toolkit