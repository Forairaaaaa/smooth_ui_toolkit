/**
 * @file water_wave_generator.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-03-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "water_wave_generator.h"
#include "../../utils/fpm/fixed.hpp"
#include "../../utils/fpm/math.hpp"

using namespace SmoothUIToolKit::Misc;

void WaterWaveGenerator::init(size_t waveLenght)
{
    if (waveLenght == 0)
        return;

    // Resize
    _data.wave_a_buffer.reSize(waveLenght);
    _data.wave_b_buffer.reSize(waveLenght);

    // Fill it up
    for (int i = 0; i < waveLenght; i++)
    {
        _data.wave_a_buffer.put(_wave_a_formula(i));
        _data.wave_b_buffer.put(_wave_b_formula(i));
    }
    _data.wave_x = waveLenght;
}

void WaterWaveGenerator::update()
{
    // Put wave b twice to make it faster
    _data.wave_a_buffer.put(_wave_a_formula(_data.wave_x));
    _data.wave_b_buffer.put(_wave_b_formula(_data.wave_x));
    _data.wave_b_buffer.put(_wave_b_formula(_data.wave_x));
    _data.wave_x++;
}

// Just simple sine
// https://www.desmos.com/calculator/dvzez1v6gr
int WaterWaveGenerator::_wave_a_formula(const int& x)
{
    fpm::fixed_16_16 fx{x};
    fx = fpm::sin(fx / 60) * _config.waveAScale + _config.waveAYOffet;
    return static_cast<int>(fx);
}

int WaterWaveGenerator::_wave_b_formula(const int& x)
{
    fpm::fixed_16_16 fx{x - 20};
    fx = fpm::sin(fx / 60) * _config.waveBScale + _config.waveBYOffet;
    return static_cast<int>(fx);
}
