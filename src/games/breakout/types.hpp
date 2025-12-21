/**
 * @file types.hpp
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
#include <vector>

namespace smooth_ui_toolkit::games::breakout {

enum class Action {
    MoveLeft,
    MoveRight,
    Fire,
};

enum class Group : int {
    Ball = 0,
    Wall,
    Player,
    Brick,
};

struct WallDesc {
    Vector2 pos;
    Vector2 size;
};

struct PaddleDesc {
    Vector2 pos;
    Vector2 size;
    float speed;
    Vector2 xLimits;
};

struct BallDesc {
    Vector2 pos;
    float radius;
    float speed;
};

struct BrickDesc {
    Vector2 pos;
    Vector2 size;
};

struct LevelDesc {
    std::vector<WallDesc> walls;
    std::vector<BrickDesc> bricks;
    PaddleDesc paddle;
    BallDesc ball;
    float screenHeight;
    int lives;
};

} // namespace smooth_ui_toolkit::games::breakout
