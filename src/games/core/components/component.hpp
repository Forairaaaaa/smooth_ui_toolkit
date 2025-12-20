/**
 * @file game_object.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-20
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <cstdint>

namespace smooth_ui_toolkit::games::engine {

class GameObject;

enum class ComponentType : uint8_t { Transform = 0, Shape = 1, Area = 2 };

class Component {
public:
    virtual ~Component() = default;

    ComponentType type() const
    {
        return _type;
    }

    GameObject* owner = nullptr;

    virtual void update(float dt) {}

protected:
    explicit Component(ComponentType type) : _type(type) {}
    ComponentType _type;
};

} // namespace smooth_ui_toolkit::games::engine
