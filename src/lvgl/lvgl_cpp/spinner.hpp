/**
 * @file spinner.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-04-19
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <lvgl.h>

#if LV_USE_SPINNER

#include "obj.hpp"

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

/**
 * @brief Lvgl spinner
 *
 */
class Spinner : public Widget<lv_spinner_create> {
public:
    using Widget::Widget;

    void setAnimParams(uint32_t t, uint32_t angle)
    {
        lv_spinner_set_anim_params(this->raw_ptr(), t, angle);
    }
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit

#endif
