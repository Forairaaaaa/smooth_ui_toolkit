/**
 * @file bar.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2026-01-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <lvgl.h>

#if LV_USE_BAR

#include "obj.hpp"

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

/**
 * @brief Lvgl bar
 *
 */
class Bar : public Widget<lv_bar_create> {
public:
    using Widget::Widget;

    void setOrientation(lv_bar_orientation_t orientation)
    {
        lv_bar_set_orientation(this->raw_ptr(), orientation);
    }

    void setValue(int32_t value, lv_anim_enable_t anim = LV_ANIM_OFF)
    {
        lv_bar_set_value(this->raw_ptr(), value, anim);
    }

    void setRange(int32_t min, int32_t max)
    {
        lv_bar_set_range(this->raw_ptr(), min, max);
    }

    void setMode(lv_bar_mode_t mode)
    {
        lv_bar_set_mode(this->raw_ptr(), mode);
    }

    void setStartValue(int32_t start_value, lv_anim_enable_t anim = LV_ANIM_OFF)
    {
        lv_bar_set_start_value(this->raw_ptr(), start_value, anim);
    }
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit

#endif
