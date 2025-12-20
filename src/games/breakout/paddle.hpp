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

    void onInit() override
    {
        groupId = static_cast<int>(Group::Player);
        _transform = get<Transform>();
        _shape = get<RectShape>();
    }

    void move(float dir, float dt)
    {
        if (dir == 0.0f) {
            return;
        }

        _transform->position.x += dir * speed * dt;

        float half = _shape->size.x * 0.5f;
        _transform->position.x = std::clamp(_transform->position.x, minX + half, maxX - half);
    }

    Vector2 position() const
    {
        return _transform->position;
    }
    Vector2 size() const
    {
        return _shape->size;
    }

private:
    Transform* _transform = nullptr;
    RectShape* _shape = nullptr;
};

} // namespace smooth_ui_toolkit::games::breakout
