/**
 * @file roller.hpp
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
#include <string>
#include <vector>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

/**
 * @brief Lvgl roller
 *
 */
class Roller : public Widget<lv_roller_create> {
public:
    using Widget::Widget;

    void setOptions(const char* options, lv_roller_mode_t mode = LV_ROLLER_MODE_NORMAL)
    {
        lv_roller_set_options(this->raw_ptr(), options, mode);
    }

    void setOptions(const std::vector<std::string>& options, lv_roller_mode_t mode = LV_ROLLER_MODE_NORMAL)
    {
        _options_str.clear();
        for (int i = 0; i < options.size(); i++) {
            _options_str += options[i];
            if (i != options.size() - 1) {
                _options_str += "\n";
            }
        }
        setOptions(_options_str.c_str(), mode);
    }

    void setVisibleRowCount(uint32_t row_cnt)
    {
        lv_roller_set_visible_row_count(this->raw_ptr(), row_cnt);
    }

    void setSelected(uint32_t sel_opt, lv_anim_enable_t anim = LV_ANIM_OFF)
    {
        lv_roller_set_selected(this->raw_ptr(), sel_opt, anim);
    }

    uint32_t getSelected()
    {
        return lv_roller_get_selected(this->raw_ptr());
    }

    uint32_t getOptionCount()
    {
        return lv_roller_get_option_count(this->raw_ptr());
    }

    const char* getOptions()
    {
        return lv_roller_get_options(this->raw_ptr());
    }

    void getSelectedStrRaw(char* buf, uint32_t buf_size)
    {
        lv_roller_get_selected_str(this->raw_ptr(), buf, buf_size);
    }

    std::string getSelectedStr(size_t buf_size = 128)
    {
        char buf[buf_size];
        getSelectedStrRaw(buf, buf_size);
        return std::string(buf);
    }

    Signal<uint32_t>& onValueChanged(void)
    {
        if (!_on_value_changed) {
            _on_value_changed = std::make_unique<Signal<uint32_t>>();
            addEventCb(
                [](lv_event_t* e) {
                    auto on_value_changed = (Signal<uint32_t>*)lv_event_get_user_data(e);
                    on_value_changed->emit(lv_roller_get_selected((lv_obj_t*)lv_event_get_target(e)));
                },
                LV_EVENT_VALUE_CHANGED, _on_value_changed.get());
        }
        return *_on_value_changed;
    }

protected:
    std::string _options_str;
    std::unique_ptr<Signal<uint32_t>> _on_value_changed;
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit