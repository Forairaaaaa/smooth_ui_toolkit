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
    int hp = 1;

    void onInit() override {}

    void damage(int v)
    {
        hp -= v;
        if (hp <= 0) {
            requestDestroy();
        }
    }
};

} // namespace smooth_ui_toolkit::games::breakout
