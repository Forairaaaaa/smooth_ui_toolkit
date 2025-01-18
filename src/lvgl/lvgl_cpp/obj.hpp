/**
 * @file obj.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <lvgl.h>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

class LvObject {
public:
    LvObject(lv_obj_t* parent = nullptr)
    {
        if (parent) {
            _lv_obj = lv_obj_create(parent);
        } else {
            _lv_obj = lv_obj_create(lv_screen_active());
        }
        lv_obj_null_on_delete(&_lv_obj);
    }

    virtual ~LvObject()
    {
        if (_lv_obj != NULL) {
            lv_obj_delete(_lv_obj);
        }
    }

    lv_obj_t* get()
    {
        return _lv_obj;
    }

    void setAlign(lv_align_t alignment)
    {
        lv_obj_set_align(_lv_obj, alignment);
    }

    void setBgColor(lv_color_t color, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_bg_color(_lv_obj, color, selector);
    }

    void setPos(int32_t x, int32_t y)
    {
        lv_obj_set_pos(_lv_obj, x, y);
    }

    void setSize(int32_t w, int32_t h)
    {
        lv_obj_set_size(_lv_obj, w, h);
    }

    void setRadius(int32_t value, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_radius(_lv_obj, value, selector);
    }

    void setBorderWidth(int32_t value, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_border_width(_lv_obj, value, selector);
    }

    void setBorderColor(lv_color_t color, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_border_color(_lv_obj, color, selector);
    }

    void setRotation(int32_t value, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_transform_rotation(_lv_obj, value, selector);
    }

    void setScrollbarMode(lv_scrollbar_mode_t mode)
    {
        lv_obj_set_scrollbar_mode(_lv_obj, mode);
    }

    void setPadding(int32_t top,
                    int32_t bottom,
                    int32_t left,
                    int32_t right,
                    lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_pad_top(_lv_obj, top, selector);
        lv_obj_set_style_pad_bottom(_lv_obj, bottom, selector);
        lv_obj_set_style_pad_left(_lv_obj, left, selector);
        lv_obj_set_style_pad_right(_lv_obj, right, selector);
    }

    void setOutlineWidth(int32_t value, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_outline_width(_lv_obj, value, selector);
    }

    void setOutlineColor(lv_color_t color, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_outline_color(_lv_obj, color, selector);
    }

    void moveBackground()
    {
        lv_obj_move_background(_lv_obj);
    }

    void moveForeground()
    {
        lv_obj_move_foreground(_lv_obj);
    }

    void hidden(bool hidden)
    {
        if (hidden) {
            lv_obj_add_flag(_lv_obj, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_remove_flag(_lv_obj, LV_OBJ_FLAG_HIDDEN);
        }
    }

    int32_t getX()
    {
        lv_obj_update_layout(_lv_obj);
        return lv_obj_get_x(_lv_obj);
    }

    int32_t getX2()
    {
        lv_obj_update_layout(_lv_obj);
        return lv_obj_get_x2(_lv_obj);
    }

    int32_t getY()
    {
        lv_obj_update_layout(_lv_obj);
        return lv_obj_get_y(_lv_obj);
    }

    int32_t getY2()
    {
        lv_obj_update_layout(_lv_obj);
        return lv_obj_get_y2(_lv_obj);
    }

    int32_t getWidth()
    {
        lv_obj_update_layout(_lv_obj);
        return lv_obj_get_width(_lv_obj);
    }

    int32_t getHeight()
    {
        lv_obj_update_layout(_lv_obj);
        return lv_obj_get_height(_lv_obj);
    }

private:
    lv_obj_t* _lv_obj = nullptr;
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit