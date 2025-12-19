/**
 * @file calendar.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-04-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "obj.hpp"
#include "tools/event/signal.hpp"
#include <lvgl.h>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

/**
 * @brief Lvgl calendar
 *
 */
class Calendar : public Widget<lv_calendar_create> {
public:
    using Widget::Widget;

    void setTodayDate(uint32_t year, uint32_t month, uint32_t day)
    {
        lv_calendar_set_today_date(this->raw_ptr(), year, month, day);
    }

    void setShowedDate(uint32_t year, uint32_t month)
    {
        lv_calendar_set_showed_date(this->raw_ptr(), year, month);
    }

    const lv_calendar_date_t* getTodayDate()
    {
        return lv_calendar_get_today_date(this->raw_ptr());
    }

    const lv_calendar_date_t* getShowedDate()
    {
        return lv_calendar_get_showed_date(this->raw_ptr());
    }

    lv_obj_t* headerArrowCreate()
    {
        return lv_calendar_header_arrow_create(this->raw_ptr());
    }

    lv_obj_t* headerDropdownCreate()
    {
        return lv_calendar_header_dropdown_create(this->raw_ptr());
    }

    Signal<lv_calendar_date_t>& onValueChanged(void)
    {
        if (!_on_value_changed) {
            _on_value_changed = std::make_unique<Signal<lv_calendar_date_t>>();
            addEventCb(
                [](lv_event_t* e) {
                    auto on_value_changed = (Signal<lv_calendar_date_t>*)lv_event_get_user_data(e);
                    lv_calendar_date_t date;
                    if (lv_calendar_get_pressed_date((lv_obj_t*)lv_event_get_current_target(e), &date)) {
                        on_value_changed->emit(date);
                    }
                },
                LV_EVENT_VALUE_CHANGED, _on_value_changed.get());
        }
        return *_on_value_changed;
    }

protected:
    std::unique_ptr<Signal<lv_calendar_date_t>> _on_value_changed;
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit