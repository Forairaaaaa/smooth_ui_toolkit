/**
 * @file area_system.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-20
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "area_system.hpp"
#include "games/core/components/shape.hpp"
#include "games/core/game_object.hpp"
#include "collision.hpp"

namespace smooth_ui_toolkit::games::engine {

void AreaSystem::update(const std::vector<GameObject*>& objects)
{
    // 1. 收集所有 Area
    std::vector<Area*> areas;
    for (auto* obj : objects) {
        if (auto* area = obj->get<Area>()) {
            areas.push_back(area);
        }
    }

    // 2. 两两检测
    for (size_t i = 0; i < areas.size(); ++i) {
        for (size_t j = i + 1; j < areas.size(); ++j) {
            test_pair(areas[i], areas[j]);
        }
    }
}

void AreaSystem::handlePreDestroy(ObjectPool<GameObject>& pool)
{
    pool.forEach([&](GameObject* obj, int) {
        if (obj->isDestroyRequested()) {
            if (auto* area = obj->get<Area>()) {
                for (auto* other : area->overlaps) {
                    area->onExited.emit(*other);
                }
                area->overlaps.clear();
            }
        }
    });
}

void AreaSystem::test_pair(Area* a, Area* b)
{
    auto* sa = a->owner->get<Shape>();
    auto* sb = b->owner->get<Shape>();
    if (!sa || !sb)
        return;

    bool colliding = collision::is_colliding(*sa, *sb);

    handle_overlap(a, b, colliding);
    handle_overlap(b, a, colliding);
}

void AreaSystem::handle_overlap(Area* self, Area* other, bool colliding)
{
    auto* otherObj = other->owner;

    if (colliding) {
        if (self->overlaps.insert(otherObj).second) {
            self->onEntered.emit(*otherObj);
        }
    } else {
        if (self->overlaps.erase(otherObj)) {
            self->onExited.emit(*otherObj);
        }
    }
}

} // namespace smooth_ui_toolkit::games::engine
