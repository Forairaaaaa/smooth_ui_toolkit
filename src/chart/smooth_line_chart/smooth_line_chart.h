/**
 * @file smooth_line_chart.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-15
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../../core/transition2d/transition2d.h"
#include "../../core/types/types.h"

namespace SmoothUIToolKit
{
    namespace Chart
    {
        // Take 1000 as 1, 500 as 1/2, 1500 as 3/2
        constexpr int ZoomBase = 1000;

        /**
         * @brief Line chart with smooth xy offset and zoom.
         *
         */
        class SmoothLineChart
        {
        public:
            struct Config_t
            {
                // Chart origin point
                Vector2D_t origin;
                // Chart size
                Vector2D_t size;
                // Interval of onReadInput() callback
                TimeSize_t readInputInterval = 20;
                // Interval of onRender() callback
                TimeSize_t renderInterval = 15;
            };

        protected:
            struct Data_t
            {
                Transition2D offset_transition;
                Transition2D zoom_transition;
                Vector2D_t temp_buffer;
                Vector2D_t result_buffer;
                TimeSize_t read_input_time_count = 0;
                TimeSize_t render_time_count = 0;
                bool is_changed = false;
            };
            Data_t _data;
            Config_t _config;

        public:
            SmoothLineChart();

            inline void setConfig(const Config_t& cfg) { _config = cfg; }
            inline Config_t& setConfig() { return _config; }
            inline const Config_t& getConfig() { return _config; }

            inline const Vector2D_t& getOrigin() { return _config.origin; }
            inline void setOrigin(int x, int y) { _config.origin.x = x, _config.origin.y = y; }
            inline const Vector2D_t& getSize() { return _config.size; }
            inline void setSize(int width, int height)
            {
                _config.size.width = width;
                _config.size.height = height;
            }

            inline Transition2D& getOffsetTransition() { return _data.offset_transition; }
            inline Transition2D& getZoomTransition() { return _data.zoom_transition; }

            inline Vector2D_t getOffset() { return _data.offset_transition.getValue(); }
            inline Vector2D_t getZoom() { return _data.zoom_transition.getValue(); }

        public:
            inline void moveOffsetTo(int xOffset, int yOffset) { _data.offset_transition.moveTo(xOffset, yOffset); }
            inline void jumpOffsetTo(int xOffset, int yOffset) { _data.offset_transition.jumpTo(xOffset, yOffset); }
            inline void moveZoomTo(int xZoom, int yZoom) { _data.zoom_transition.moveTo(xZoom, yZoom); }
            inline void jumpZoomTo(int xZoom, int yZoom) { _data.zoom_transition.jumpTo(xZoom, yZoom); }
            inline bool isFinish() { return _data.offset_transition.isFinish() && _data.zoom_transition.isFinish(); }
            virtual void update(const TimeSize_t& currentTime);

            /**
             * @brief Get the point that map into chart
             *
             * @param rawX Raw x
             * @param rawY Raw y
             * @return const Vector2D_t& Point that applied chart's offset and zoom
             */
            const Vector2D_t& getChartPoint(int rawX, int rawY);
            inline const Vector2D_t& getChartPoint(Vector2D_t rawPoint) { return getChartPoint(rawPoint.x, rawPoint.y); }

            /**
             * @brief Check is the point inside of chart
             *
             * @param chartX
             * @param chartY
             * @return true
             * @return false
             */
            bool isInChart(const int& chartX, const int& chartY);
            inline bool isInchart(const Vector2D_t& chartPoint) { return isInChart(chartPoint.x, chartPoint.y); }

        public:
            virtual void onUpdate(const TimeSize_t& currentTime) {}
            virtual void onReadInput() {}
            virtual void onRender() {}
        };
    } // namespace Chart
} // namespace SmoothUIToolKit