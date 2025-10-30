/**
 * @file smooth_options_menu.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-08-16
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../utils/raylib_wrapper.h"
#include "raylib.h"
#include <smooth_ui_toolkit.h>
#include <mooncake_log.h>
#include <cmath>

using namespace smooth_ui_toolkit;

class Menu : public SmoothOptionsMenu {
public:
    /**
     * @brief Setup menu
     *
     */
    void init()
    {
        // Must update in every frame on raylib
        setConfig().renderInterval = 0;
        setConfig().readInputInterval = 0;

        // Add 5 options
        for (int i = 0; i < 5; i++) {
            addOption(nullptr);
        }

        // Configure animation for all options
        for (auto& option : setOptionList()) {
            // Position animation - smooth and bouncy
            option.position.x.springOptions().visualDuration = 0.5;
            option.position.x.springOptions().bounce = 0.4;
            option.position.y.springOptions() = option.position.x.springOptions();

            // Shape animation - slightly slower
            option.shape.x.springOptions().visualDuration = 0.6;
            option.shape.x.springOptions().bounce = 0.3;
            option.shape.y.springOptions() = option.shape.x.springOptions();
        }

        // Setup circular keyframe positions
        float centerX = 400;
        float centerY = 225;
        float radius = 150;

        for (int i = 0; i < 5; i++) {
            float angle = (i * 2.0f * M_PI / 5.0f) - M_PI / 2; // Start from top
            float x = centerX + radius * std::cos(angle);
            float y = centerY + radius * std::sin(angle);

            // First keyframe (top) is larger
            if (i == 0) {
                setKeyframe(i, {x - 60, y - 30, 120, 60});
            } else {
                setKeyframe(i, {x - 40, y - 20, 80, 40});
            }
        }

        // Initialize to first keyframe
        jumpTo(0);
    }

    void onGoLast() override
    {
        mclog::info("go last");
    }

    void onGoNext() override
    {
        mclog::info("go next");
    }

    void onPress() override
    {
        mclog::info("on press");
    }

    void onRelease() override
    {
        mclog::info("on release");
    }

    void onClick() override
    {
        mclog::info("on click, selected index: {}", getSelectedOptionIndex());
    }

    /**
     * @brief Update input and make action
     *
     */
    void onReadInput() override
    {
        // Switch between options
        if (IsKeyPressed(KEY_A)) {
            goLast();
        } else if (IsKeyPressed(KEY_D)) {
            goNext();
        }

        // Press and release selected option
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            // Squeeze the selected option
            auto& selected = getSelectedOption();
            auto current_frame = getOptionCurrentFrame(getMatchingOptionIndex(0));
            auto pressed_keyframe = shape::scale<float>(current_frame, anchor_center, {1.3, 0.6});
            press(pressed_keyframe);
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            release();
        }
    }

    /**
     * @brief Render menu base on all the keyframes
     *
     */
    void onRender() override
    {
        // Clear
        ClearBackground(WHITE);

        // Draw center point
        DrawCircle(400, 225, 5, GRAY);

        // Render each option with different colors
        Color colors[] = {RED, ORANGE, VIOLET, GREEN, BLUE};

        for (int i = 0; i < getKeyframeList().size(); i++) {
            int option_index = getMatchingOptionIndex(i);
            auto frame = getOptionCurrentFrame(option_index);

            DrawRectangle(frame.x, frame.y, frame.width, frame.height, colors[option_index]);
            DrawText(std::to_string(option_index).c_str(), frame.x + 5, frame.y, 20, WHITE);
        }

        // Draw keyframe positions (for debugging)
        for (int i = 0; i < getKeyframeList().size(); i++) {
            auto kf = getKeyframe(i);
            DrawRectangleLines(kf.x, kf.y, kf.width, kf.height, LIGHTGRAY);
        }

        // Instructions
        DrawText("Press A/D to navigate", 10, 10, 20, BLACK);
        DrawText("Click to select", 10, 35, 20, BLACK);
    }
};

int main()
{
    Menu menu;
    menu.init();

    raylib::create_window(800, 450, "你好", [&]() {
        menu.update();
    });

    return 0;
}
