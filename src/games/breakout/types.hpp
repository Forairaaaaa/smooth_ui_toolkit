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
#include <cstdint>
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

namespace collision_layer {

constexpr uint32_t Ball = 1u << 0;
constexpr uint32_t Wall = 1u << 1;
constexpr uint32_t Player = 1u << 2;
constexpr uint32_t Brick = 1u << 3;

} // namespace collision_layer

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
