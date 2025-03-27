/**
 * @file label.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "obj.h"
#include <lvgl.h>
#include <string>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

/**
 * @brief Lvgl label
 *
 */
class Label : public Widget<lv_label_create> {
public:
    using Widget::Widget;

    void setText(const std::string& text)
    {
        lv_label_set_text(this->raw_ptr(), text.c_str());
    }

    const char* getText()
    {
        return lv_label_get_text(this->raw_ptr());
    }

    void setLongMode(lv_label_long_mode_t mode)
    {
        lv_label_set_long_mode(this->raw_ptr(), mode);
    }
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit