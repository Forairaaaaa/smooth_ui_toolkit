/**
 * @file paddle.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "types.hpp"
#include "core/math/vector.hpp"
#include "games/core/core.h"

namespace smooth_ui_toolkit::games::breakout {

class Paddle : public GameObject {
public:
    float speed = 0.0f;
    float minX = 0.0f;
    float maxX = 0.0f;

    void onInit() override {}

    void move(float dir, float dt)
    {
        if (dir == 0.0f) {
            return;
        }

        auto transform = get<Transform>();
        auto shape = get<RectShape>();

        transform->position.x += dir * speed * dt;

        float half = shape->size.x * 0.5f;
        transform->position.x = std::clamp(transform->position.x, minX + half, maxX - half);
    }

    Vector2 position()
    {
        return get<Transform>()->position;
    }

    Vector2 size()
    {
        return get<RectShape>()->size;
    }
};

} // namespace smooth_ui_toolkit::games::breakout
