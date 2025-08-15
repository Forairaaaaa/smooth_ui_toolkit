/**
 * @file vector.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-08-15
 *
 * @copyright Copyright (c) 2025
 *
 */
// ref: https://github.com/godotengine/godot/blob/master/core/math/vector2.h
#pragma once
#include "base.h"

namespace smooth_ui_toolkit {

/**
 * @brief
 *
 */
template <typename T>
struct Vector2Base {
    union {
        struct {
            T x;
            T y;
        };

        struct {
            T width;
            T height;
        };

        T coord[2] = {0};
    };

    Vector2Base() : x(0), y(0) {}
    Vector2Base(T x, T y) : x(x), y(y) {}
    Vector2Base(const Vector2Base& other) : x(other.x), y(other.y) {}

    Vector2Base& operator=(const Vector2Base& other)
    {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    void set(const T& new_x, const T& new_y)
    {
        x = new_x;
        y = new_y;
    }

    Vector2Base clamp(const Vector2Base& p_min, const Vector2Base& p_max)
    {
        return Vector2Base(smooth_ui_toolkit::clamp(x, p_min.x, p_max.x),
                           smooth_ui_toolkit::clamp(y, p_min.y, p_max.y));
    }
};

/**
 * @brief A 2D vector using floating-point coordinates.
 *
 */
using Vector2 = Vector2Base<float>;

/**
 * @brief A 2D vector using integer coordinates.
 *
 */
using Vector2i = Vector2Base<int>;

/**
 * @brief
 *
 */
template <typename T>
struct Vector4Base {
    union {
        struct {
            T x;
            T y;
            T z;
            T w;
        };

        struct {
            T pos_x;
            T pos_y;
            T width;
            T height;
        };

        T coord[4] = {0};
    };

    Vector4Base() : x(0), y(0), z(0), w(0) {}
    Vector4Base(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
    Vector4Base(const Vector4Base& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}

    Vector4Base& operator=(const Vector4Base& other)
    {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
            w = other.w;
        }
        return *this;
    }

    void set(const T& newX, const T& newY, const T& newZ, const T& newW)
    {
        x = newX;
        y = newY;
        z = newZ;
        w = newW;
    }

    Vector4Base clamp(const Vector4Base& pMin, const Vector4Base& pMax)
    {
        return Vector4Base(smooth_ui_toolkit::clamp(x, pMin.x, pMax.x),
                           smooth_ui_toolkit::clamp(y, pMin.y, pMax.y),
                           smooth_ui_toolkit::clamp(z, pMin.z, pMax.z),
                           smooth_ui_toolkit::clamp(w, pMin.w, pMax.w));
    }
};

/**
 * @brief A 4D vector using floating-point coordinates.
 *
 */
using Vector4 = Vector4Base<float>;

/**
 * @brief A 4D vector using integer coordinates.
 *
 */
using Vector4i = Vector4Base<int>;

} // namespace smooth_ui_toolkit
