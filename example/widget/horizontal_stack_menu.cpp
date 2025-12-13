/**
 * @file horizontal_stack_menu.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-13
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../utils/raylib_wrapper.hpp"
#include <smooth_ui_toolkit.hpp>
#include <mooncake_log.h>

using namespace smooth_ui_toolkit;

static const Vector2i _screen_size = {320, 240};

class Menu : public SmoothSelectorMenu {
public:
    /**
     * @brief Setup menu
     *
     */
    void init()
    {
        // Set camera to screen size
        setCameraSize(_screen_size.width, _screen_size.height);

        // Quicker selector movement
        getSelectorPostion().x.springOptions().visualDuration = 0.4;
        getSelectorPostion().x.springOptions().bounce = 0.3;
        getSelectorPostion().y.springOptions() = getSelectorPostion().x.springOptions();
        getSelectorShape().x.springOptions() = getSelectorPostion().x.springOptions();
        getSelectorShape().y.springOptions() = getSelectorShape().x.springOptions();

        // Slower camera movement
        getCamera().x.springOptions().visualDuration = 0.8;
        getCamera().y.springOptions() = getCamera().x.springOptions();

        // Update in every frame is required by raylib
        setConfig().renderInterval = 0;
        setConfig().readInputInterval = 0;

        // Add dummy options in horizontal stack
        for (int i = 0; i < 6; i++) {
            addOption({{(float)i * 100, 100, 72, 72}, nullptr});
        }
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
            auto pressed_keyframe = shape::scale<float>(getSelectorCurrentFrame(), anchor_center, {1.5, 0.5});
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

        // A camera offset for options and selector to apply
        // To keep their render position inside of the screen size
        int camera_x_offset = -getCameraOffset().x;

        // // You can disable this offset and enable render camera section below to see how camera works
        // camera_x_offset = 0;

        // Redner options
        int index = 0;
        for (auto& i : getOptionList()) {
            DrawRectangle(i.keyframe.x + camera_x_offset, i.keyframe.y, i.keyframe.width, i.keyframe.height, BLUE);
            DrawText(std::to_string(index).c_str(), i.keyframe.x + camera_x_offset + 5, i.keyframe.y, 20, WHITE);

            index++;
        }

        // Render selector
        DrawRectangle(getSelectorCurrentFrame().x + camera_x_offset,
                      getSelectorCurrentFrame().y,
                      getSelectorCurrentFrame().width,
                      getSelectorCurrentFrame().height,
                      GREEN);

        // // Render camera
        // DrawRectangleLines(
        //     getCameraOffset().x, getCameraOffset().y, getCameraSize().width, getCameraSize().height, LIGHTGRAY);

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
