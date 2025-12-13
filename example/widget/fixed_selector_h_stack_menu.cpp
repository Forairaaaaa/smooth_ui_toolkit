/**
 * @file fixed_selector_h_stack_menu.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-13
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../utils/raylib_wrapper.h"
#include <smooth_ui_toolkit.h>
#include <mooncake_log.h>

using namespace smooth_ui_toolkit;

static const smooth_ui_toolkit::Vector2 _screen_size = {320, 240};
static const smooth_ui_toolkit::Vector2 _option_size = {120, 120};
static const smooth_ui_toolkit::Vector2 _selector_pos = {100, 100};

class Menu : public SmoothSelectorMenu {
public:
    /**
     * @brief Setup menu
     *
     */
    void init()
    {
        // Camera is not needed in this senario normally

        // Quicker selector movement
        getSelectorPostion().x.springOptions().visualDuration = 0.4;
        getSelectorPostion().x.springOptions().bounce = 0.3;
        getSelectorPostion().y.springOptions() = getSelectorPostion().x.springOptions();
        getSelectorShape().x.springOptions() = getSelectorPostion().x.springOptions();
        getSelectorShape().y.springOptions() = getSelectorShape().x.springOptions();

        // Update in every frame is required by raylib
        setConfig().renderInterval = 0;
        setConfig().readInputInterval = 0;

        // Add dummy options in horizontal stack
        for (int i = 0; i < 6; i++) {
            addOption({{(float)i * 170, _selector_pos.y, _option_size.width, _option_size.height}, nullptr});
        }

        jumpTo(1);
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
        mclog::info("on click, target index: {}", getSelectedOptionIndex());
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

        // Press and release selector
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            // Squeeze selector
            // Use anchor_top_left to avoid position shift,
            // since options' redner offset is based on selector's postion
            auto pressed_keyframe = shape::scale<float>(getSelectorCurrentFrame(), anchor_top_left, {1.5, 0.5});
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

        // Calculate selector offset
        int selector_x_offset = -getSelectorPostion().x + _selector_pos.x;

        // Redner options
        // Apply selector offset to options' render position
        // so that options will move instead of selector
        int index = 0;
        for (auto& i : getOptionList()) {
            DrawRectangle(i.keyframe.x + selector_x_offset, i.keyframe.y, i.keyframe.width, i.keyframe.height, BLUE);
            DrawText(std::to_string(index).c_str(), i.keyframe.x + selector_x_offset + 5, i.keyframe.y, 20, WHITE);

            index++;
        }

        // Get the fixed selector shape
        smooth_ui_toolkit::Vector4 fixed_selector_kf = {
            _selector_pos.x, _selector_pos.y, getSelectorShape().x, getSelectorShape().y};
        // Convert shape anchor
        auto selector_render_kf = shape::convert_anchor(fixed_selector_kf, anchor_top_left, anchor_center);
        // Apply new anchor position offset
        selector_render_kf.x += _option_size.width / 2;
        selector_render_kf.y += _option_size.height / 2;
        // Render selector
        DrawRectangle(
            selector_render_kf.x, selector_render_kf.y, selector_render_kf.width, selector_render_kf.height, GREEN);

        // Render screen frame
        DrawRectangleLines(0, 0, _screen_size.width, _screen_size.height, RED);

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
