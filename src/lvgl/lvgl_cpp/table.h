/**
 * @file table.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-09-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "obj.h"
#include <lvgl.h>
#include <stdint.h>
#include <string>

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

    void setCellValue(uint32_t row, uint32_t col, const std::string& txt)
    {
        lv_table_set_cell_value(this->raw_ptr(), row, col, txt.c_str());
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
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit