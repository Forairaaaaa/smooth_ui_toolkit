/**
 * @file water_wave_generator.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-03-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../../core/types/types.h"
#include "../../utils/ring_buffer/ring_buffer.h"
#include <cstddef>
#include <cstdint>

namespace SmoothUIToolKit
{
    namespace Misc
    {
        /**
         * @brief  Provide two dynamic sine curves, to simulate waving water surface.
         *
         */
        class WaterWaveGenerator
        {
        public:
            struct Config_t
            {
                int waveAScale = 10;
                int waveBScale = 13;
                int waveAYOffet = 0;
                int waveBYOffet = -10;
            };

        private:
            struct Data_t
            {
                RingBuffer<int, 1> wave_a_buffer;
                RingBuffer<int, 1> wave_b_buffer;
                uint16_t wave_x = 0;
            };
            Data_t _data;
            Config_t _config;

        protected:
            virtual int _wave_a_formula(const int& x);
            virtual int _wave_b_formula(const int& x);

        public:
            void init(size_t waveLenght);
            inline Config_t& setConfig() { return _config; }

            virtual void update();
            inline RingBuffer<int, 1>& getWaveA() { return _data.wave_a_buffer; }
            inline RingBuffer<int, 1>& getWaveB() { return _data.wave_b_buffer; }
        };

    } // namespace Misc
} // namespace SmoothUIToolKit
