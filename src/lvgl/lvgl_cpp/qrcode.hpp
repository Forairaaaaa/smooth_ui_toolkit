/**
 * @file qrcode.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-30
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <lvgl.h>

#if LV_USE_QRCODE

#include "obj.hpp"
#include <string_view>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

/**
 * @brief Lvgl spinner
 *
 */
class Qrcode : public Widget<lv_qrcode_create> {
public:
    using Widget::Widget;

    void setSize(int32_t size)
    {
        lv_qrcode_set_size(this->raw_ptr(), size);
    }

    void setDarkColor(lv_color_t color)
    {
        lv_qrcode_set_dark_color(this->raw_ptr(), color);
    }

    void setLightColor(lv_color_t color)
    {
        lv_qrcode_set_light_color(this->raw_ptr(), color);
    }

    lv_result_t update(std::string_view data)
    {
        return lv_qrcode_update(this->raw_ptr(), data.data(), data.size());
    }

    void setData(std::string_view data)
    {
        lv_qrcode_set_data(this->raw_ptr(), data.data());
    }

    void setQuietZone(bool enable)
    {
        lv_qrcode_set_quiet_zone(this->raw_ptr(), enable);
    }
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit

#endif
