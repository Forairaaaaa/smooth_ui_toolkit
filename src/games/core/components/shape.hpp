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
#include "component.hpp"
#include <cstdint>

namespace smooth_ui_toolkit::games::engine {

/**
 * @brief
 *
 */
enum class ShapeType : uint8_t { Circle = 0, Rect = 1, COUNT };

/**
 * @brief
 *
 */
class Shape : public Component {
public:
    static constexpr ComponentType Type = ComponentType::Shape;

    ShapeType shapeType() const
    {
        return _shape_type;
    }

protected:
    explicit Shape(ShapeType type) : Component(Type), _shape_type(type) {}
    ShapeType _shape_type;
};

/**
 * @brief
 *
 */
class CircleShape : public Shape {
public:
    CircleShape(float radius) : Shape(ShapeType::Circle), radius(radius) {}

    float radius;
};

/**
 * @brief
 *
 */
class RectShape : public Shape {
public:
    RectShape(const Vector2& size) : Shape(ShapeType::Rect), size(size) {}

    Vector2 size;
};

} // namespace smooth_ui_toolkit::games::engine
