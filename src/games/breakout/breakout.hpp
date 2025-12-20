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

class Brick : public GameObject {
public:
    int hp = 1;

    void onInit() override
    {
        groupId = static_cast<int>(Group::Brick);
        _area = get<Area>();
    }

    void damage(int v)
    {
        hp -= v;
        if (hp <= 0) {
            requestDestroy();
        }
    }

private:
    Area* _area = nullptr;
};

class Ball : public GameObject {
public:
    float speed = 0.0f;
    Vector2 direction;
    bool active = false;
    int damage = 1;

    void onInit() override
    {
        groupId = static_cast<int>(Group::Ball);
        _transform = get<Transform>();
        _shape = get<CircleShape>();

        setup_collision();
    }

    void onUpdate(float dt) override
    {
        if (!active) {
            return;
        }

        _transform->position += direction * speed * dt;
    }

    void launch(Vector2 dir)
    {
        direction = dir.normalized();
        active = true;
    }

    float radius()
    {
        return _shape->radius;
    }

private:
    Transform* _transform = nullptr;
    CircleShape* _shape = nullptr;

    void reflect_from_paddle(GameObject& paddle)
    {
        auto ball_pos = _transform->position;
        auto pad_os = paddle.get<Transform>()->position;
        auto pad_size = paddle.get<RectShape>()->size;

        float hit = (ball_pos.x - pad_os.x) / (pad_size.x * 0.5f);
        hit = std::clamp(hit, -1.0f, 1.0f);

        direction = {hit, -1.0f};
        direction = direction.normalized();
    }

    void reflect_from_wall(GameObject& wall)
    {
        auto ball_pos = _transform->position;
        auto wall_pos = wall.get<Transform>()->position;
        auto wall_size = wall.get<RectShape>()->size;

        float dx = ball_pos.x - wall_pos.x;
        float dy = ball_pos.y - wall_pos.y;

        float px = (wall_size.x * 0.5f + _shape->radius) - std::abs(dx);
        float py = (wall_size.y * 0.5f + _shape->radius) - std::abs(dy);

        if (px < py) {
            float sign = dx > 0 ? 1.0f : -1.0f;
            _transform->position.x += px * sign;
            direction.x *= -1;
        } else {
            float sign = dy > 0 ? 1.0f : -1.0f;
            _transform->position.y += py * sign;
            direction.y *= -1;
        }

        direction = direction.normalized();
    }

    void reflect_from_brick(GameObject& brick)
    {
        reflect_from_wall(brick);
        static_cast<Brick*>(&brick)->damage(damage);
    }

    void setup_collision()
    {
        auto* area = get<Area>();

        area->onEntered.connect([this](GameObject& other) {
            auto g = static_cast<Group>(other.groupId);

            if (g == Group::Wall) {
                reflect_from_wall(other);
            }

            if (g == Group::Player) {
                reflect_from_paddle(other);
            }

            if (g == Group::Brick) {
                reflect_from_brick(other);
            }
        });
    }
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

    virtual void onBuildLevel()
    {
        // Walls
        addWall({6, 225}, {12, 450});
        addWall({794, 225}, {12, 450});
        addWall({400, 6}, {800, 12});

        // Paddle
        addPaddle({400, 420}, {100, 16}, 600, {20, 800 - 20});

        // Ball
        addBall({0, 0}, 8, 600);

        // Bricks
        const int rows = 5;
        const int cols = 10;
        Vector2 brickSize = {60, 20};

        float startX = 400 - (cols * brickSize.x) * 0.5f + brickSize.x * 0.5f + 1;
        float startY = 60;

        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                Vector2 pos = {startX + x * brickSize.x, startY + y * brickSize.y};
                addBrick(pos, brickSize);
            }
        }
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
};

} // namespace smooth_ui_toolkit::games::breakout
