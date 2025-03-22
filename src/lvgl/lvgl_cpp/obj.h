/**
 * @file obj.h
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
    LvObject() = default;
    LvObject(lv_obj_t* parent)
    {
        _lv_obj = lv_obj_create(parent);
        lv_obj_null_on_delete(&_lv_obj);
    }

    virtual ~LvObject()
    {
        if (_lv_obj != NULL) {
            lv_obj_delete(_lv_obj);
        }
    }

    void set(lv_obj_t* obj)
    {
        _lv_obj = obj;
    }

    lv_obj_t* get()
    {
        return _lv_obj;
    }

    void setAlign(lv_align_t alignment)
    {
        lv_obj_set_align(_lv_obj, alignment);
    }

    void setOpa(lv_opa_t opa, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_opa(_lv_obj, opa, selector);
    }

    void setBgColor(lv_color_t color, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_bg_color(_lv_obj, color, selector);
    }

    void setBgOpa(lv_opa_t opa, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_bg_opa(_lv_obj, opa, selector);
    }

    void setPos(int32_t x, int32_t y)
    {
        lv_obj_set_pos(_lv_obj, x, y);
    }

    void setX(int32_t x)
    {
        lv_obj_set_x(_lv_obj, x);
    }

    void setY(int32_t y)
    {
        lv_obj_set_y(_lv_obj, y);
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
            addFlag(LV_OBJ_FLAG_HIDDEN);
        } else {
            removeFlag(LV_OBJ_FLAG_HIDDEN);
        }
    }

    void addFlag(lv_obj_flag_t flag)
    {
        lv_obj_add_flag(_lv_obj, flag);
    }

    void removeFlag(lv_obj_flag_t flag)
    {
        lv_obj_remove_flag(_lv_obj, flag);
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

    void setTextColor(lv_color_t color, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_text_color(_lv_obj, color, selector);
    }

    lv_color_t getTextColor(lv_style_selector_t selector = LV_PART_MAIN)
    {
        return lv_obj_get_style_text_color(_lv_obj, selector);
    }

    void setTextFont(const lv_font_t* font, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_text_font(_lv_obj, font, selector);
    }

    const lv_font_t* getTextFont(lv_style_selector_t selector = LV_PART_MAIN)
    {
        return lv_obj_get_style_text_font(_lv_obj, selector);
    }

    void setFlexFlow(lv_flex_flow_t flow)
    {
        lv_obj_set_flex_flow(_lv_obj, flow);
    }

    void setFlexAlign(lv_flex_align_t main_place, lv_flex_align_t cross_place, lv_flex_align_t track_cross_place)
    {
        lv_obj_set_flex_align(_lv_obj, main_place, cross_place, track_cross_place);
    }

    void setPadRow(int32_t value, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_pad_row(_lv_obj, value, selector);
    }

    void setPadColumn(int32_t value, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_pad_column(_lv_obj, value, selector);
    }

    void addEventCb(lv_event_cb_t event_cb, lv_event_code_t filter, void* user_data = nullptr)
    {
        lv_obj_add_event_cb(_lv_obj, event_cb, filter, user_data);
    }

    void onPressed(lv_event_cb_t event_cb, void* user_data = nullptr)
    {
        addEventCb(event_cb, LV_EVENT_PRESSED, user_data);
    }

    void onRelease(lv_event_cb_t event_cb, void* user_data = nullptr)
    {
        addEventCb(event_cb, LV_EVENT_RELEASED, user_data);
    }

    void onClick(lv_event_cb_t event_cb, void* user_data = nullptr)
    {
        addEventCb(event_cb, LV_EVENT_CLICKED, user_data);
    }

protected:
    lv_obj_t* _lv_obj = nullptr;
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit