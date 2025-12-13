/**
 * @file chart.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-04-10
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "obj.hpp"
#include <lvgl.h>
#include <vector>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

/**
 * @brief Lvgl chart
 *
 */
class Chart : public Widget<lv_chart_create> {
public:
    using Widget::Widget;

    // ~Chart()
    // {
    //     // for (int i = 0; i < _series_list.size(); i++) {
    //     //     removeSeries(i);
    //     // }
    // }

    void setPointCount(uint32_t cnt)
    {
        lv_chart_set_point_count(this->raw_ptr(), cnt);
    }

    void setRange(lv_chart_axis_t axis, int32_t min, int32_t max)
    {
        lv_chart_set_range(this->raw_ptr(), axis, min, max);
    }

    void setUpdateMode(lv_chart_update_mode_t update_mode)
    {
        lv_chart_set_update_mode(this->raw_ptr(), update_mode);
    }

    void setDivLineCount(uint8_t hdiv, uint8_t vdiv)
    {
        lv_chart_set_div_line_count(this->raw_ptr(), hdiv, vdiv);
    }

    lv_chart_series_t* addSeriesRaw(lv_color_t color, lv_chart_axis_t axis)
    {
        return lv_chart_add_series(this->raw_ptr(), color, axis);
    }

    void removeSeriesRaw(lv_chart_series_t* series)
    {
        lv_chart_remove_series(this->raw_ptr(), series);
    }

    void setNextValueRaw(lv_chart_series_t* series, int32_t value)
    {
        lv_chart_set_next_value(this->raw_ptr(), series, value);
    }

    int addSeries(lv_color_t color, lv_chart_axis_t axis)
    {
        _series_list.push_back(addSeriesRaw(color, axis));
        return _series_list.size() - 1;
    }

    void removeSeries(int seriesIndex)
    {
        if (seriesIndex >= _series_list.size()) {
            return;
        }
        removeSeriesRaw(_series_list[seriesIndex]);
        _series_list.erase(_series_list.begin() + seriesIndex);
    }

    void setNextValue(int seriesIndex, int32_t value)
    {
        if (seriesIndex >= _series_list.size()) {
            return;
        }
        setNextValueRaw(_series_list[seriesIndex], value);
    }

    const std::vector<lv_chart_series_t*>& getSeriesList()
    {
        return _series_list;
    }

    lv_chart_series_t* getSeries(int index)
    {
        if (index >= _series_list.size()) {
            return nullptr;
        }
        return _series_list[index];
    }

protected:
    std::vector<lv_chart_series_t*> _series_list;
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit