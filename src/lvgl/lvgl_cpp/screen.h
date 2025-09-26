/**
 * @file screen.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-09-26
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "obj.h"
#include <lvgl.h>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

/**
 * @brief Lvgl screen, obj with parent NULL
 *
 */
class Screen : public Widget<lv_obj_create> {
public:
    using Widget::Widget;

    Screen() : Widget(NULL) {}

    inline void load()
    {
        lv_screen_load(this->raw_ptr());
    }

    inline void loadAnim(lv_screen_load_anim_t anim_type, uint32_t time, uint32_t delay, bool auto_del)
    {
        lv_screen_load_anim(this->raw_ptr(), anim_type, time, delay, auto_del);
    }
};

/**
 * @brief Current active screen, lv_screen_active()
 *
 */
class ScreenActive : public Object {
public:
    ScreenActive()
    {
        this->lv_obj.reset(lv_screen_active());
    }

    ~ScreenActive() noexcept
    {
        this->lv_obj.release();
    }

    ScreenActive(const ScreenActive&) = delete;
    ScreenActive& operator=(const ScreenActive&) = delete;

    inline void load()
    {
        lv_screen_load(this->raw_ptr());
    }

    inline void loadAnim(lv_screen_load_anim_t anim_type, uint32_t time, uint32_t delay, bool auto_del)
    {
        lv_screen_load_anim(this->raw_ptr(), anim_type, time, delay, auto_del);
    }
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit
