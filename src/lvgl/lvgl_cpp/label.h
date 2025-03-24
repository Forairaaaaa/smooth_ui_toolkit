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

class LvLabel : public LvObject {
public:
    LvLabel() {};
    LvLabel(lv_obj_t* parent)
    {
        _lv_obj = lv_label_create(parent);
        lv_obj_null_on_delete(&_lv_obj);
    }

    virtual ~LvLabel() {};

    void setText(const char* text)
    {
        lv_label_set_text(_lv_obj, text);
    }

    void setText(const std::string& text)
    {
        lv_label_set_text(_lv_obj, text.c_str());
    }

    std::string getText()
    {
        return lv_label_get_text(_lv_obj);
    }
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit