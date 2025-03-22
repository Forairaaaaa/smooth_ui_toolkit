/**
 * @file dev_zone.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <cstddef>
#include <cstdint>
#include <memory>
#include <mutex>
#include <smooth_ui_toolkit.h>
#include <mooncake_log.h>
#include "animation/animate/animate.h"
#include "animation/animate_value/animate_value.h"
#include "lvgl/lvgl_cpp/obj.h"
#include "utils/raylib_wrapper.h"
#include "utils/lvgl_wrapper.h"
#include <lvgl/lvgl_cpp/label.h>
#include <lvgl/lvgl_cpp/slider.h>
#include <src/core/lv_obj.h>
#include <src/core/lv_obj_pos.h>
#include <src/core/lv_obj_scroll.h>
#include <src/core/lv_obj_style.h>
#include <src/core/lv_obj_style_gen.h>
#include <src/display/lv_display.h>
#include <lvgl/lvgl_cpp/button.h>
#include <src/font/lv_font.h>
#include <src/misc/lv_area.h>
#include <src/misc/lv_color.h>
#include <src/misc/lv_style.h>
#include <src/misc/lv_types.h>
#include <string>
#include <vector>
#include <array>

using namespace smooth_ui_toolkit;
using namespace lvgl_cpp;

class DigitFlow : public LvObject {
public:
    DigitFlow(lv_obj_t* parent = nullptr)
    {
        _lv_obj = lv_obj_create(parent);
        lv_obj_null_on_delete(&_lv_obj);
    }

    virtual ~DigitFlow() {};

    inline void init()
    {
        // Mask basic
        setPadding(0, 0, 0, 0);
        setOutlineWidth(0);
        setRadius(0);
        setBorderWidth(0);
        removeFlag(LV_OBJ_FLAG_SCROLLABLE);
        setBgOpa(LV_OPA_TRANSP);

        // Child labels
        _digit_labels.clear();
        _digit_labels.resize(12);
        for (int i = 0; i < 12; i++) {
            _digit_labels[i] = std::make_shared<LvLabel>(_lv_obj);
            _digit_labels[i]->setText(std::to_string(_digit_list[i]));
            _digit_labels[i]->setAlign(LV_ALIGN_CENTER);
        }

        // Font height
        _font_height = lv_font_get_line_height(getTextFont());
        _digit_y_offset.springOptions().visualDuration = 0.6;
        _digit_y_offset.springOptions().bounce = 0.05;
        _digit_y_offset = _current_digit_index * _font_height;
        setSize(LV_SIZE_CONTENT, _font_height);
    }

    inline void setTextFont(const lv_font_t* font, lv_style_selector_t selector = LV_PART_MAIN)
    {
        LvObject::setTextFont(font, selector);
        init();
    }

    inline void setTextColor(lv_color_t color)
    {
        LvObject::setTextColor(color);
        for (auto& digit : _digit_labels) {
            digit->setTextColor(color);
        }
    }

    inline void update()
    {
        if (_font_height <= 0) {
            init();
        }
        _digit_y_offset.update();
        for (int i = 0; i < _digit_labels.size(); i++) {
            _digit_labels[i]->setPos(0, i * _font_height - _digit_y_offset.directValue());
        }
    }

    inline int value()
    {
        return _digit_list[_current_digit_index];
    }

    inline void increase()
    {
        if (_current_digit_index >= _digit_list.size() - 2) {
            _current_digit_index = 1;
            _digit_y_offset.retarget(0, 1 * _font_height);
        } else {
            _current_digit_index++;
            _digit_y_offset = _current_digit_index * _font_height;
        }
    }

    inline void decrease()
    {
        if (_current_digit_index <= 1) {
            _current_digit_index = _digit_list.size() - 2;
            _digit_y_offset.retarget((_digit_list.size() - 1) * _font_height, _current_digit_index * _font_height);
        } else {
            _current_digit_index--;
            _digit_y_offset = _current_digit_index * _font_height;
        }
    }

    inline void increaseTo(int targetValue)
    {
        increase();
        int target_digit = std::abs(targetValue) % 10;
        while (value() != target_digit) {
            increase();
        }
    }

    inline void decreaseTo(int targetValue)
    {
        decrease();
        int target_digit = std::abs(targetValue) % 10;
        while (value() != target_digit) {
            decrease();
        }
    }

    inline AnimateValue& flowAnimate()
    {
        return _digit_y_offset;
    }

protected:
    static inline constexpr std::array<int, 12> _digit_list = {9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int32_t _font_height = 0;
    AnimateValue _digit_y_offset;
    size_t _current_digit_index = 1;
    std::vector<std::shared_ptr<LvLabel>> _digit_labels;
};

class NumberFlow : public LvObject {
public:
    struct Digit_t {
        std::unique_ptr<DigitFlow> digitFlow;
        AnimateValue positionX;
        AnimateValue opacity;
        bool isGoingDestroy = false;
    };

    NumberFlow(lv_obj_t* parent = nullptr)
    {
        _lv_obj = lv_obj_create(parent);
        lv_obj_null_on_delete(&_lv_obj);
    }

    virtual ~NumberFlow() {};

    bool transparentBg = true;

    inline void init()
    {
        // Mask basic
        setPadding(0, 0, 0, 0);
        removeFlag(LV_OBJ_FLAG_SCROLLABLE);
        if (transparentBg) {
            setOutlineWidth(0);
            setBorderWidth(0);
            setBgOpa(LV_OPA_TRANSP);
        }

        // Font height
        _font_height = lv_font_get_line_height(getTextFont());
        _font_width = lv_font_get_glyph_width(getTextFont(), '0', '0');
        setSize(LV_SIZE_CONTENT, _font_height);

        setValue(_current_number);
    }

    inline void update()
    {
        if (_digits.empty()) {
            init();
        }

        handle_digit_destroy();

        for (auto& digit : _digits) {
            digit.digitFlow->update();
            digit.digitFlow->setPos(digit.positionX, 0);
            int opa = digit.opacity;
            if (opa > 255) {
                opa = 255;
            } else if (opa < 0) {
                opa = 0;
            }
            digit.digitFlow->setOpa(opa);
        }
    }

    inline int value()
    {
        return _current_number;
    }

    inline void setValue(int targetValue)
    {
        _current_number = targetValue;
        handle_digit_changed();
        handle_digit_number();
    }

protected:
    int32_t _font_height = 0;
    int32_t _font_width = 0;
    int _last_number = 0;
    int _current_number = 0;
    int _current_number_of_digits = 1;
    std::vector<Digit_t> _digits;

    int get_number_of_digits(int num)
    {
        if (num == 0) {
            return 1;
        }
        int count = 0;
        while (num != 0) {
            num /= 10;
            count++;
        }
        return count;
    }

    inline void handle_digit_changed()
    {
        auto new_number_of_digits = get_number_of_digits(_current_number);
        int digit_list_size = _digits.size();

        // Add digits
        if (new_number_of_digits > digit_list_size) {
            // mclog::info("add digits");
            while (new_number_of_digits > digit_list_size) {
                _digits.push_back(Digit_t());
                _digits.back().digitFlow = std::make_unique<DigitFlow>(_lv_obj);
                _digits.back().digitFlow->init();
                _digits.back().digitFlow->setTextColor(getTextColor());
                _digits.back().positionX.springOptions().visualDuration = 0.6;
                _digits.back().positionX.springOptions().bounce = 0.05;
                if (digit_list_size != 0) {
                    _digits.back().positionX.teleport((_current_number_of_digits - 1) * _font_width);
                }
                _digits.back().positionX.move(digit_list_size * _font_width);
                _digits.back().opacity.springOptions().visualDuration = 0.3;
                _digits.back().opacity.springOptions().bounce = 0.05;
                _digits.back().opacity.move(255);
                digit_list_size++;
            }
        }

        // Remove digits
        else if ((new_number_of_digits < digit_list_size) && (new_number_of_digits < _current_number_of_digits)) {
            // mclog::info("remove digits");
            if (_current_number_of_digits > new_number_of_digits) {
                // move extra digits back to 0, and mark destroy
                for (int i = new_number_of_digits; i < digit_list_size; i++) {
                    _digits[i].positionX.move((new_number_of_digits - 1) * _font_width);
                    _digits[i].opacity = 0;
                    _digits[i].opacity.move(0);
                    _digits[i].isGoingDestroy = true;
                }
            }
        }

        // Reorder digits
        for (int i = 0; i < new_number_of_digits; i++) {
            _digits[i].positionX.move(i * _font_width);
            _digits[i].opacity.move(255);
            _digits[i].isGoingDestroy = false;
        }

        _current_number_of_digits = new_number_of_digits;
    }

    inline void handle_digit_destroy()
    {
        for (int i = 0; i < _digits.size(); i++) {
            if (_digits[i].isGoingDestroy && _digits[i].positionX.done() && _digits[i].opacity.done()) {
                _digits.erase(_digits.begin() + i);
            }
        }
    }

    inline void handle_digit_number()
    {
        // Iterate through each digit
        int number = _current_number;
        int divisor = std::pow(10, _current_number_of_digits - 1);
        for (int i = 0; i < _current_number_of_digits; ++i) {
            int digit = number / divisor;
            // mclog::info("{}", digit);
            if (_digits[i].digitFlow->value() != digit) {
                if (_last_number < _current_number) {
                    _digits[i].digitFlow->increaseTo(digit);
                } else {
                    _digits[i].digitFlow->decreaseTo(digit);
                }
            }
            number %= divisor;
            divisor /= 10;
        }
        _last_number = _current_number;
    }
};

int main()
{
    lvgl::create_window(800, 520);

    auto number_flow = new NumberFlow(lv_screen_active());
    number_flow->setAlign(LV_ALIGN_CENTER);
    number_flow->setPos(0, -110);
    number_flow->setTextFont(&lv_font_montserrat_48);
    // number_flow->setTextFont(&ui_font_RajdhaniBold72);
    // number_flow->setTextFont(&ui_font_RajdhaniBold144);
    // number_flow->transparentBg = false;
    number_flow->setTextColor(lv_color_hex(0x0A0A0A));

    // flex layout
    auto flex_layout = new LvObject(lv_screen_active());
    flex_layout->setBorderWidth(0);
    flex_layout->setBgOpa(0);
    flex_layout->setFlexFlow(LV_FLEX_FLOW_ROW);
    flex_layout->setFlexAlign(LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    flex_layout->setSize(LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    flex_layout->setAlign(LV_ALIGN_CENTER);
    flex_layout->setPos(0, 150);
    flex_layout->setPadColumn(50);

    auto btn_next = new LvButton(flex_layout->get());
    btn_next->label().setText("-1");
    btn_next->onClick().connect([&]() { number_flow->setValue(number_flow->value() - 1); });

    auto btn_last = new LvButton(flex_layout->get());
    btn_last->label().setText("+1");
    btn_last->onClick().connect([&]() { number_flow->setValue(number_flow->value() + 1); });

    auto btn_random = new LvButton(flex_layout->get());
    btn_random->label().setText("random");
    btn_random->onClick().connect([&]() { number_flow->setValue(rand()); });

    int target_value = 0;
    auto slider = new LvSlider(flex_layout->get());
    slider->setRange(1, 9);
    slider->setValue(1);
    slider->onValueChanged().connect([&](int value) {
        int target_value = 0;
        for (int i = 1; i <= value; ++i) {
            target_value = target_value * 10 + i;
        }
        // mclog::info("{}", target_value);
        number_flow->setValue(target_value);
    });

    while (1) {
        number_flow->update();
        lvgl::update_window();
    }

    return 0;
}
