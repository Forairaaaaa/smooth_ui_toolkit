/**
 * @file arkanoid.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-20
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "core/math/vector.hpp"
#include "games/core/shape.hpp"
#include "games/core/collision.hpp"
#include "core/hal/hal.hpp"
#include <vector>

namespace smooth_ui_toolkit::games::arkanoid {

/**
 * @brief
 *
 */
class Entity {
public:
    enum class Type { Ball, Wall, Brick, Player };

    Type type()
    {
        return _type;
    }

    virtual void _process(const float& delta) {}

protected:
    explicit Entity(Type type) : _type(type) {}

    Type _type;
};

/**
 * @brief
 *
 */
class Wall : public Entity {
public:
    Wall(Vector2 position = {}, Vector2 size = {}) : Entity(Type::Wall), shape(position, size) {}

    RectShape shape;
};

/**
 * @brief
 *
 */
class Ball : public Entity {
public:
    Ball(Vector2 position = {}, float radius = 0.0f) : Entity(Type::Ball), shape(position, radius), hitbox(shape) {}

    CircleShape shape;
    CollisionShape hitbox;
    Vector2 velocity;

    void _process(const float& delta) override
    {
        shape.position.x += velocity.x * delta;
        shape.position.y += velocity.y * delta;
    }

private:
};

/**
 * @brief
 *
 */
struct Renderable {
    std::vector<Wall> walls;
    Ball ball;
};

class Arkanoid {
public:
    void init()
    {
        onInit();
        _last_tick = ui_hal::get_tick_s();
    }

    void update()
    {
        _delta = ui_hal::get_tick_s() - _last_tick;

        for (auto& wall : _renderable.walls) {
            if (_renderable.ball.hitbox.isCollidingWith(wall.shape)) {
                printf("????\n");
                _renderable.ball.velocity.x = -_renderable.ball.velocity.x;
                _renderable.ball.velocity.y = -_renderable.ball.velocity.y;
            }
        }
        _renderable.ball._process(_delta);

        _last_tick = ui_hal::get_tick_s();
    }

    void render()
    {
        onRender(_renderable);
    }

    void addWall(const Vector2& position, const Vector2& size)
    {
        _renderable.walls.push_back(Wall(position, size));
    }

    virtual void onInit() {}
    virtual void onRender(const Renderable& renderable) {}

protected:
    Renderable _renderable;
    float _last_tick = 0.0f;
    float _delta = 0.0f;
};

} // namespace smooth_ui_toolkit::games::arkanoid
