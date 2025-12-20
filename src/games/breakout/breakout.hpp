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
#include "types.hpp"
#include "paddle.hpp"
#include "brick.hpp"
#include "ball.hpp"
#include "core/hal/hal.hpp"

namespace smooth_ui_toolkit::games::breakout {

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
        _world.update(_frame_dt);
        handle_input(_frame_dt);
        onRender();
    }

protected:
    virtual void onBuildLevel() = 0;
    virtual bool onReadAction(Action action) = 0;
    virtual void onRender() = 0;

    World _world;

    Paddle* _paddle = nullptr;
    Ball* _ball = nullptr;

    float _current_tick = 0.0f;
    float _last_tick = 0.0f;
    float _frame_dt = 0.0f;

    void tick()
    {
        _current_tick = ui_hal::get_tick_s();
        _frame_dt = _current_tick - _last_tick;
        _last_tick = _current_tick;
    }

    World& world()
    {
        return _world;
    }

    void addWall(Vector2 pos, Vector2 size)
    {
        auto wall = _world.createObject(std::make_unique<GameObject>());
        wall->add(std::make_unique<Transform>(pos));
        wall->add(std::make_unique<RectShape>(size));
        wall->add(std::make_unique<Area>());
        wall->groupId = static_cast<int>(Group::Wall);
    }

    void addPaddle(Vector2 pos, Vector2 size, float speed, Vector2 xLimits)
    {
        auto paddle = _world.createObject(std::make_unique<Paddle>());
        paddle->add(std::make_unique<Transform>(pos));
        paddle->add(std::make_unique<RectShape>(size));
        paddle->add(std::make_unique<Area>());
        _paddle = static_cast<Paddle*>(paddle);
        _paddle->speed = speed;
        _paddle->minX = xLimits.x;
        _paddle->maxX = xLimits.y;
    }

    void addBall(Vector2 pos, float radius, float speed)
    {
        auto ball = _world.createObject(std::make_unique<Ball>());
        ball->add(std::make_unique<Transform>(pos));
        ball->add(std::make_unique<CircleShape>(radius));
        ball->add(std::make_unique<Area>());
        _ball = static_cast<Ball*>(ball);
        _ball->speed = speed;
    }

    void addBrick(Vector2 pos, Vector2 size)
    {
        auto brick = _world.createObject(std::make_unique<Brick>());
        brick->add(std::make_unique<Transform>(pos));
        brick->add(std::make_unique<RectShape>(size));
        brick->add(std::make_unique<Area>());
    }

    void loadLevel(const LevelDesc& level)
    {
        for (const auto& w : level.walls) {
            addWall(w.pos, w.size);
        }

        addPaddle(level.paddle.pos, level.paddle.size, level.paddle.speed, level.paddle.xLimits);

        addBall(level.ball.pos, level.ball.radius, level.ball.speed);

        for (const auto& b : level.bricks) {
            addBrick(b.pos, b.size);
        }
    }

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
};

} // namespace smooth_ui_toolkit::games::breakout
