/**
 * @file switch.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <lvgl.h>

#if LV_USE_SWITCH

#include "obj.hpp"
#include "tools/event/signal.hpp"
#include <memory>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

/**
 * @brief Lvgl switch
 *
 */
class Switch : public Widget<lv_switch_create> {
public:
    using Widget::Widget;

    void setValue(bool value)
    {
        if (value) {
            addState(LV_STATE_CHECKED);
        } else {
            removeState(LV_STATE_CHECKED);
        }
    }

    bool getValue()
    {
        return lv_obj_has_state(this->raw_ptr(), LV_STATE_CHECKED);
    }

    Signal<bool>& onValueChanged(void)
    {
        if (!_on_value_changed) {
            _on_value_changed = std::make_unique<Signal<bool>>();
            addEventCb(
                [](lv_event_t* e) {
                    auto on_value_changed = (Signal<bool>*)lv_event_get_user_data(e);
                    on_value_changed->emit(lv_obj_has_state((lv_obj_t*)lv_event_get_target(e), LV_STATE_CHECKED));
                },
                LV_EVENT_VALUE_CHANGED,
                _on_value_changed.get());
        }
        return *_on_value_changed;
    }

protected:
    std::unique_ptr<Signal<bool>> _on_value_changed;
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit

#endif
