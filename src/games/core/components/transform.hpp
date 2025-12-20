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
#include "core/math/vector.hpp"
#include "component.hpp"

namespace smooth_ui_toolkit::games {

class Transform : public Component {
public:
    static constexpr ComponentType Type = ComponentType::Transform;
    Transform() : Component(Type) {}
    Transform(Vector2 position) : Component(Type), position(position) {}

    Vector2 position{0, 0};
};

} // namespace smooth_ui_toolkit::games
