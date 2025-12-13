/**
 * @file image.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-04-13
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "obj.hpp"
#include <lvgl.h>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

/**
 * @brief Lvgl image
 *
 */
class Image : public Widget<lv_image_create> {
public:
    using Widget::Widget;

    void setSrc(const void* src)
    {
        lv_image_set_src(this->raw_ptr(), src);
    }

    void setPivot(int32_t x, int32_t y)
    {
        lv_image_set_pivot(this->raw_ptr(), x, y);
    }

    void setRotation(int32_t angle)
    {
        lv_image_set_rotation(this->raw_ptr(), angle);
    }

    void setScale(uint32_t zoom)
    {
        lv_image_set_scale(this->raw_ptr(), zoom);
    }

    void setScaleX(uint32_t zoom)
    {
        lv_image_set_scale_x(this->raw_ptr(), zoom);
    }

    void setScaleY(uint32_t zoom)
    {
        lv_image_set_scale_y(this->raw_ptr(), zoom);
    }
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit