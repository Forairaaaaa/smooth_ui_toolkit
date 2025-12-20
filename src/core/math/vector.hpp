/**
 * @file vector.hpp
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
#include "base.hpp"
#include <cmath>

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
struct Vector2 : public Vector2Base<float> {
    Vector2() : Vector2Base<float>() {}
    Vector2(float x, float y) : Vector2Base<float>(x, y) {}
    Vector2(const Vector2Base<float>& other) : Vector2Base<float>(other) {}

    // 从整数向量转换
    Vector2(const Vector2Base<int>& other)
        : Vector2Base<float>(static_cast<float>(other.x), static_cast<float>(other.y))
    {
    }

    // 显式转换操作符
    explicit operator Vector2Base<int>() const
    {
        return Vector2Base<int>(static_cast<int>(x), static_cast<int>(y));
    }

    float length() const
    {
        return std::sqrt(x * x + y * y);
    }
};

/**
 * @brief A 2D vector using integer coordinates.
 *
 */
struct Vector2i : public Vector2Base<int> {
    Vector2i() : Vector2Base<int>() {}
    Vector2i(int x, int y) : Vector2Base<int>(x, y) {}
    Vector2i(const Vector2Base<int>& other) : Vector2Base<int>(other) {}

    // 从浮点向量转换
    Vector2i(const Vector2Base<float>& other) : Vector2Base<int>(static_cast<int>(other.x), static_cast<int>(other.y))
    {
    }

    // 显式转换操作符
    explicit operator Vector2Base<float>() const
    {
        return Vector2Base<float>(static_cast<float>(x), static_cast<float>(y));
    }
};

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
struct Vector4 : public Vector4Base<float> {
    Vector4() : Vector4Base<float>() {}
    Vector4(float x, float y, float z, float w) : Vector4Base<float>(x, y, z, w) {}
    Vector4(const Vector4Base<float>& other) : Vector4Base<float>(other) {}

    // 从整数向量转换
    Vector4(const Vector4Base<int>& other)
        : Vector4Base<float>(static_cast<float>(other.x),
                             static_cast<float>(other.y),
                             static_cast<float>(other.z),
                             static_cast<float>(other.w))
    {
    }

    // 显式转换操作符
    explicit operator Vector4Base<int>() const
    {
        return Vector4Base<int>(static_cast<int>(x), static_cast<int>(y), static_cast<int>(z), static_cast<int>(w));
    }
};

/**
 * @brief A 4D vector using integer coordinates.
 *
 */
struct Vector4i : public Vector4Base<int> {
    Vector4i() : Vector4Base<int>() {}
    Vector4i(int x, int y, int z, int w) : Vector4Base<int>(x, y, z, w) {}
    Vector4i(const Vector4Base<int>& other) : Vector4Base<int>(other) {}

    // 从浮点向量转换
    Vector4i(const Vector4Base<float>& other)
        : Vector4Base<int>(static_cast<int>(other.x),
                           static_cast<int>(other.y),
                           static_cast<int>(other.z),
                           static_cast<int>(other.w))
    {
    }

    // 显式转换操作符
    explicit operator Vector4Base<float>() const
    {
        return Vector4Base<float>(
            static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w));
    }
};

} // namespace smooth_ui_toolkit
