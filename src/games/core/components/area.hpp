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
#include <unordered_set>

namespace smooth_ui_toolkit::games::engine {

class Area : public Component {
public:
    static constexpr ComponentType Type = ComponentType::Area;

    Area() : Component(Type) {}

    Signal<GameObject&> onEntered;
    Signal<GameObject&> onExited;

    // 当前帧检测到的对象
    std::unordered_set<GameObject*> overlaps;
};

} // namespace smooth_ui_toolkit::games::engine
