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

using namespace SmoothUIToolKit;
using namespace SmoothUIToolKit::Chart;

SmoothLineChart::SmoothLineChart()
{
    // Default no zoom
    _data.zoom_transition.jumpTo(ZoomBase, ZoomBase);
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
    // Apply offset
    _data.temp_buffer = getOffset();
    _data.result_buffer.x = rawX + _config.origin.x + _data.temp_buffer.x;
    _data.result_buffer.y = rawY + _config.origin.y + _data.temp_buffer.y;

    // Apply zoom
    _data.temp_buffer = getZoom();
    _data.result_buffer.x = _data.result_buffer.x * _data.temp_buffer.x / ZoomBase;
    _data.result_buffer.y = _data.result_buffer.y * _data.temp_buffer.y / ZoomBase;

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
