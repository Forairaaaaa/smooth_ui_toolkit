/**
 * @file area_system.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-20
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "games/core/components/area.hpp"
#include "tools/object_pool/object_pool.hpp"

namespace smooth_ui_toolkit::games {

class AreaSystem {
public:
    void update(const std::vector<GameObject*>& objects);
    void handlePreDestroy(ObjectPool<GameObject>& pool);

private:
    void test_pair(Area* a, Area* b);
    void handle_overlap(Area* self, Area* other, bool colliding);
};

} // namespace smooth_ui_toolkit::games
