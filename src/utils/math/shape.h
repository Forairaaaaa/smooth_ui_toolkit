/**
 * @file shape.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-08-16
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "vector.h"

namespace smooth_ui_toolkit {

enum Anchor_t {
    anchor_top_left,
    anchor_top_center,
    anchor_top_right,
    anchor_center_left,
    anchor_center,
    anchor_center_right,
    anchor_bottom_left,
    anchor_bottom_center,
    anchor_bottom_right
};

namespace shape {

/**
 * @brief Get anchor offset relative to top_left
 */
template <typename T>
Vector2Base<T> get_anchor_offset(const Vector4Base<T>& rect, Anchor_t anchor)
{
    Vector2Base<T> offset{0, 0};

    // X offset
    if (anchor == anchor_top_center || anchor == anchor_center || anchor == anchor_bottom_center) {
        offset.x = rect.width / 2;
    } else if (anchor == anchor_top_right || anchor == anchor_center_right || anchor == anchor_bottom_right) {
        offset.x = rect.width;
    }

    // Y offset
    if (anchor == anchor_center_left || anchor == anchor_center || anchor == anchor_center_right) {
        offset.y = rect.height / 2;
    } else if (anchor == anchor_bottom_left || anchor == anchor_bottom_center || anchor == anchor_bottom_right) {
        offset.y = rect.height;
    }

    return offset;
}

/**
 * @brief Convert anchor point of a rectangle
 *
 * @tparam T
 * @param rect
 * @param from
 * @param to
 * @return Vector4Base<T>
 */
template <typename T>
Vector4Base<T> convert_anchor(const Vector4Base<T>& rect, Anchor_t from, Anchor_t to)
{
    Vector4Base<T> result = rect;

    auto from_offset = get_anchor_offset(rect, from);
    auto to_offset = get_anchor_offset(rect, to);

    result.pos_x += from_offset.x - to_offset.x;
    result.pos_y += from_offset.y - to_offset.y;

    return result;
}

/**
 * @brief Scale a rectangle by a scale factor with specified anchor point
 *
 * @tparam T
 * @param rect
 * @param anchor 缩放的基准锚点
 * @param scaleFactor
 * @return Vector4Base<T>
 */
template <typename T>
Vector4Base<T> scale(const Vector4Base<T>& rect, const Anchor_t& anchor, const Vector2Base<T>& scaleFactor)
{
    // 计算锚点在原矩形中的绝对位置
    auto anchor_offset = get_anchor_offset(rect, anchor);
    Vector2Base<T> anchor_pos{rect.pos_x + anchor_offset.x, rect.pos_y + anchor_offset.y};

    // 创建缩放后的矩形
    Vector4Base<T> scaled_rect = rect;
    scaled_rect.width *= scaleFactor.x;
    scaled_rect.height *= scaleFactor.y;

    // 根据锚点位置调整缩放后矩形的位置，保持锚点位置不变
    auto scaled_anchor_offset = get_anchor_offset(scaled_rect, anchor);
    scaled_rect.pos_x = anchor_pos.x - scaled_anchor_offset.x;
    scaled_rect.pos_y = anchor_pos.y - scaled_anchor_offset.y;

    return scaled_rect;
}

} // namespace shape
} // namespace smooth_ui_toolkit