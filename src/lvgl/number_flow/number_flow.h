/**
 * @file number_flow.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */
// Refs: https://number-flow.barvian.me
#pragma once
#include "../lvgl_cpp/obj.h"
#include "../lvgl_cpp/label.h"
#include "digit_flow.h"
#include <lvgl.h>
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

class NumberFlow : public Widget<lv_obj_create> {
public:
    using Widget::Widget;

    // no copy constructor and copy assignment operator
    NumberFlow(const NumberFlow&) = delete;
    NumberFlow& operator=(const NumberFlow&) = delete;

    struct Item_t {
        AnimateValue positionX;
        AnimateValue opacity;
        bool isGoingDestroy = false;
    };

    struct Digit_t : public Item_t {
        std::unique_ptr<DigitFlow> digitFlow;
    };

    struct Label_t : public Item_t {
        std::unique_ptr<Label> label;
    };

    // Spring will feels more natural
    animation_type::Type_t animationType = animation_type::spring;
    bool transparentBg = true;
    bool showPositiveSign = false;

    void init()
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

    void update()
    {
        if (_digits.empty()) {
            init();
        }

        handle_sign_update();
        handle_digit_update();
    }

    int value()
    {
        return _current_number;
    }

    void setValue(int targetValue)
    {
        _current_number = targetValue;
        handle_sign_changed();
        handle_digit_changed();
        handle_digit_number_changed();
    }

protected:
    int32_t _font_height = 0;
    int32_t _font_width = 0;
    int _last_number = 0;
    int _current_number = 0;
    int _current_number_of_digits = 1;
    std::vector<std::unique_ptr<Digit_t>> _digits;
    std::unique_ptr<Label_t> _sign;

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

    void handle_digit_changed()
    {
        auto new_number_of_digits = get_number_of_digits(_current_number);
        int digit_list_size = _digits.size();

        // Add digits
        if (new_number_of_digits > digit_list_size) {
            // mclog::info("add digits");
            while (new_number_of_digits > digit_list_size) {
                _digits.push_back(std::make_unique<Digit_t>());
                _digits.back()->digitFlow = std::make_unique<DigitFlow>(this->raw_ptr());
                _digits.back()->digitFlow->animationType = animationType;
                _digits.back()->digitFlow->init();
                _digits.back()->digitFlow->setTextColor(getTextColor());
                DigitFlow::setup_animation(_digits.back()->positionX, animationType);
                if (digit_list_size != 0) {
                    _digits.back()->positionX.teleport((_current_number_of_digits - 1) * _font_width);
                }
                _digits.back()->positionX.move(digit_list_size * _font_width);
                DigitFlow::setup_animation(_digits.back()->opacity, animationType);
                _digits.back()->opacity.move(255);
                digit_list_size++;
            }
        }

        // Remove digits
        else if ((new_number_of_digits < digit_list_size) && (new_number_of_digits < _current_number_of_digits)) {
            // mclog::info("remove digits");
            if (_current_number_of_digits > new_number_of_digits) {
                // move extra digits back to 0, and mark destroy
                for (int i = new_number_of_digits; i < digit_list_size; i++) {
                    _digits[i]->positionX.move((new_number_of_digits - 1) * _font_width);
                    _digits[i]->opacity = 0;
                    _digits[i]->opacity.move(0);
                    _digits[i]->isGoingDestroy = true;
                }
            }
        }

        // Reorder digits
        int sign_width = 0;
        if (_sign) {
            if (!_sign->isGoingDestroy) {
                sign_width = lv_font_get_glyph_width(getTextFont(), _current_number < 0 ? '-' : '+', '0');
            }
        }
        for (int i = 0; i < new_number_of_digits; i++) {
            _digits[i]->positionX.move(i * _font_width + sign_width);
            _digits[i]->opacity.move(255);
            _digits[i]->isGoingDestroy = false;
        }

        _current_number_of_digits = new_number_of_digits;
    }

    void handle_digit_update()
    {
        for (int i = 0; i < _digits.size(); i++) {
            if (_digits[i]->isGoingDestroy && _digits[i]->positionX.done() && _digits[i]->opacity.done()) {
                _digits.erase(_digits.begin() + i);
            }
        }

        for (auto& digit : _digits) {
            digit->digitFlow->update();
            digit->digitFlow->setPos(digit->positionX, 0);
            digit->digitFlow->setOpa(std::clamp((int)digit->opacity.value(), 0, 255));
        }
    }

    void handle_digit_number_changed()
    {
        // Iterate through each digit
        int number = _current_number;
        int divisor = std::pow(10, _current_number_of_digits - 1);
        for (int i = 0; i < _current_number_of_digits; ++i) {
            int digit = std::abs(number / divisor);
            // mclog::info("{}", digit);
            if (_digits[i]->digitFlow->value() != digit) {
                bool increase = (_last_number < _current_number);
                if (_current_number < 0) {
                    increase = !increase;
                }
                if (increase) {
                    _digits[i]->digitFlow->increaseTo(digit);
                } else {
                    _digits[i]->digitFlow->decreaseTo(digit);
                }
            }
            number %= divisor;
            divisor /= 10;
        }
        _last_number = _current_number;
    }

    void handle_sign_changed()
    {
        std::string new_sign;
        if (_current_number < 0) {
            new_sign = "-";
        } else if (_current_number > 0) {
            new_sign = showPositiveSign ? "+" : "";
        }

        if (new_sign.empty()) {
            if (_sign) {
                _sign->isGoingDestroy = true;
                _sign->positionX.move(0);
                _sign->opacity.move(0);
            }
        } else {
            if (!_sign) {
                _sign = std::make_unique<Label_t>();
                _sign->label = std::make_unique<Label>(this->raw_ptr());
                DigitFlow::setup_animation(_sign->positionX, animationType);
                DigitFlow::setup_animation(_sign->opacity, animationType);
            }
            _sign->positionX.move(0);
            if (_sign->label->getText() != new_sign) {
                _sign->opacity.teleport(0);
            }
            _sign->opacity.move(255);
            _sign->isGoingDestroy = false;
            _sign->label->setText(new_sign);
        }
    }

    void handle_sign_update()
    {
        if (_sign) {
            _sign->positionX.update();
            _sign->opacity.update();
            _sign->label->setPos(0, _sign->positionX);
            _sign->label->setOpa(std::clamp((int)_sign->opacity.value(), 0, 255));
            if (_sign->isGoingDestroy && _sign->positionX.done() && _sign->opacity.done()) {
                _sign.reset();
            }
        }
    }
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit