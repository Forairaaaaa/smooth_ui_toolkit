/**
 * @file animate_vector4.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-08-16
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "animate_vector4.hpp"
#include "core/hal/hal.hpp"

using namespace smooth_ui_toolkit;

AnimateVector4::AnimateVector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

AnimateVector4::AnimateVector4(const Vector4& defaultValue)
    : x(defaultValue.x), y(defaultValue.y), z(defaultValue.z), w(defaultValue.w)
{
}

AnimateVector4::AnimateVector4(float defaultX, float defaultY, float defaultZ, float defaultW)
    : x(defaultX), y(defaultY), z(defaultZ), w(defaultW)
{
}

AnimateVector4::AnimateVector4(AnimateVector4&& other) noexcept
    : x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z)), w(std::move(other.w))
{
}

AnimateVector4& AnimateVector4::operator=(AnimateVector4&& other) noexcept
{
    if (this != &other) {
        x = std::move(other.x);
        y = std::move(other.y);
        z = std::move(other.z);
        w = std::move(other.w);
    }
    return *this;
}

AnimateVector4& AnimateVector4::operator=(const Vector4& newValue)
{
    move(newValue);
    return *this;
}

AnimateVector4::operator Vector4()
{
    return value();
}

void AnimateVector4::begin()
{
    x.begin();
    y.begin();
    z.begin();
    w.begin();
}

void AnimateVector4::stop()
{
    x.stop();
    y.stop();
    z.stop();
    w.stop();
}

void AnimateVector4::teleport(const Vector4& newValue)
{
    x.teleport(newValue.x);
    y.teleport(newValue.y);
    z.teleport(newValue.z);
    w.teleport(newValue.w);
}

void AnimateVector4::teleport(float newX, float newY, float newZ, float newW)
{
    x.teleport(newX);
    y.teleport(newY);
    z.teleport(newZ);
    w.teleport(newW);
}

void AnimateVector4::move(const Vector4& newValue)
{
    x.move(newValue.x);
    y.move(newValue.y);
    z.move(newValue.z);
    w.move(newValue.w);
}

void AnimateVector4::move(float newX, float newY, float newZ, float newW)
{
    x.move(newX);
    y.move(newY);
    z.move(newZ);
    w.move(newW);
}

Vector4 AnimateVector4::value()
{
    return Vector4(x.value(), y.value(), z.value(), w.value());
}

Vector4 AnimateVector4::directValue()
{
    return Vector4(x.directValue(), y.directValue(), z.directValue(), w.directValue());
}

void AnimateVector4::update()
{
    auto currentTime = ui_hal::get_tick_s();
    update(currentTime);
}

void AnimateVector4::update(const float& currentTime)
{
    x.update(currentTime);
    y.update(currentTime);
    z.update(currentTime);
    w.update(currentTime);
}

bool AnimateVector4::done()
{
    return x.done() && y.done() && z.done() && w.done();
}
