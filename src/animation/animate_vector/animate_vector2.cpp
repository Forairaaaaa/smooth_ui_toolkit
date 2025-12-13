/**
 * @file animate_vector2.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-08-15
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "animate_vector2.hpp"
#include "utils/hal/hal.hpp"

using namespace smooth_ui_toolkit;

AnimateVector2::AnimateVector2() : x(0.0f), y(0.0f) {}

AnimateVector2::AnimateVector2(const Vector2& defaultValue) : x(defaultValue.x), y(defaultValue.y) {}

AnimateVector2::AnimateVector2(float defaultX, float defaultY) : x(defaultX), y(defaultY) {}

AnimateVector2::AnimateVector2(AnimateVector2&& other) noexcept : x(std::move(other.x)), y(std::move(other.y)) {}

AnimateVector2& AnimateVector2::operator=(AnimateVector2&& other) noexcept
{
    if (this != &other) {
        x = std::move(other.x);
        y = std::move(other.y);
    }
    return *this;
}

AnimateVector2& AnimateVector2::operator=(const Vector2& newValue)
{
    move(newValue);
    return *this;
}

AnimateVector2::operator Vector2()
{
    return value();
}

void AnimateVector2::begin()
{
    x.begin();
    y.begin();
}

void AnimateVector2::stop()
{
    x.stop();
    y.stop();
}

void AnimateVector2::teleport(const Vector2& newValue)
{
    x.teleport(newValue.x);
    y.teleport(newValue.y);
}

void AnimateVector2::teleport(float newX, float newY)
{
    x.teleport(newX);
    y.teleport(newY);
}

void AnimateVector2::move(const Vector2& newValue)
{
    x.move(newValue.x);
    y.move(newValue.y);
}

void AnimateVector2::move(float newX, float newY)
{
    x.move(newX);
    y.move(newY);
}

Vector2 AnimateVector2::value()
{
    return Vector2(x.value(), y.value());
}

Vector2 AnimateVector2::directValue()
{
    return Vector2(x.directValue(), y.directValue());
}

void AnimateVector2::update()
{
    auto currentTime = ui_hal::get_tick_s();
    update(currentTime);
}

void AnimateVector2::update(const float& currentTime)
{
    x.update(currentTime);
    y.update(currentTime);
}

bool AnimateVector2::done()
{
    return x.done() && y.done();
}
