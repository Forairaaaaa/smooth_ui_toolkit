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

SmoothLineChart::SmoothLineChart()
{
    // Default no zoom
    _data.zoom_transition.jumpTo(_config.zoomBase, _config.zoomBase);
}

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

const Vector2D_t& SmoothLineChart::getChartPoint(int rawX, int rawY)
{
    // Apply zoom
    _data.temp_buffer = getIntZoom();
    _data.result_buffer.x = rawX * _data.temp_buffer.x / _config.zoomBase;
    _data.result_buffer.y = rawY * _data.temp_buffer.y / _config.zoomBase;

    // Apply offset
    _data.temp_buffer = getOffset();
    _data.result_buffer.x = _data.result_buffer.x + _config.origin.x + _data.temp_buffer.x;
    _data.result_buffer.y = _data.result_buffer.y + _config.origin.y + _data.temp_buffer.y;

    return _data.result_buffer;
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

int SmoothLineChart::floatZoom2IntZoom(const float& floatZoom)
{
    fpm::fixed_16_16 fz{floatZoom};
    return static_cast<int>(fz * _config.zoomBase);
}

const float& SmoothLineChart::intZoom2FloatZoom(const int& intZoom)
{
    fpm::fixed_16_16 fz{intZoom};
    _data.zoom_value_buffer.x = static_cast<float>(fz / _config.zoomBase);
    return _data.zoom_value_buffer.x;
}

const SmoothLineChart::FloatZoom2D_t& SmoothLineChart::intZoom2FloatZoom(const Vector2D_t& intZoom)
{
    fpm::fixed_16_16 fzx{intZoom.x};
    fpm::fixed_16_16 fzy{intZoom.y};
    _data.zoom_value_buffer.x = static_cast<float>(fzx / _config.zoomBase);
    _data.zoom_value_buffer.y = static_cast<float>(fzy / _config.zoomBase);
    return _data.zoom_value_buffer;
}
