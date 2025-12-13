/**
 * @file fixed_selector_v_stack_curved_menu.cpp
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

static const smooth_ui_toolkit::Vector2 _screen_size = {320, 320};
static const smooth_ui_toolkit::Vector2 _option_size = {360, 28};
static const smooth_ui_toolkit::Vector2 _selector_pos = {16, _screen_size.height / 2 - _option_size.height / 2};

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

        // Add dummy options in vertical stack
        for (int i = 0; i < 12; i++) {
            addOption({{_selector_pos.x, (float)i * 46, _option_size.width, _option_size.height}, nullptr});
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
            auto pressed_keyframe = shape::scale<float>(getSelectorCurrentFrame(), anchor_top_left, {1.2, 0.5});
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
        int selector_y_offset = -getSelectorPostion().y + _selector_pos.y;

        // Redner options
        // Apply selector offset to options' render position
        // so that options will move instead of selector
        int index = 0;
        for (auto& i : getOptionList()) {
            auto curved_offset = get_curved_offset(i.keyframe.y - getSelectorPostion().y);

            DrawRectangle(i.keyframe.x + curved_offset,
                          i.keyframe.y + selector_y_offset,
                          i.keyframe.width,
                          i.keyframe.height,
                          SKYBLUE);
            DrawText(std::to_string(index).c_str(),
                     i.keyframe.x + curved_offset + 5,
                     i.keyframe.y + selector_y_offset,
                     20,
                     WHITE);

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
        DrawRectangleLines(
            selector_render_kf.x, selector_render_kf.y, selector_render_kf.width, selector_render_kf.height, RED);

        // // Render screen frame
        // DrawRectangleLines(0, 0, _screen_size.width, _screen_size.height, GREEN);

        // Render curve
        DrawCircleLines(200, _selector_pos.y + _option_size.height / 2, 200, LIGHTGRAY);

        // Instructions
        DrawText("Press A/D to navigate", 10, 10, 20, BLACK);
        DrawText("Click to select", 10, 35, 20, BLACK);
    }

private:
    int get_curved_offset(float deltaY)
    {
        const float radius = 200.0f;
        const float max_offset = 80.0f;
        const float eps = 0.0001f;

        // 1. clamp input
        float y = clamp(deltaY, -radius, radius);

        // 2. safe sqrt
        float inside = radius * radius - y * y;
        if (inside < eps) {
            inside = 0.0f;
        }

        float x = radius - sqrtf(inside);

        // 3. clamp output
        if (x > max_offset) {
            x = max_offset;
        }

        return (int)(x + 0.5f);
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
