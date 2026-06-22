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
#include "games/core/components/rigidbody.hpp"
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

namespace collision_layer {

constexpr uint32_t Wall = 1u << 0;
constexpr uint32_t Logo = 1u << 1;

} // namespace collision_layer

class Logo : public GameObject {
public:
    Logo(int groupId, Vector2 pos, Vector2 size, Vector2 direction, float speed)
    {
        const Vector2 initial_direction = direction.normalized();

        add(std::make_unique<Transform>(pos));
        add(std::make_unique<RectShape>(size));
        add(std::make_unique<Area>(collision_layer::Logo, collision_layer::Wall | collision_layer::Logo));
        add(std::make_unique<Rigidbody>(initial_direction * speed));

        this->groupId = groupId;
        this->speed = speed;
        this->direction = initial_direction;
    }

    float speed;
    Vector2 direction;

    void onReady() override
    {
        setup_collision();
    }

private:
    void reflect_from_body(GameObject& body)
    {
        auto transform = get<Transform>();
        auto logo_pos = transform->position;
        auto logo_size = get<RectShape>()->size;
        auto body_pos = body.get<Transform>()->position;
        auto body_size = body.get<RectShape>()->size;

        float dx = logo_pos.x - body_pos.x;
        float dy = logo_pos.y - body_pos.y;

        float px = (body_size.x * 0.5f + logo_size.x * 0.5f) - std::abs(dx);
        float py = (body_size.y * 0.5f + logo_size.y * 0.5f) - std::abs(dy);

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

    void setup_collision()
    {
        auto area = get<Area>();
        area->onEntered.connect([this](GameObject& other) {
            reflect_from_body(other);
        });
    }

    void sync_rigidbody()
    {
        auto* rigidbody = get<Rigidbody>();
        if (!rigidbody) {
            return;
        }

        rigidbody->velocity = direction * speed;
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
    virtual void onLogoCollide(int logoGroupId) {}

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
        wall->add(std::make_unique<Area>(collision_layer::Wall, 0u));
    }

    void addLogo(int groupId, Vector2 pos, Vector2 size, Vector2 direction, float speed)
    {
        auto logo = _world.createObject(std::make_unique<Logo>(groupId, pos, size, direction, speed));
        const auto logo_id = logo->groupId;
        logo->get<Area>()->onEntered.connect([this, logo_id](GameObject& other) {
            onLogoCollide(logo_id);
        });
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
