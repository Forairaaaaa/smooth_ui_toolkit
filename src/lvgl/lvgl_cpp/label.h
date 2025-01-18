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

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

class LvLabel : public LvObject {
public:
    LvLabel(lv_obj_t* parent = nullptr)
    {
        _lv_obj = lv_label_create(parent);
        lv_obj_null_on_delete(&_lv_obj);
    }

    virtual ~LvLabel(){};

    void setText(const char* text)
    {
        lv_label_set_text(_lv_obj, text);
    }

    void setTextColor(lv_color_t color, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_text_color(_lv_obj, color, selector);
    }

    void setFont(const lv_font_t* font, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_text_font(_lv_obj, font, selector);
    }
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit