/**
 * @file slider.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-03-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "obj.h"
#include "label.h"
#include "utils/event/signal.h"
#include <memory>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

class LvSlider : public LvObject {
public:
    LvSlider(lv_obj_t* parent = nullptr)
    {
        _lv_obj = lv_slider_create(parent);
        lv_obj_null_on_delete(&_lv_obj);
    }

    virtual ~LvSlider(){};

    void setRange(int min, int max)
    {
        lv_slider_set_range(_lv_obj, min, max);
        lv_slider_set_value(_lv_obj, (max + min) / 2, LV_ANIM_ON);
    }

    int32_t getValue()
    {
        return lv_slider_get_value(_lv_obj);
    }

    void setValue(int32_t value)
    {
        lv_slider_set_value(_lv_obj, value, LV_ANIM_ON);
    }

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