/**
 * @file collision.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-20
 *
 * @copyright Copyright (c) 2025
 *
 */
// https://github.com/godotengine/godot/blob/master/scene/2d/physics/collision_shape_2d.h
// https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
#pragma once
#include "shape.hpp"
#include <algorithm>

namespace smooth_ui_toolkit::games {

/**
 * @brief
 *
 */
namespace collision {

inline static bool collide_rect_rect_impl(const RectShape& a, const RectShape& b)
{
    const float ax_half = a.size.x * 0.5f;
    const float ay_half = a.size.y * 0.5f;
    const float bx_half = b.size.x * 0.5f;
    const float by_half = b.size.y * 0.5f;

    if (a.position.x + ax_half < b.position.x - bx_half)
        return false;
    if (a.position.x - ax_half > b.position.x + bx_half)
        return false;
    if (a.position.y + ay_half < b.position.y - by_half)
        return false;
    if (a.position.y - ay_half > b.position.y + by_half)
        return false;

    return true;
}

inline static bool collide_circle_circle_impl(const CircleShape& a, const CircleShape& b)
{
    const float dx = a.position.x - b.position.x;
    const float dy = a.position.y - b.position.y;
    const float r = a.radius + b.radius;

    return dx * dx + dy * dy <= r * r;
}

inline static bool collide_circle_rect_impl(const CircleShape& c, const RectShape& r)
{
    const float rx_half = r.size.x * 0.5f;
    const float ry_half = r.size.y * 0.5f;

    const float rx_min = r.position.x - rx_half;
    const float rx_max = r.position.x + rx_half;
    const float ry_min = r.position.y - ry_half;
    const float ry_max = r.position.y + ry_half;

    // clamp 圆心到矩形最近点
    float closest_x = std::clamp(c.position.x, rx_min, rx_max);
    float closest_y = std::clamp(c.position.y, ry_min, ry_max);

    const float dx = c.position.x - closest_x;
    const float dy = c.position.y - closest_y;

    return dx * dx + dy * dy <= c.radius * c.radius;
}

/* -------------------------------------------------------------------------- */
/*                               Function table                               */
/* -------------------------------------------------------------------------- */

using CollideFn = bool (*)(const Shape&, const Shape&);

#define DEFINE_COLLIDE_ADAPTER(FUNC, TYPE_A, TYPE_B, SHAPE_A, SHAPE_B)                      \
    inline bool FUNC(const Shape& a, const Shape& b)                                        \
    {                                                                                       \
        return FUNC##_impl(static_cast<const SHAPE_A&>(a), static_cast<const SHAPE_B&>(b)); \
    }

#define DEFINE_COLLIDE_SWAP_ADAPTER(NAME)                   \
    inline bool NAME##_swap(const Shape& a, const Shape& b) \
    {                                                       \
        return NAME(b, a);                                  \
    }

DEFINE_COLLIDE_ADAPTER(collide_circle_rect, Circle, Rect, CircleShape, RectShape)
DEFINE_COLLIDE_ADAPTER(collide_circle_circle, Circle, Circle, CircleShape, CircleShape)
DEFINE_COLLIDE_ADAPTER(collide_rect_rect, Rect, Rect, RectShape, RectShape)

DEFINE_COLLIDE_SWAP_ADAPTER(collide_circle_rect)

static constexpr CollideFn CollideTable[(int)ShapeType::COUNT][(int)ShapeType::COUNT] = {
    // a = Circle
    {
        collide_circle_circle, // b = Circle
        collide_circle_rect    // b = Rect
    },

    // a = Rect
    {// Rect - Circle = Circle - Rect (交换参数)
     collide_circle_rect_swap,
     collide_rect_rect}};

inline static bool is_colliding(const Shape& a, const Shape& b)
{
    return CollideTable[(int)a.type()][(int)b.type()](a, b);
}

} // namespace collision

/**
 * @brief
 *
 */
class CollisionShape {
public:
    CollisionShape(Shape& shape) : _shape(shape) {}

    bool isCollidingWith(const Shape& other)
    {
        return collision::is_colliding(_shape, other);
    }

private:
    Shape& _shape;
};

} // namespace smooth_ui_toolkit::games
