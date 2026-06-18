/**
 * @file rigidbody.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "games/core/game_object.hpp"
#include "transform.hpp"

namespace smooth_ui_toolkit::games {

class Rigidbody : public Component {
public:
    static constexpr ComponentType Type = ComponentType::Rigidbody;

    Rigidbody() : Component(Type) {}
    Rigidbody(Vector2 velocity) : Component(Type), velocity(velocity) {}
    Rigidbody(Vector2 velocity, Vector2 acceleration) : Component(Type), velocity(velocity), acceleration(acceleration)
    {
    }

    Vector2 velocity{0, 0};
    Vector2 acceleration{0, 0};
    bool enabled = true;

    void update(float dt) override
    {
        if (!enabled || !owner) {
            return;
        }

        auto* transform = owner->get<Transform>();
        if (!transform) {
            return;
        }

        velocity += acceleration * dt;
        transform->position += velocity * dt;
    }

    void applyImpulse(Vector2 impulse)
    {
        velocity += impulse;
    }
};

} // namespace smooth_ui_toolkit::games
