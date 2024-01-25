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
#include <cmath>

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

/* -------------------------------------------------------------------------- */
/*                                   Convert                                  */
/* -------------------------------------------------------------------------- */
int SmoothLineChart::_float_2_int(const float& value)
{
    fpm::fixed_24_8 f_value{value};
    return static_cast<int>(f_value * _config.valueScale);
}

const float& SmoothLineChart::_int_2_float(const int& value)
{
    fpm::fixed_24_8 f_value{value};
    _data.temp_float_buffer.x = static_cast<float>(f_value / _config.valueScale);
    return _data.temp_float_buffer.x;
}

const VectorFloat2D_t& SmoothLineChart::_int_2_float(const Vector2D_t& value)
{
    fpm::fixed_24_8 f_value_x{value.x};
    fpm::fixed_24_8 f_value_y{value.y};
    _data.temp_float_buffer.x = static_cast<float>(f_value_x / _config.valueScale);
    _data.temp_float_buffer.y = static_cast<float>(f_value_y / _config.valueScale);
    return _data.temp_float_buffer;
}

/* -------------------------------------------------------------------------- */
/*                                Current value                               */
/* -------------------------------------------------------------------------- */
const VectorFloat2D_t& SmoothLineChart::getCurrentOffset()
{
    fpm::fixed_24_8 f_offset_x{_data.offset_transition.getValue().x};
    fpm::fixed_24_8 f_offset_y{_data.offset_transition.getValue().y};
    _data.temp_float_buffer.x = static_cast<float>(f_offset_x / _data.zoom_transition.getTargetPoint().x);
    _data.temp_float_buffer.y = static_cast<float>(f_offset_y / _data.zoom_transition.getTargetPoint().y);
    return _data.temp_float_buffer;
}

/* -------------------------------------------------------------------------- */
/*                                  Move zoom                                 */
/* -------------------------------------------------------------------------- */
void SmoothLineChart::moveZoomTo(const float& xZoom, const float& yZoom)
{
    _data.zoom_transition.moveTo(_float_2_int(xZoom), _float_2_int(yZoom));
    // Since offset depends on zoom, kick offset again
    moveOffsetTo(_data.last_offset.x, _data.last_offset.y);
}

void SmoothLineChart::moveXZoomTo(const float& zoom)
{
    _data.zoom_transition.moveTo(_float_2_int(zoom), _data.zoom_transition.getTargetPoint().y);
    moveOffsetTo(_data.last_offset.x, _data.last_offset.y);
}

void SmoothLineChart::moveYZoomTo(const float& zoom)
{
    _data.zoom_transition.moveTo(_data.zoom_transition.getTargetPoint().x, _float_2_int(zoom));
    moveOffsetTo(_data.last_offset.x, _data.last_offset.y);
}

/* -------------------------------------------------------------------------- */
/*                                  Jump zoom                                 */
/* -------------------------------------------------------------------------- */
void SmoothLineChart::jumpZoomTo(const float& xZoom, const float& yZoom)
{
    _data.zoom_transition.jumpTo(_float_2_int(xZoom), _float_2_int(yZoom));
    jumpOffsetTo(_data.last_offset.x, _data.last_offset.y);
}

void SmoothLineChart::jumpXZoomTo(const float& zoom)
{
    _data.zoom_transition.jumpTo(_float_2_int(zoom), _data.zoom_transition.getTargetPoint().y);
    jumpOffsetTo(_data.last_offset.x, _data.last_offset.y);
}

void SmoothLineChart::jumpYZoomTo(const float& zoom)
{
    _data.zoom_transition.jumpTo(_data.zoom_transition.getTargetPoint().x, _float_2_int(zoom));
    jumpOffsetTo(_data.last_offset.x, _data.last_offset.y);
}

