/**
 * @file ball.hpp
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
#include "brick.hpp"
#include "games/core/core.h"

namespace smooth_ui_toolkit::games::breakout {

class Ball : public GameObject {
public:
    Ball(Vector2 pos, float radius, float speed, int damage = 1)
    {
        groupId = static_cast<int>(Group::Ball);

        add(std::make_unique<Transform>(pos));
        add(std::make_unique<CircleShape>(radius));
        add(std::make_unique<Area>(collision_layer::Ball,
                                   collision_layer::Wall | collision_layer::Player | collision_layer::Brick));
        add(std::make_unique<Rigidbody>());

        this->speed = speed;
        this->damage = damage;
        sync_rigidbody();
    }

    float speed;
    Vector2 direction;
    int damage;

    bool active = false;

    void onReady() override
    {
        setup_collision();
    }

    void launch(Vector2 dir)
    {
        direction = dir.normalized();
        active = true;
        sync_rigidbody();
    }

    void stop()
    {
        direction = {0, 0};
        active = false;
        sync_rigidbody();
    }

    float radius()
    {
        return get<CircleShape>()->radius;
    }

private:
    void reflect_from_paddle(GameObject& paddle)
    {
        auto ball_pos = get<Transform>()->position;
        auto pad_os = paddle.get<Transform>()->position;
        auto pad_size = paddle.get<RectShape>()->size;

        float hit = (ball_pos.x - pad_os.x) / (pad_size.x * 0.5f);
        hit = std::clamp(hit, -1.0f, 1.0f);

        direction = {hit, -1.0f};
        direction = direction.normalized();
        sync_rigidbody();
    }

    void reflect_from_wall(GameObject& wall)
    {
        auto transform = get<Transform>();
        auto ball_pos = transform->position;
        auto ball_radius = get<CircleShape>()->radius;
        auto wall_pos = wall.get<Transform>()->position;
        auto wall_size = wall.get<RectShape>()->size;

        float dx = ball_pos.x - wall_pos.x;
        float dy = ball_pos.y - wall_pos.y;

        float px = (wall_size.x * 0.5f + ball_radius) - std::abs(dx);
        float py = (wall_size.y * 0.5f + ball_radius) - std::abs(dy);

        if (px < py) {
            float sign = dx > 0 ? 1.0f : -1.0f;
            transform->position.x += px * sign;
            direction.x *= -1;
        } else {
            float sign = dy > 0 ? 1.0f : -1.0f;
            transform->position.y += py * sign;
            direction.y *= -1;
        }

        direction = direction.normalized();
        sync_rigidbody();
    }

    void reflect_from_brick(GameObject& brick)
    {
        reflect_from_wall(brick);
        static_cast<Brick*>(&brick)->damage(damage);
    }

    void setup_collision()
    {
        auto area = get<Area>();
        area->onEntered.connect([this](GameObject& other) {
            auto* other_area = other.get<Area>();
            if (!other_area) {
                return;
            }

            const uint32_t layer = other_area->collisionLayer;
            if (layer & collision_layer::Wall) {
                reflect_from_wall(other);
            }

            if (layer & collision_layer::Player) {
                reflect_from_paddle(other);
            }

            if (layer & collision_layer::Brick) {
                reflect_from_brick(other);
            }
        });
    }

    void sync_rigidbody()
    {
        auto* rigidbody = get<Rigidbody>();
        if (!rigidbody) {
            return;
        }

        rigidbody->velocity = active ? direction * speed : Vector2{0, 0};
        rigidbody->enabled = active;
    }
};

} // namespace smooth_ui_toolkit::games::breakout
