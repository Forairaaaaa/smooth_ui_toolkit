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
#if LV_USE_TEXTAREA

#include "obj.hpp"
#include <lvgl.h>
#include <string_view>

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

    void addText(std::string_view text)
    {
        lv_textarea_add_text(this->raw_ptr(), text.data());
    }

    void deleteChar()
    {
        lv_textarea_delete_char(this->raw_ptr());
    }

    void deleteCharForward()
    {
        lv_textarea_delete_char_forward(this->raw_ptr());
    }

    void setText(std::string_view text)
    {
        lv_textarea_set_text(this->raw_ptr(), text.data());
    }

    void setPlaceholderText(std::string_view text)
    {
        lv_textarea_set_placeholder_text(this->raw_ptr(), text.data());
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

    void setPasswordBullet(std::string_view bullet)
    {
        lv_textarea_set_password_bullet(this->raw_ptr(), bullet.data());
    }

    void setOneLine(bool enable)
    {
        lv_textarea_set_one_line(this->raw_ptr(), enable);
    }

    void setAcceptedChars(std::string_view list)
    {
        lv_textarea_set_accepted_chars(this->raw_ptr(), list.data());
    }

    void setMaxLength(uint32_t num)
    {
        lv_textarea_set_max_length(this->raw_ptr(), num);
    }

    void setInsertReplace(std::string_view txt)
    {
        lv_textarea_set_insert_replace(this->raw_ptr(), txt.data());
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

#endif
