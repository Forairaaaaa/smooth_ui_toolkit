/**
 * @file animate_color.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-04-04
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../utils/lvgl_wrapper.hpp"
#include <smooth_ui_toolkit.hpp>
#include <uitk/short_namespaces.hpp>
#include <smooth_lvgl.hpp>
#include <mooncake_log.h>
#include <random>

using namespace uitk;
using namespace uitk::lvgl_cpp;
using namespace uitk::color;

int main()
{
    lvgl::create_window(800, 520);

    std::vector<uint32_t> color_list = {0x9FB3DF, 0xD4C9BE, 0x9ACBD0, 0xF2EFE7, 0x8AB2A6, 0xACD3A8, 0xFFEDFA,
                                        0xB7B1F2, 0xEBE5C2, 0xB9B28A, 0xFFD95F, 0xA6F1E0, 0xFFEDFA, 0xEAFAEA,
                                        0xC8AAAA, 0x16C47F, 0xFAFFC5, 0xFF8383, 0xFFF574, 0xFCFFC1};

    // Color animation
    AnimateRgb_t bg_color;
    bg_color.duration = 0.3;
    bg_color.begin();
    bg_color = 0xffffff;

    // Color label
    auto label = Label(lv_screen_active());
    label.setAlign(LV_ALIGN_CENTER);
    label.setPos(0, -50);
    label.setTextFont(&lv_font_montserrat_24);
    label.setText("click me");

    // Switch color when label is clicked
    label.addFlag(LV_OBJ_FLAG_CLICKABLE);
    label.onClick().connect([&]() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, color_list.size() - 1);
        auto new_color = color_list[dis(gen)];
        label.setText(fmt::format("#{:06X}", new_color));
        bg_color = new_color;
    });

    while (1) {
        // Update color animation
        bg_color.update();

        // Apply color
        lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(bg_color.toHex()), LV_PART_MAIN);
        label.setTextColor(lv_color_hex(blend_in_difference(bg_color, 0xaaaaaa).toHex()));

        lvgl::update_window();
    }

    return 0;
}
