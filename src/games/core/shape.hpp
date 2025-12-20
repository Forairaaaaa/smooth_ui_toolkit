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

protected:
    explicit Shape(ShapeType type) : _type(type) {}
    ShapeType _type;
};

/**
 * @brief
 *
 */
class CircleShape : public Shape {
public:
    CircleShape(Vector2i& position, int radius) : Shape(ShapeType::Circle), position(position), radius(radius) {}

    Vector2i& position;
    int radius = 0;
};

/**
 * @brief
 *
 */
class RectShape : public Shape {
public:
    RectShape(Vector2i& position, const Vector2i& size) : Shape(ShapeType::Rect), position(position), size(size) {}

    Vector2i& position;
    Vector2i size;
};

} // namespace smooth_ui_toolkit::games
