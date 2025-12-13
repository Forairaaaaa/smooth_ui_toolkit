/**
 * @file smooth_selector_menu.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-08-16
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../utils/raylib_wrapper.hpp"
#include <smooth_ui_toolkit.hpp>
#include <uitk/short_namespace.hpp>
#include <mooncake_log.h>

using namespace uitk;

class Menu : public SmoothSelectorMenu {
public:
    /**
     * @brief Setup menu
     *
     */
    void init()
    {
        setCameraSize(300, 260);

        // Quicker selector movement
        getSelectorPostion().x.springOptions().visualDuration = 0.4;
        getSelectorPostion().x.springOptions().bounce = 0.3;
        getSelectorPostion().y.springOptions() = getSelectorPostion().x.springOptions();

        // A bit slower selector reshaping
        getSelectorShape().x.springOptions().visualDuration = 0.5;
        getSelectorShape().x.springOptions().bounce = 0.3;
        getSelectorShape().y.springOptions() = getSelectorShape().x.springOptions();

        // Slower camera movement
        getCamera().x.springOptions().visualDuration = 0.8;
        getCamera().y.springOptions() = getCamera().x.springOptions();

        // Update in every frame is required by raylib
        setConfig().renderInterval = 0;
        setConfig().readInputInterval = 0;

        // Add dummy options
        addOption({{50, 60, 120, 40}, nullptr});
        addOption({{200, 80, 80, 120}, nullptr});
        addOption({{320, 20, 150, 40}, nullptr});
        addOption({{50, 320, 160, 80}, nullptr});
        addOption({{400, 220, 100, 80}, nullptr});
        addOption({{600, 120, 120, 140}, nullptr});
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
            auto pressed_keyframe = shape::scale<float>(getSelectorCurrentFrame(), shape::Anchor::Center, {1.6, 0.5});
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

        // Redner options
        int index = 0;
        for (auto& i : getOptionList()) {
            DrawRectangle(i.keyframe.x, i.keyframe.y, i.keyframe.width, i.keyframe.height, BLUE);
            DrawText(std::to_string(index).c_str(), i.keyframe.x + 5, i.keyframe.y, 20, WHITE);

            index++;
        }

        // Render selector
        DrawRectangle(getSelectorCurrentFrame().x,
                      getSelectorCurrentFrame().y,
                      getSelectorCurrentFrame().width,
                      getSelectorCurrentFrame().height,
                      GREEN);

        // Render camera
        DrawRectangleLines(
            getCameraOffset().x, getCameraOffset().y, getCameraSize().width, getCameraSize().height, BLACK);

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