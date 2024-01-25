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
                // Take zoomBase as 1, so zoom to 1/2, means zoom value goes to zoomBase/2 (by default 5000)
                int zoomBase = 10000;
            };

        protected:
            struct Data_t
            {
                Transition2D offset_transition;
                Transition2D zoom_transition;
                Vector2D_t temp_buffer;
                Vector2D_t point_buffer;
                TimeSize_t read_input_time_count = 0;
                TimeSize_t render_time_count = 0;
                bool is_changed = false;
                VectorFloat2D_t float_zoom_buffer;
            };
            Data_t _data;
            Config_t _config;

        public:
            SmoothLineChart();

            // Config
            inline void setConfig(const Config_t& cfg) { _config = cfg; }
            inline Config_t& setConfig() { return _config; }
            inline const Config_t& getConfig() { return _config; }

            // Chart
            inline const Vector2D_t& getOrigin() { return _config.origin; }
            inline void setOrigin(int x, int y) { _config.origin.x = x, _config.origin.y = y; }
            inline const Vector2D_t& getSize() { return _config.size; }
            inline void setSize(int width, int height)
            {
                _config.size.width = width;
                _config.size.height = height;
            }

            // Offset
            inline Transition2D& getOffsetTransition() { return _data.offset_transition; }
            inline Vector2D_t getOffset() { return _data.offset_transition.getValue(); }

            // Zoom
            inline Transition2D& getZoomTransition() { return _data.zoom_transition; }
            inline Vector2D_t getIntZoom() { return _data.zoom_transition.getValue(); }
            inline const VectorFloat2D_t& getFloatZoom() { return intZoom2FloatZoom(_data.zoom_transition.getValue()); }
            inline const int& getZoomBase() { return _config.zoomBase; }

        public:
            /**
             * @brief Convert float zoom into int zoom.
             *
             * @param zoom
             * @return int
             */
            int floatZoom2IntZoom(const float& floatZoom);

            /**
             * @brief Convert int zoom into float zoom.
             *
             * @param intZoom
             * @return const float&
             */
            const float& intZoom2FloatZoom(const int& intZoom);
            const VectorFloat2D_t& intZoom2FloatZoom(const Vector2D_t& intZoom);

            /**
             * @brief Move to target offset smoothly.
             *
             * @param xOffset
             * @param yOffset
             */
            inline void moveOffsetTo(int xOffset, int yOffset) { _data.offset_transition.moveTo(xOffset, yOffset); }

            /**
             * @brief Jump to target offset with on transition.
             *
             * @param xOffset
             * @param yOffset
             */
            inline void jumpOffsetTo(int xOffset, int yOffset) { _data.offset_transition.jumpTo(xOffset, yOffset); }

            /**
             * @brief Move to target float zoom smoothly.
             *
             * @param xZoom
             * @param yZoom
             */
            inline void moveFloatZoomTo(const float& xZoom, const float& yZoom)
            {
                moveIntZoomTo(floatZoom2IntZoom(xZoom), floatZoom2IntZoom(yZoom));
            }

            /**
             * @brief Move to target int zoom smoothly.
             *
             * @param xZoom
             * @param yZoom
             */
            inline void moveIntZoomTo(int xZoom, int yZoom) { _data.zoom_transition.moveTo(xZoom, yZoom); }

            /**
             * @brief Jump to target float zoom without transition.
             *
             * @param xZoom
             * @param yZoom
             */
            inline void jumpFloatZoomTo(const float& xZoom, const float& yZoom)
            {
                jumpIntZoomTo(floatZoom2IntZoom(xZoom), floatZoom2IntZoom(yZoom));
            }

            /**
             * @brief Jump to target int zoom without transition.
             *
             * @param xZoom
             * @param yZoom
             */
            inline void jumpIntZoomTo(int xZoom, int yZoom) { _data.zoom_transition.jumpTo(xZoom, yZoom); }

            /**
             * @brief Is transition finished.
             *
             * @return true
             * @return false
             */
            inline bool isFinish() { return _data.offset_transition.isFinish() && _data.zoom_transition.isFinish(); }

            /**
             * @brief Update chart.
             *
             * @param currentTime
             */
            virtual void update(const TimeSize_t& currentTime);

            /**
             * @brief Get point that applied chart's offset and zoom.
             *
             * @param rawX Raw x
             * @param rawY Raw y
             * @return const Vector2D_t& Point that applied chart's offset and zoom
             */
            const Vector2D_t& getChartPoint(const int& rawX, const int& rawY);
            inline const Vector2D_t& getChartPoint(const Vector2D_t& rawPoint) { return getChartPoint(rawPoint.x, rawPoint.y); }

            const Vector2D_t& getChartPoint(const float& rawX, const float& rawY);

            /**
             * @brief Check is the point inside of chart.
             *
             * @param chartX
             * @param chartY
             * @return true
             * @return false
             */
            bool isInChart(const int& chartX, const int& chartY);
            inline bool isInchart(const Vector2D_t& chartPoint) { return isInChart(chartPoint.x, chartPoint.y); }

            const float& getYFloatZoomByRange(const float& minY, const float& maxY);
            inline void moveYZoomToRange(const float& minY, const float& maxY)
            {
                moveIntZoomTo(getZoomTransition().getXTransition().getEndValue(),
                              floatZoom2IntZoom(getYFloatZoomByRange(minY, maxY)));
            }

        public:
            virtual void onUpdate(const TimeSize_t& currentTime) {}
            virtual void onReadInput() {}
            virtual void onRender() {}
        };
    } // namespace Chart
} // namespace SmoothUIToolKit