/**
 * @file table.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-09-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <lvgl.h>

#if LV_USE_TABLE

#include "obj.hpp"
#include <cstdint>
#include <string_view>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

/**
 * @brief Lvgl table
 *
 */
class Table : public Widget<lv_table_create> {
public:
    using Widget::Widget;

    void setCellValue(uint32_t row, uint32_t col, const char* txt)
    {
        lv_table_set_cell_value(this->raw_ptr(), row, col, txt);
    }

    void setCellValue(uint32_t row, uint32_t col, std::string_view txt)
    {
        lv_table_set_cell_value(this->raw_ptr(), row, col, txt.data());
    }

    void setRowCount(uint32_t row_cnt)
    {
        lv_table_set_row_count(this->raw_ptr(), row_cnt);
    }

    void setColumnCount(uint32_t col_cnt)
    {
        lv_table_set_column_count(this->raw_ptr(), col_cnt);
    }

    void setColumnWidth(uint32_t col_id, int32_t w)
    {
        lv_table_set_column_width(this->raw_ptr(), col_id, w);
    }

    void setCellCtrl(uint32_t row, uint32_t col, lv_table_cell_ctrl_t ctrl)
    {
        lv_table_set_cell_ctrl(this->raw_ptr(), row, col, ctrl);
    }

    void clearCellCtrl(uint32_t row, uint32_t col, lv_table_cell_ctrl_t ctrl)
    {
        lv_table_clear_cell_ctrl(this->raw_ptr(), row, col, ctrl);
    }

    void setCellUserData(uint32_t row, uint32_t col, void* user_data)
    {
        lv_table_set_cell_user_data(this->raw_ptr(), row, col, user_data);
    }

    void setSelectedCell(uint32_t row, uint32_t col)
    {
        lv_table_set_selected_cell(this->raw_ptr(), row, col);
    }

    const char* getCellValue(uint32_t row, uint32_t col)
    {
        return lv_table_get_cell_value(this->raw_ptr(), row, col);
    }

    uint32_t getRowCount()
    {
        return lv_table_get_row_count(this->raw_ptr());
    }

    uint32_t getColumnCount()
    {
        return lv_table_get_column_count(this->raw_ptr());
    }

    int32_t getColumnWidth(uint32_t col)
    {
        return lv_table_get_column_width(this->raw_ptr(), col);
    }

    bool hasCellCtrl(uint32_t row, uint32_t col, lv_table_cell_ctrl_t ctrl)
    {
        return lv_table_has_cell_ctrl(this->raw_ptr(), row, col, ctrl);
    }

    void getSelectedCell(uint32_t* row, uint32_t* col)
    {
        lv_table_get_selected_cell(this->raw_ptr(), row, col);
    }

    void* getCellUserData(uint32_t row, uint32_t col)
    {
        return lv_table_get_cell_user_data(this->raw_ptr(), row, col);
    }

    Signal<uint32_t, uint32_t>& onCellSelected(void)
    {
        if (!_on_cell_selected) {
            _on_cell_selected = std::make_unique<Signal<uint32_t, uint32_t>>();
            addEventCb(
                [](lv_event_t* e) {
                    auto on_cell_selected = (Signal<uint32_t, uint32_t>*)lv_event_get_user_data(e);
                    uint32_t row, col;
                    lv_table_get_selected_cell((lv_obj_t*)lv_event_get_target(e), &row, &col);
                    on_cell_selected->emit(row, col);
                },
                LV_EVENT_VALUE_CHANGED,
                _on_cell_selected.get());
        }
        return *_on_cell_selected;
    }

private:
    std::unique_ptr<Signal<uint32_t, uint32_t>> _on_cell_selected;
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit

#endif
