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

namespace smooth_ui_toolkit::games {

/**
 * @brief
 *
 */
namespace collision {

inline static bool collide_rect_rect_impl(const RectShape& a, const RectShape& b)
{
    const int ax_half = a.size.x >> 1;
    const int ay_half = a.size.y >> 1;
    const int bx_half = b.size.x >> 1;
    const int by_half = b.size.y >> 1;

    // 分离轴判断
    if (a.position.x + ax_half < b.position.x - bx_half) {
        return false;
    }
    if (a.position.x - ax_half > b.position.x + bx_half) {
        return false;
    }
    if (a.position.y + ay_half < b.position.y - by_half) {
        return false;
    }
    if (a.position.y - ay_half > b.position.y + by_half) {
        return false;
    }

    return true;
}

inline static bool collide_circle_circle_impl(const CircleShape& a, const CircleShape& b)
{
    const int64_t dx = (int64_t)a.position.x - b.position.x;
    const int64_t dy = (int64_t)a.position.y - b.position.y;
    const int64_t r = (int64_t)a.radius + b.radius;

    return dx * dx + dy * dy <= r * r;
}

inline static bool collide_circle_rect_impl(const CircleShape& c, const RectShape& r)
{
    const int rx_half = r.size.x >> 1;
    const int ry_half = r.size.y >> 1;

    const int rx_min = r.position.x - rx_half;
    const int rx_max = r.position.x + rx_half;
    const int ry_min = r.position.y - ry_half;
    const int ry_max = r.position.y + ry_half;

    // clamp 圆心到矩形最近点
    int closest_x = c.position.x;
    if (closest_x < rx_min) {
        closest_x = rx_min;
    } else if (closest_x > rx_max) {
        closest_x = rx_max;
    }

    int closest_y = c.position.y;
    if (closest_y < ry_min) {
        closest_y = ry_min;
    } else if (closest_y > ry_max) {
        closest_y = ry_max;
    }

    const int64_t dx = (int64_t)c.position.x - closest_x;
    const int64_t dy = (int64_t)c.position.y - closest_y;

    return dx * dx + dy * dy <= (int64_t)c.radius * c.radius;
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
