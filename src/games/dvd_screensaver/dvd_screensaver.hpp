/**
 * @file dvd_screensaver.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "core/math/vector.hpp"
#include "games/core/components/shape.hpp"
#include "games/core/components/transform.hpp"
#include "games/core/world.hpp"
#include "games/core/frame_clock.hpp"
#include "tools/random/random.hpp"
#include <memory>

namespace smooth_ui_toolkit::games::dvd_screensaver {

enum class Group : int {
    Wall = -1,
    // Use any id but wall as a user defined group
};

class Logo : public GameObject {
public:
    Logo(int groupId, Vector2 pos, Vector2 size, Vector2 direction, float speed)
    {
        add(std::make_unique<Transform>(pos));
        add(std::make_unique<RectShape>(size));
        add(std::make_unique<Area>());

        this->groupId = groupId;
        this->speed = speed;
        this->direction = direction;
    }

    float speed;
    Vector2 direction;

    void onReady() override
    {
        setup_collision();
    }

    void onUpdate(float dt) override
    {
        auto transform = get<Transform>();
        transform->position += direction * speed * dt;
    }

private:
    void reflect_from_wall(GameObject& wall)
    {
        auto transform = get<Transform>();
        auto logo_pos = transform->position;
        auto logo_size = get<RectShape>()->size;
        auto wall_pos = wall.get<Transform>()->position;
        auto wall_size = wall.get<RectShape>()->size;

        float dx = logo_pos.x - wall_pos.x;
        float dy = logo_pos.y - wall_pos.y;

        float px = (wall_size.x * 0.5f + logo_size.x * 0.5f) - std::abs(dx);
        float py = (wall_size.y * 0.5f + logo_size.y * 0.5f) - std::abs(dy);

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
    }

    void setup_collision()
    {
        auto area = get<Area>();
        area->onEntered.connect([this](GameObject& other) {
            reflect_from_wall(other);
        });
    }
};

class DvdScreensaver {
public:
    virtual ~DvdScreensaver() = default;

    void init()
    {
        _world.init();
        onBuildLevel();
        onInit();
        _clock.tick();
    }

    void update()
    {
        _clock.tick();
        _world.update(_clock.dt());
        onRender(_clock.dt());
    }

protected:
    virtual void onBuildLevel() = 0;
    virtual void onInit() {}
    virtual void onRender(float dt) = 0;

    World& getWorld()
    {
        return _world;
    }

    void addWall(Vector2 pos, Vector2 size)
    {
        auto wall = _world.createObject(std::make_unique<GameObject>());
        wall->groupId = static_cast<int>(Group::Wall);
        wall->add(std::make_unique<Transform>(pos));
        wall->add(std::make_unique<RectShape>(size));
        wall->add(std::make_unique<Area>());
    }

    void addLogo(int groupId, Vector2 pos, Vector2 size, Vector2 direction, float speed)
    {
        _world.createObject(std::make_unique<Logo>(groupId, pos, size, direction, speed));
    }

    void addScreenFrameAsWall(Vector2 screenSize)
    {
        addWall({screenSize.width / 2, 0}, {screenSize.width, 1});
        addWall({screenSize.width / 2, screenSize.height}, {screenSize.width, 1});
        addWall({0, screenSize.height / 2}, {1, screenSize.height});
        addWall({screenSize.width, screenSize.height / 2}, {1, screenSize.height});
    }

    void addRandomLogo(int groupId, Vector2 screenSize, Vector2 size)
    {
        auto& random = Random::getInstance();

        Vector2 pos = {random.getFloat(50.0f, screenSize.width - 50.0f),
                       random.getFloat(30.0f, screenSize.height - 30.0f)};

        Vector2 direction = {random.getFloat(-1.0f, 1.0f), random.getFloat(-1.0f, 1.0f)};
        direction = direction.normalized();

        float speed = random.getFloat(100.0f, 300.0f);

        addLogo(groupId, pos, size, direction, speed);
    }

protected:
    World _world;
    FrameClock _clock;
};

} // namespace smooth_ui_toolkit::games::dvd_screensaver
