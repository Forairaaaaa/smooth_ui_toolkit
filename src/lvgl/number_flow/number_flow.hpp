/**
 * @file number_flow.hpp
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
#include "../lvgl_cpp/obj.hpp"
#include "../lvgl_cpp/label.hpp"
#include "digit_flow.hpp"
#include <lvgl.h>
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>
#include <string>

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

    // 动画类型，默认 spring 更自然
    animation_type::Type_t animationType = animation_type::spring;
    // 透明背景
    bool transparentBg = true;
    // 显示正负号
    bool showPositiveSign = false;
    // 最小显示位数，不足时前导补0
    int minDigits = 0;

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

    // 设置前缀
    void setPrefix(const std::string& newPrefix)
    {
        _prefix = newPrefix;
        handle_prefix_changed();
    }

    // 设置后缀
    void setSuffix(const std::string& newSuffix)
    {
        _suffix = newSuffix;
        handle_suffix_changed();
    }

    // 设置前缀颜色
    void setPrefixColor(lv_color_t color)
    {
        if (_label_prefix && _label_prefix->label) {
            _label_prefix->label->setTextColor(color);
        }
    }

    // 设置后缀颜色
    void setSuffixColor(lv_color_t color)
    {
        if (_label_suffix && _label_suffix->label) {
            _label_suffix->label->setTextColor(color);
        }
    }

    // 设置数字颜色
    void setDigitColor(lv_color_t color)
    {
        Widget::setTextColor(color);
        for (auto& digit : _digits) {
            if (digit.digitFlow) {
                digit.digitFlow->setTextColor(color);
            }
        }
        if (_label_sign && _label_sign->label) {
            _label_sign->label->setTextColor(color);
        }
    }

    void update()
    {
        if (_digits.empty()) {
            init();
        }

        handle_prefix_update();
        handle_suffix_update();
        handle_sign_update();
        handle_digit_update();
    }

    int value()
    {
        return _current_number;
    }

    // 获取控件总宽度的便利方法
    int getTotalWidth()
    {
        update_prefix_width_cache();
        update_suffix_width_cache();
        int digits_width = _current_number_of_digits * _font_width;
        int sign_width = get_sign_width();
        return _cached_prefix_width + sign_width + digits_width + _cached_suffix_width;
    }

    void setValue(int targetValue)
    {
        _current_number = targetValue;
        handle_prefix_changed();
        handle_sign_changed();
        handle_digit_changed();
        handle_suffix_changed();
        handle_digit_number_changed();
    }

protected:
    int32_t _font_height = 0;
    int32_t _font_width = 0;
    int _last_number = 0;
    int _current_number = 0;
    int _current_number_of_digits = 1;
    std::vector<Digit_t> _digits;
    std::unique_ptr<Label_t> _label_sign;
    std::unique_ptr<Label_t> _label_prefix;
    std::unique_ptr<Label_t> _label_suffix;
    std::string _prefix = "";
    std::string _suffix = "";

    int _cached_prefix_width = 0;
    int _cached_suffix_width = 0;

    int get_actual_digits(int num)
    {
        if (num == 0) {
            return 1;
        }
        int count = 0;
        int temp = std::abs(num);
        while (temp != 0) {
            temp /= 10;
            count++;
        }
        return count;
    }

    int get_number_of_digits(int num)
    {
        return std::max(get_actual_digits(num), minDigits);
    }

    int get_text_width(const std::string& text)
    {
        int width = 0;
        for (char c : text) {
            width += lv_font_get_glyph_width(getTextFont(), c, c);
        }
        return width;
    }

    int get_sign_width()
    {
        if (_label_sign && !_label_sign->isGoingDestroy) {
            return lv_font_get_glyph_width(getTextFont(), _current_number < 0 ? '-' : '+', '0');
        }
        return 0;
    }

    void update_prefix_width_cache()
    {
        _cached_prefix_width = (_label_prefix && !_label_prefix->isGoingDestroy) ? get_text_width(_prefix) : 0;
    }

    void update_suffix_width_cache()
    {
        _cached_suffix_width = (_label_suffix && !_label_suffix->isGoingDestroy) ? get_text_width(_suffix) : 0;
    }

    void handle_digit_changed()
    {
        auto new_number_of_digits = get_number_of_digits(_current_number);
        int digit_list_size = _digits.size();

        // Add digits
        if (new_number_of_digits > digit_list_size) {
            // mclog::info("add digits");
            while (new_number_of_digits > digit_list_size) {
                _digits.emplace_back();
                _digits.back().digitFlow = std::make_unique<DigitFlow>(this->raw_ptr());
                _digits.back().digitFlow->animationType = animationType;
                _digits.back().digitFlow->init();
                _digits.back().digitFlow->setTextColor(getTextColor());
                DigitFlow::setup_animation(_digits.back().positionX, animationType);
                if (digit_list_size != 0) {
                    _digits.back().positionX.teleport((_current_number_of_digits - 1) * _font_width);
                }
                _digits.back().positionX.move(digit_list_size * _font_width);
                DigitFlow::setup_animation(_digits.back().opacity, animationType);
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
        update_prefix_width_cache();
        int sign_width = get_sign_width();

        for (int i = 0; i < new_number_of_digits; i++) {
            _digits[i].positionX.move(i * _font_width + _cached_prefix_width + sign_width);
            _digits[i].opacity.move(255);
            _digits[i].isGoingDestroy = false;
        }

        _current_number_of_digits = new_number_of_digits;
    }

    void handle_digit_update()
    {
        for (int i = 0; i < _digits.size(); i++) {
            if (_digits[i].isGoingDestroy && _digits[i].positionX.done() && _digits[i].opacity.done()) {
                _digits.erase(_digits.begin() + i);
            }
        }

        for (auto& digit : _digits) {
            digit.digitFlow->update();
            digit.digitFlow->setPos(digit.positionX, 0);
            digit.digitFlow->setOpa(std::clamp((int)digit.opacity.value(), 0, 255));
        }
    }

    void handle_digit_number_changed()
    {
        // Iterate through each digit
        int number = std::abs(_current_number);
        int actual_digits = get_actual_digits(number);
        int divisor = std::pow(10, _current_number_of_digits - 1);

        for (int i = 0; i < _current_number_of_digits; ++i) {
            int digit;

            // 如果当前位是前导零位置
            if (i < (_current_number_of_digits - actual_digits)) {
                digit = 0;
            } else {
                digit = number / divisor;
                number %= divisor;
            }
            divisor /= 10;

            // mclog::info("pos {}: digit {}", i, digit);
            if (_digits[i].digitFlow->value() != digit) {
                bool increase = (_last_number < _current_number);
                if (_current_number < 0) {
                    increase = !increase;
                }
                if (increase) {
                    _digits[i].digitFlow->increaseTo(digit);
                } else {
                    _digits[i].digitFlow->decreaseTo(digit);
                }
            }
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
            if (_label_sign) {
                _label_sign->isGoingDestroy = true;
                _label_sign->positionX.move(0);
                _label_sign->opacity.move(0);
            }
        } else {
            if (!_label_sign) {
                _label_sign = std::make_unique<Label_t>();
                _label_sign->label = std::make_unique<Label>(this->raw_ptr());
                DigitFlow::setup_animation(_label_sign->positionX, animationType);
                DigitFlow::setup_animation(_label_sign->opacity, animationType);
            }
            update_prefix_width_cache();
            _label_sign->positionX.move(_cached_prefix_width);
            if (_label_sign->label->getText() != new_sign) {
                _label_sign->opacity.teleport(0);
            }
            _label_sign->opacity.move(255);
            _label_sign->isGoingDestroy = false;
            _label_sign->label->setText(new_sign);
        }
    }

    void handle_prefix_changed()
    {
        if (_prefix.empty()) {
            if (_label_prefix) {
                _label_prefix->isGoingDestroy = true;
                _label_prefix->positionX.move(0);
                _label_prefix->opacity.move(0);
            }
        } else {
            if (!_label_prefix) {
                _label_prefix = std::make_unique<Label_t>();
                _label_prefix->label = std::make_unique<Label>(this->raw_ptr());

                DigitFlow::setup_animation(_label_prefix->positionX, animationType);
                DigitFlow::setup_animation(_label_prefix->opacity, animationType);
            }
            _label_prefix->positionX.move(0);
            if (_label_prefix->label->getText() != _prefix) {
                _label_prefix->opacity.teleport(0);
            }
            _label_prefix->opacity.move(255);
            _label_prefix->isGoingDestroy = false;
            _label_prefix->label->setText(_prefix);
            update_prefix_width_cache();
        }
    }

    void handle_suffix_changed()
    {
        if (_suffix.empty()) {
            if (_label_suffix) {
                _label_suffix->isGoingDestroy = true;
                _label_suffix->positionX.move(0);
                _label_suffix->opacity.move(0);
            }
        } else {
            if (!_label_suffix) {
                _label_suffix = std::make_unique<Label_t>();
                _label_suffix->label = std::make_unique<Label>(this->raw_ptr());

                DigitFlow::setup_animation(_label_suffix->positionX, animationType);
                DigitFlow::setup_animation(_label_suffix->opacity, animationType);
            }

            // Position suffix after digits
            int digits_width = _current_number_of_digits * _font_width;
            update_prefix_width_cache();
            int sign_width = get_sign_width();

            _label_suffix->positionX.move(_cached_prefix_width + sign_width + digits_width);
            if (_label_suffix->label->getText() != _suffix) {
                _label_suffix->opacity.teleport(0);
            }
            _label_suffix->opacity.move(255);
            _label_suffix->isGoingDestroy = false;
            _label_suffix->label->setText(_suffix);
            update_suffix_width_cache();
        }
    }

    void handle_prefix_update()
    {
        if (_label_prefix) {
            _label_prefix->positionX.update();
            _label_prefix->opacity.update();
            _label_prefix->label->setPos(_label_prefix->positionX, 0);
            _label_prefix->label->setOpa(std::clamp((int)_label_prefix->opacity.value(), 0, 255));
            if (_label_prefix->isGoingDestroy && _label_prefix->positionX.done() && _label_prefix->opacity.done()) {
                _label_prefix.reset();
            }
        }
    }

    void handle_suffix_update()
    {
        if (_label_suffix) {
            _label_suffix->positionX.update();
            _label_suffix->opacity.update();
            _label_suffix->label->setPos(_label_suffix->positionX, 0);
            _label_suffix->label->setOpa(std::clamp((int)_label_suffix->opacity.value(), 0, 255));
            if (_label_suffix->isGoingDestroy && _label_suffix->positionX.done() && _label_suffix->opacity.done()) {
                _label_suffix.reset();
            }
        }
    }

    void handle_sign_update()
    {
        if (_label_sign) {
            _label_sign->positionX.update();
            _label_sign->opacity.update();
            _label_sign->label->setPos(_label_sign->positionX, 0);
            _label_sign->label->setOpa(std::clamp((int)_label_sign->opacity.value(), 0, 255));
            if (_label_sign->isGoingDestroy && _label_sign->positionX.done() && _label_sign->opacity.done()) {
                _label_sign.reset();
            }
        }
    }
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit