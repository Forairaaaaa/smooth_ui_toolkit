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

class LvButton : public LvObject {
public:
    LvButton() {};
    LvButton(lv_obj_t* parent)
    {
        _lv_obj = std::shared_ptr<lv_obj_t>(lv_button_create(parent), lv_obj_delete);
    }

    virtual ~LvButton() {};

    virtual void create(lv_obj_t* parent) override
    {
        _lv_obj = std::shared_ptr<lv_obj_t>(lv_button_create(parent), lv_obj_delete);
    }

    LvLabel& label()
    {
        if (!_label) {
            _label = std::make_shared<LvLabel>(_lv_obj.get());
        }
        return *_label;
    }

    void onClick(lv_event_cb_t event_cb, void* user_data = nullptr)
    {
        LvObject::onClick(event_cb, user_data);
    }

    /**
     * @brief On click signal
     *
     * @return Signal<void>&
     */
    Signal<void>& onClick(void)
    {
        if (!_on_click) {
            _on_click = std::make_shared<Signal<void>>();
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
    std::shared_ptr<LvLabel> _label;
    std::shared_ptr<Signal<void>> _on_click;
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit
