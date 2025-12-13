/**
 * @file slider.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-03-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "obj.hpp"
#include "utils/event/signal.hpp"
#include <lvgl.h>
#include <memory>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

/**
 * @brief Lvgl slider
 *
 */
class Slider : public Widget<lv_slider_create> {
public:
    using Widget::Widget;

    void setRange(int min, int max, bool autoCenterValue = true)
    {
        lv_slider_set_range(this->raw_ptr(), min, max);
        if (autoCenterValue) {
            setValue((max + min) / 2);
        }
    }

    int32_t getValue()
    {
        return lv_slider_get_value(this->raw_ptr());
    }

    void setValue(int32_t value)
    {
        lv_slider_set_value(this->raw_ptr(), value, LV_ANIM_ON);
    }

    /**
     * @brief On value changed signal
     *
     * @return Signal<int32_t>&
     */
    Signal<int32_t>& onValueChanged(void)
    {
        if (!_on_value_changed) {
            _on_value_changed = std::make_unique<Signal<int32_t>>();
            addEventCb(
                [](lv_event_t* e) {
                    auto on_value_changed = (Signal<int32_t>*)lv_event_get_user_data(e);
                    on_value_changed->emit(lv_slider_get_value((lv_obj_t*)lv_event_get_target(e)));
                },
                LV_EVENT_VALUE_CHANGED, _on_value_changed.get());
        }
        return *_on_value_changed;
    }

protected:
    std::unique_ptr<Signal<int32_t>> _on_value_changed;
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit