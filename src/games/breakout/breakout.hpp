/**
 * @file breakout.hpp
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
#include "games/core/core.h"
#include "core/hal/hal.hpp"

namespace smooth_ui_toolkit::games::breakout {

enum class Action {
    MoveLeft,
    MoveRight,
    Fire,
};

enum class Group : int {
    Ball = 0,
    Wall,
    Player,
    Brick,
};

class Ball : public GameObject {
public:
    Vector2 velocity{0, 0};
    bool active = false;

    void onInit() override
    {
        groupId = static_cast<int>(Group::Ball);
        _transform = get<Transform>();
    }

    void onUpdate(float dt) override
    {
        if (!active) {
            return;
        }
        _transform->position.x += velocity.x * dt;
        _transform->position.y += velocity.y * dt;
    }

    void launch(Vector2 v)
    {
        velocity = v;
        active = true;
    }

    float radius()
    {
        return get<CircleShape>()->radius;
    }

private:
    Transform* _transform = nullptr;
};

class Paddle : public GameObject {
public:
    float speed = 600.0f;

    void onInit() override
    {
        groupId = static_cast<int>(Group::Player);
        _transform = get<Transform>();
    }

    void move(float dir, float dt)
    {
        _transform->position.x += dir * speed * dt;
    }

    Vector2 position() const
    {
        return _transform->position;
    }

    Vector2 size()
    {
        return get<RectShape>()->size;
    }

private:
    Transform* _transform = nullptr;
};

class Breakout {
public:
    virtual ~Breakout() = default;

    void init()
    {
        onBuildLevel();
        _world.init();
    }

    void update()
    {
        tick();
        _world.update(_delta_time);
        handle_input(_delta_time);
    }

    void render()
    {
        onRender();
    }

protected:
    World _world;

    Paddle* _paddle = nullptr;
    Ball* _ball = nullptr;

    float _current_tick = 0.0f;
    float _last_tick = 0.0f;
    float _delta_time = 0.0f;

    void tick()
    {
        _current_tick = ui_hal::get_tick_s();
        _delta_time = _current_tick - _last_tick;
        _last_tick = _current_tick;
    }

    void addWall(Vector2 pos, Vector2 size)
    {
        auto wall = _world.createObject(std::make_unique<GameObject>());
        wall->add(std::make_unique<Transform>(pos));
        wall->add(std::make_unique<RectShape>(size));
        wall->add(std::make_unique<Area>());
        wall->groupId = static_cast<int>(Group::Wall);
    }

    void addPaddle(Vector2 pos, Vector2 size, float speed)
    {
        auto paddle = _world.createObject(std::make_unique<Paddle>());
        paddle->add(std::make_unique<Transform>(pos));
        paddle->add(std::make_unique<RectShape>(size));
        paddle->add(std::make_unique<Area>());
        _paddle = static_cast<Paddle*>(paddle);
        _paddle->speed = speed;
    }

    void addBall(Vector2 pos, float radius)
    {
        auto ball = _world.createObject(std::make_unique<Ball>());
        ball->add(std::make_unique<Transform>(pos));
        ball->add(std::make_unique<CircleShape>(radius));
        ball->add(std::make_unique<Area>());
        _ball = static_cast<Ball*>(ball);
    }

    virtual void onBuildLevel()
    {
        // Walls
        addWall({6, 225}, {12, 450});
        addWall({794, 225}, {12, 450});
        addWall({400, 6}, {800, 12});

        // Paddle
        addPaddle({400, 420}, {100, 16}, 600);

        // Ball
        addBall({0, 0}, 8);

        setup_ball_collision();
    }
    virtual bool onReadAction(Action action) = 0;
    virtual void onRender() = 0;

    void handle_input(float dt)
    {
        float dir = 0.0f;
        if (onReadAction(Action::MoveLeft)) {
            dir -= 1.0f;
        }
        if (onReadAction(Action::MoveRight)) {
            dir += 1.0f;
        }

        _paddle->move(dir, dt);

        // Fire
        if (!_ball->active && onReadAction(Action::Fire)) {
            _ball->launch({0, -600});
        }

        // 跟随板子
        if (!_ball->active) {
            auto p = _paddle->position();
            _ball->get<Transform>()->position = {p.x, p.y - _ball->radius() - (_paddle->size().y / 2)};
        }
    }

    void setup_ball_collision()
    {
        auto* area = _ball->get<Area>();

        area->onEntered.connect([this](GameObject& other) {
            auto g = static_cast<Group>(other.groupId);

            if (g == Group::Wall) {
                reflect_from_wall(other);
            }

            if (g == Group::Player) {
                reflect_from_paddle(other);
            }
        });
    }

    void reflect_from_paddle(GameObject& paddle)
    {
        auto ballPos = _ball->get<Transform>()->position;
        auto padPos = paddle.get<Transform>()->position;
        auto padSize = paddle.get<RectShape>()->size;

        float hit = (ballPos.x - padPos.x) / (padSize.x * 0.5f);
        hit = std::clamp(hit, -1.0f, 1.0f);

        float speed = _ball->velocity.length();
        _ball->velocity = {hit * speed, -std::abs(_ball->velocity.y)};
    }

    void reflect_from_wall(GameObject& wall)
    {
        auto ballPos = _ball->get<Transform>()->position;

        auto wall_pos = wall.get<Transform>()->position;
        auto wall_size = wall.get<RectShape>()->size;

        float dx = ballPos.x - wall_pos.x;
        float dy = ballPos.y - wall_pos.y;

        float px = (wall_size.x * 0.5f) - std::abs(dx);
        float py = (wall_size.y * 0.5f) - std::abs(dy);

        if (px < py) {
            // 撞在左右边
            _ball->velocity.x *= -1;
        } else {
            // 撞在上下边
            _ball->velocity.y *= -1;
        }
    }
};
} // namespace smooth_ui_toolkit::games::breakout
