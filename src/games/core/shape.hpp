/**
 * @file shape.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-20
 *
 * @copyright Copyright (c) 2025
 *
 */
// https://github.com/godotengine/godot/tree/master/core/math
#pragma once
#include "core/math/vector.hpp"
#include <cstdint>

namespace smooth_ui_toolkit::games {

/**
 * @brief
 *
 */
enum class ShapeType : uint8_t { Circle = 0, Rect = 1, COUNT };

/**
 * @brief
 *
 */
class Shape {
public:
    ShapeType type() const
    {
        return _type;
    }

    Vector2 position;

protected:
    explicit Shape(ShapeType type, const Vector2& position) : _type(type), position(position) {}
    ShapeType _type;
};

/**
 * @brief
 *
 */
class CircleShape : public Shape {
public:
    CircleShape(const Vector2& position, float radius) : Shape(ShapeType::Circle, position), radius(radius) {}

    float radius;
};

/**
 * @brief
 *
 */
class RectShape : public Shape {
public:
    RectShape(const Vector2& position, const Vector2& size) : Shape(ShapeType::Rect, position), size(size) {}

    Vector2 size;
};

} // namespace smooth_ui_toolkit::games
