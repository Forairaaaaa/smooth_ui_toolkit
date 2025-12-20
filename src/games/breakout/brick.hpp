/**
 * @file brick.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "types.hpp"
#include "games/core/core.h"

namespace smooth_ui_toolkit::games::breakout {

class Brick : public GameObject {
public:
    Brick(Vector2 pos, Vector2 size, int hp = 1)
    {
        groupId = static_cast<int>(Group::Brick);

        add(std::make_unique<Transform>(pos));
        add(std::make_unique<RectShape>(size));
        add(std::make_unique<Area>());

        this->hp = hp;
    }

    int hp;

    void onReady() override {}

    void damage(int v)
    {
        hp -= v;
        if (hp <= 0) {
            requestDestroy();
        }
    }
};

} // namespace smooth_ui_toolkit::games::breakout
