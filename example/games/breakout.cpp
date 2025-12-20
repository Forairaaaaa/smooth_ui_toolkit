/**
 * @file breakout.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../utils/raylib_wrapper.hpp"
#include <uitk/short_namespace.hpp>
#include <games/games.hpp>
#include <mooncake_log.h>

using namespace uitk;
using namespace uitk::games;
using namespace uitk::games::breakout;

namespace smooth_ui_toolkit::games::breakout {

class BreakoutRaylib : public Breakout {
protected:
    // Define a simple level
    LevelDesc level1()
    {
        LevelDesc level;

        // Walls
        level.walls = {
            {{6, 225}, {12, 450}},
            {{794, 225}, {12, 450}},
            {{400, 6}, {800, 12}},
        };

        // Paddle
        level.paddle = {{400, 420}, {100, 16}, 600, {20, 800 - 20}};

        // Ball
        level.ball = {{0, 0}, 8, 600};

        // Bricks
        const int rows = 5;
        const int cols = 10;
        Vector2 brickSize = {60, 20};

        float startX = 400 - (cols * brickSize.x) * 0.5f + brickSize.x * 0.5f;
        float startY = 60;

        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                level.bricks.push_back({{startX + x * brickSize.x, startY + y * brickSize.y}, brickSize});
            }
        }

        level.screenHeight = 450.0f;
        level.lives = 3;

        return level;
    }

    // Build the level
    void onBuildLevel() override
    {
        loadLevel(level1());
    }

    // Handle user input
    bool onReadAction(Action action) override
    {
        switch (action) {
            case Action::MoveLeft:
                return IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
            case Action::MoveRight:
                return IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
            case Action::Fire:
                return IsKeyPressed(KEY_SPACE);
        }
        return false;
    }

    // Render the game objects
    void onRender() override
    {
        ClearBackground(WHITE);

        getWorld().forEachObject([](GameObject* obj) {
            auto group = static_cast<Group>(obj->groupId);

            if (group == Group::Wall || group == Group::Player) {
                auto p = obj->get<Transform>()->position;
                auto s = obj->get<RectShape>()->size;
                DrawRectangle(p.x - s.x / 2, p.y - s.y / 2, s.x, s.y, GRAY);
            }

            else if (group == Group::Ball) {
                auto p = obj->get<Transform>()->position;
                auto r = obj->get<CircleShape>()->radius;
                DrawCircle(p.x, p.y, r, RED);
            }

            else if (group == Group::Brick) {
                auto pos = obj->get<Transform>()->position;
                auto size = obj->get<RectShape>()->size;
                DrawRectangle(pos.x - size.x / 2, pos.y - size.y / 2, size.x, size.y, ORANGE);
            }
        });
    }

    void onGameOver() override
    {
        mclog::info("game over! rebuilding level...");
        resetGame();
    }
};

} // namespace smooth_ui_toolkit::games::breakout

int main()
{
    BreakoutRaylib game;
    game.init();

    raylib::create_window(800, 450, "你好", [&]() {
        game.update();
        // ui_hal::delay_s(1.0f / 30.0f);
    });
    return 0;
}
