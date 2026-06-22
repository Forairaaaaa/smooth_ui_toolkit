/**
 * @file area.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-20
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "tools/event/signal.hpp"
#include "component.hpp"
#include <cstdint>
#include <unordered_set>

namespace smooth_ui_toolkit::games {

class Area : public Component {
public:
    static constexpr ComponentType Type = ComponentType::Area;
    static constexpr uint32_t DefaultCollisionLayer = 1u;
    static constexpr uint32_t AllCollisionLayers = 0xFFFFFFFFu;

    Area() : Component(Type) {}
    Area(uint32_t collisionLayer, uint32_t collisionMask = AllCollisionLayers)
        : Component(Type), collisionLayer(collisionLayer), collisionMask(collisionMask)
    {
    }

    Signal<GameObject&> onEntered;
    Signal<GameObject&> onExited;

    uint32_t collisionLayer = DefaultCollisionLayer;
    uint32_t collisionMask = AllCollisionLayers;

    bool monitors(const Area& other) const
    {
        return (collisionMask & other.collisionLayer) != 0;
    }

    // 当前帧检测到的对象
    std::unordered_set<GameObject*> overlaps;
};

} // namespace smooth_ui_toolkit::games
