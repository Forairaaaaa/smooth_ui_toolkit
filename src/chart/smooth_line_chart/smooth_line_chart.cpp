/**
 * @file smooth_line_chart.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-15
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "smooth_line_chart.h"
#include "../../utils/fpm/fixed.hpp"
#include "../../utils/fpm/math.hpp"

using namespace SmoothUIToolKit;
using namespace SmoothUIToolKit::Chart;

SmoothLineChart::SmoothLineChart() { jumpZoomTo(1, 1); }

void SmoothLineChart::update(const TimeSize_t& currentTime)
{
    // Callback
    onUpdate(currentTime);

    // Read input callback
    if (currentTime - _data.read_input_time_count > _config.readInputInterval)
    {
        onReadInput();
        _data.read_input_time_count = currentTime;
    }

    _data.offset_transition.update(currentTime);
    _data.zoom_transition.update(currentTime);

    // Render callback
    if (currentTime - _data.render_time_count > _config.renderInterval)
    {
        onRender();
        _data.render_time_count = currentTime;
    }
}

const Vector2D_t& SmoothLineChart::getChartPoint(const float& rawX, const float& rawY)
{
    fpm::fixed_24_8 f_x{rawX};
    fpm::fixed_24_8 f_y{rawY};

    // Apply zoom
    _data.temp_buffer = _data.zoom_transition.getValue();
    f_x = f_x * _data.temp_buffer.x / _config.valueScale;
    f_y = f_y * _data.temp_buffer.y / _config.valueScale;

    // Apply offset
    _data.temp_buffer = _data.offset_transition.getValue();
    f_x = f_x + _config.origin.x + _data.temp_buffer.x / _config.valueScale;
    f_y = f_y + _config.origin.y + _data.temp_buffer.y / _config.valueScale;

    _data.point_buffer.x = static_cast<int>(f_x);
    _data.point_buffer.y = static_cast<int>(f_y);
    return _data.point_buffer;
}

bool SmoothLineChart::isInChart(const int& chartX, const int& chartY)
{
    if (chartX < _config.origin.x)
        return false;
    if (chartX > _config.origin.x + _config.size.width)
        return false;
    if (chartY < _config.origin.y)
        return false;
    if (chartY > _config.origin.y + _config.size.height)
        return false;
    return true;
}

int SmoothLineChart::_float_2_int(const float& value)
{
    fpm::fixed_24_8 f_value{value};
    return static_cast<int>(f_value * _config.valueScale);
}

const float& SmoothLineChart::_int_2_float(const int& value)
{
    fpm::fixed_24_8 f_value{value};
    _data.float_zoom_buffer.x = static_cast<float>(f_value / _config.valueScale);
    return _data.float_zoom_buffer.x;
}

const VectorFloat2D_t& SmoothLineChart::_int_2_float(const Vector2D_t& value)
{
    fpm::fixed_24_8 f_value_x{value.x};
    fpm::fixed_24_8 f_value_y{value.y};
    _data.float_zoom_buffer.x = static_cast<float>(f_value_x / _config.valueScale);
    _data.float_zoom_buffer.y = static_cast<float>(f_value_y / _config.valueScale);
    return _data.float_zoom_buffer;
}

const float& SmoothLineChart::getYZoomByRange(const float& minY, const float& maxY)
{
    fpm::fixed_24_8 f_min{minY};
    fpm::fixed_24_8 f_max{maxY};
    fpm::fixed_24_8 f_height{_config.size.height};
    _data.float_zoom_buffer.x = static_cast<float>(f_height / (f_max - f_min));
    return _data.float_zoom_buffer.x;
}
