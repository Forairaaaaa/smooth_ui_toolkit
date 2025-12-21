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
    Paddle(Vector2 pos, Vector2 size, float speed, Vector2 xLimits)
    {
        groupId = static_cast<int>(Group::Player);

        add(std::make_unique<Transform>(pos));
        add(std::make_unique<RectShape>(size));
        add(std::make_unique<Area>());

        this->speed = speed;
        this->minX = xLimits.x;
        this->maxX = xLimits.y;
    }

    float speed;
    float minX;
    float maxX;

    void onReady() override {}

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
