/**
 * @file text_area.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-04-24
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "obj.hpp"
#include <lvgl.h>
#include <string>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

/**
 * @brief Lvgl text area
 *
 */
class TextArea : public Widget<lv_textarea_create> {
public:
    using Widget::Widget;

    void addChar(uint32_t c)
    {
        lv_textarea_add_char(this->raw_ptr(), c);
    }

    void addText(const std::string& text)
    {
        lv_textarea_add_text(this->raw_ptr(), text.c_str());
    }

    void deleteChar()
    {
        lv_textarea_delete_char(this->raw_ptr());
    }

    void deleteCharForward()
    {
        lv_textarea_delete_char_forward(this->raw_ptr());
    }

    void setText(const std::string& text)
    {
        lv_textarea_set_text(this->raw_ptr(), text.c_str());
    }

    void setPlaceholderText(const std::string& text)
    {
        lv_textarea_set_placeholder_text(this->raw_ptr(), text.c_str());
    }

    void setCursorPos(int32_t pos)
    {
        lv_textarea_set_cursor_pos(this->raw_ptr(), pos);
    }

    void setCursorClickPos(bool enable)
    {
        lv_textarea_set_cursor_click_pos(this->raw_ptr(), enable);
    }

    void setPasswordMode(bool enable)
    {
        lv_textarea_set_password_mode(this->raw_ptr(), enable);
    }

    void setPasswordBullet(const std::string& bullet)
    {
        lv_textarea_set_password_bullet(this->raw_ptr(), bullet.c_str());
    }

    void setOneLine(bool enable)
    {
        lv_textarea_set_one_line(this->raw_ptr(), enable);
    }

    void setAcceptedChars(const std::string& list)
    {
        lv_textarea_set_accepted_chars(this->raw_ptr(), list.c_str());
    }

    void setMaxLength(uint32_t num)
    {
        lv_textarea_set_max_length(this->raw_ptr(), num);
    }

    void setInsertReplace(const std::string& txt)
    {
        lv_textarea_set_insert_replace(this->raw_ptr(), txt.c_str());
    }

    void setTextSelection(bool enable)
    {
        lv_textarea_set_text_selection(this->raw_ptr(), enable);
    }

    void setTextAreaAlign(lv_text_align_t align)
    {
        lv_textarea_set_align(this->raw_ptr(), align);
    }
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit