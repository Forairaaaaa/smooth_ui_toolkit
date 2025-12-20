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
        _world.init();
        onBuildLevel();
    }

    void update()
    {
        if (_going_reset) {
            _going_reset = false;
            _world.clear();
            onBuildLevel();
            resetBall();
        }

        tick();
        _world.update(_frame_dt);
        handle_input(_frame_dt);
        check_ball_out_of_bounds();
        onRender();
    }

protected:
    virtual void onBuildLevel() = 0;
    virtual bool onReadAction(Action action) = 0;
    virtual void onRender() = 0;
    virtual void onGameOver() {}

    World& getWorld()
    {
        return _world;
    }

    int getLives() const
    {
        return _lives;
    }

    void addWall(Vector2 pos, Vector2 size)
    {
        auto wall = _world.createObject(std::make_unique<GameObject>());
        wall->groupId = static_cast<int>(Group::Wall);
        wall->add(std::make_unique<Transform>(pos));
        wall->add(std::make_unique<RectShape>(size));
        wall->add(std::make_unique<Area>());
    }

    void addPaddle(Vector2 pos, Vector2 size, float speed, Vector2 xLimits)
    {
        auto paddle = _world.createObject(std::make_unique<Paddle>(pos, size, speed, xLimits));
        _paddle = static_cast<Paddle*>(paddle);
    }

    void addBall(Vector2 pos, float radius, float speed)
    {
        auto ball = _world.createObject(std::make_unique<Ball>(pos, radius, speed));
        _ball = static_cast<Ball*>(ball);
    }

    void addBrick(Vector2 pos, Vector2 size)
    {
        _world.createObject(std::make_unique<Brick>(pos, size));
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

        _screen_height = level.screenHeight;
        _lives = level.lives;
    }

    void loseLife()
    {
        _lives--;

        if (_lives <= 0) {
            onGameOver();
        } else {
            resetBall();
        }
    }

    void resetBall()
    {
        _ball->active = false;
        _ball->direction = {0, 0};

        auto pad_pos = _paddle->position();
        float y = pad_pos.y - _ball->radius() - (_paddle->size().y * 0.5f);

        _ball->get<Transform>()->position = {pad_pos.x, y};

        _waiting_for_launch = true;
    }

    void resetGame()
    {
        _going_reset = true;
    }

protected:
    World _world;

    Paddle* _paddle = nullptr;
    Ball* _ball = nullptr;

    float _current_tick = 0.0f;
    float _last_tick = 0.0f;
    float _frame_dt = 0.0f;

    int _lives = 3;
    float _screen_height = 1000.0f;
    bool _waiting_for_launch = true;

    bool _going_reset = false;

    void tick()
    {
        _current_tick = ui_hal::get_tick_s();
        _frame_dt = _current_tick - _last_tick;
        _last_tick = _current_tick;
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
        if (_waiting_for_launch && onReadAction(Action::Fire)) {
            _ball->launch({0, -1});
            _waiting_for_launch = false;
        }

        // 跟随板子
        if (!_ball->active) {
            auto p = _paddle->position();
            _ball->get<Transform>()->position = {p.x, p.y - _ball->radius() - (_paddle->size().y / 2)};
        }
    }

    void check_ball_out_of_bounds()
    {
        if (!_ball || !_ball->active)
            return;

        float y = _ball->get<Transform>()->position.y;

        if (y > _screen_height) { // 屏幕底部
            _ball->active = false;
            loseLife();
        }
    }
};

} // namespace smooth_ui_toolkit::games::breakout