/* -------------------------------------------------------------------------- */
/*                                 Move offset                                */
/* -------------------------------------------------------------------------- */
void SmoothLineChart::moveOffsetTo(const float& xOffset, const float& yOffset)
{
    fpm::fixed_24_8 f_x_offset{xOffset};
    fpm::fixed_24_8 f_y_offset{yOffset};
    _data.offset_transition.moveTo(static_cast<int>(f_x_offset * _data.zoom_transition.getTargetPoint().x),
                                   static_cast<int>(f_y_offset * _data.zoom_transition.getTargetPoint().y));

    _data.last_offset.reset(xOffset, yOffset);
}

void SmoothLineChart::moveXOffsetTo(const float& offset)
{
    fpm::fixed_24_8 f_x_offset{offset};
    _data.offset_transition.moveTo(static_cast<int>(f_x_offset * _data.zoom_transition.getTargetPoint().x),
                                   _data.offset_transition.getTargetPoint().y);

    _data.last_offset.x = offset;
}

void SmoothLineChart::moveYOffsetTo(const float& offset)
{
    fpm::fixed_24_8 f_y_offset{offset};
    _data.offset_transition.moveTo(_data.offset_transition.getTargetPoint().x,
                                   static_cast<int>(f_y_offset * _data.zoom_transition.getTargetPoint().y));

    _data.last_offset.y = offset;
}

/* -------------------------------------------------------------------------- */
/*                                 Jump offset                                */
/* -------------------------------------------------------------------------- */
void SmoothLineChart::jumpOffsetTo(const float& xOffset, const float& yOffset)
{
    fpm::fixed_24_8 f_x_offset{xOffset};
    fpm::fixed_24_8 f_y_offset{yOffset};
    _data.offset_transition.jumpTo(static_cast<int>(f_x_offset * _data.zoom_transition.getTargetPoint().x),
                                   static_cast<int>(f_y_offset * _data.zoom_transition.getTargetPoint().y));

    _data.last_offset.reset(xOffset, yOffset);
}

void SmoothLineChart::jumpXOffsetTo(const float& offset)
{
    fpm::fixed_24_8 f_x_offset{offset};
    _data.offset_transition.jumpTo(static_cast<int>(f_x_offset * _data.zoom_transition.getTargetPoint().x),
                                   _data.offset_transition.getTargetPoint().y);

    _data.last_offset.x = offset;
}

void SmoothLineChart::jumpYOffsetTo(const float& offset)
{
    fpm::fixed_24_8 f_y_offset{offset};
    _data.offset_transition.jumpTo(_data.offset_transition.getTargetPoint().x,
                                   static_cast<int>(f_y_offset * _data.zoom_transition.getTargetPoint().y));

    _data.last_offset.y = offset;
}

/* -------------------------------------------------------------------------- */
/*                              Chart point apis                              */
/* -------------------------------------------------------------------------- */
void SmoothLineChart::mirrorChartPointY(Vector2D_t& chartPoint)
{
    chartPoint.y = 2 * _config.origin.y + _config.size.height - chartPoint.y;
}

const Vector2D_t& SmoothLineChart::getChartPoint(const float& rawX, const float& rawY, const bool& mirrorY)
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

    _data.temp_buffer.x = static_cast<int>(f_x);
    _data.temp_buffer.y = static_cast<int>(f_y);

    if (mirrorY)
        mirrorChartPointY(_data.temp_buffer);

    return _data.temp_buffer;
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

/* -------------------------------------------------------------------------- */
/*                                    Range                                   */
/* -------------------------------------------------------------------------- */
const float& SmoothLineChart::getZoomByRange(const float& min, const float& max, const float& target)
{
    fpm::fixed_24_8 f_min{min};
    fpm::fixed_24_8 f_max{max};
    fpm::fixed_24_8 f_target{target};
    _data.temp_float_buffer.x = static_cast<float>(f_target / (f_max - f_min));
    return _data.temp_float_buffer.x;
}

void SmoothLineChart::moveYIntoRange(const float& minY, const float& maxY)
{
    moveYZoomTo(getZoomByRange(minY, maxY, _config.size.height));
    moveYOffsetTo(-minY);
}

void SmoothLineChart::moveXIntoRange(const float& minX, const float& maxX)
{
    moveXZoomTo(getZoomByRange(minX, maxX, _config.size.width));
    moveXOffsetTo(-minX);
}
