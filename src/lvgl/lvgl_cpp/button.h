/**
 * @file button.h
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
#include "label.h"
#include "utils/event/signal.h"
#include <memory>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

/**
 * @brief Lvgl button
 *
 */
class Button : public Widget<lv_button_create> {
public:
    using Widget::Widget;

    Label& label()
    {
        if (!_label) {
            _label = std::make_unique<Label>(this->raw_ptr());
        }
        return *_label;
    }

    void onClick(lv_event_cb_t event_cb, void* user_data = nullptr)
    {
        Object::onClick(event_cb, user_data);
    }

    /**
     * @brief On click signal
     *
     * @return Signal<void>&
     */
    Signal<void>& onClick(void)
    {
        if (!_on_click) {
            _on_click = std::make_unique<Signal<void>>();
            addEventCb(
                [](lv_event_t* e) {
                    auto on_click = (Signal<void>*)lv_event_get_user_data(e);
                    on_click->emit();
                },
                LV_EVENT_CLICKED, _on_click.get());
        }
        return *_on_click;
    }

protected:
    std::unique_ptr<Label> _label;
    std::unique_ptr<Signal<void>> _on_click;
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit
