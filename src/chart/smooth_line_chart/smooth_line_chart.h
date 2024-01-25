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
                // Since our transition is base on int, we scale the value to represent float, default 1000(.3f)
                int valueScale = 1000;
            };

        protected:
            struct Data_t
            {
                Transition2D offset_transition;
                Transition2D zoom_transition;
                TimeSize_t read_input_time_count = 0;
                TimeSize_t render_time_count = 0;
                bool is_changed = false;
                Vector2D_t temp_buffer;
                VectorFloat2D_t temp_float_buffer;
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
            const VectorFloat2D_t& getCurrentOffset();

            // Zoom
            inline Transition2D& getZoomTransition() { return _data.zoom_transition; }
            inline const VectorFloat2D_t& getCurrentZoom() { return _int_2_float(_data.zoom_transition.getValue()); }

        private:
            // Convert
            int _float_2_int(const float& value);
            const float& _int_2_float(const int& value);
            const VectorFloat2D_t& _int_2_float(const Vector2D_t& value);

        public:
            /**
             * @brief Move to target zoom smoothly.
             * Since offset depends on zoom, move or jump offset should be called again after this.
             *
             * @param xZoom
             * @param yZoom
             */
            inline void moveZoomTo(const float& xZoom, const float& yZoom)
            {
                _data.zoom_transition.moveTo(_float_2_int(xZoom), _float_2_int(yZoom));
            }
            inline void moveXZoomTo(const float& offset)
            {
                _data.zoom_transition.moveTo(_float_2_int(offset), _data.zoom_transition.getTargetPoint().y);
            }
            inline void moveYZoomTo(const float& offset)
            {
                _data.zoom_transition.moveTo(_data.zoom_transition.getTargetPoint().x, _float_2_int(offset));
            }

            /**
             * @brief Jump to target zoom without transition.
             * Since offset depends on zoom, move or jump offset should be called again after this.
             *
             * @param xZoom
             * @param yZoom
             */
            inline void jumpZoomTo(const float& xZoom, const float& yZoom)
            {
                _data.zoom_transition.jumpTo(_float_2_int(xZoom), _float_2_int(yZoom));
            }
            inline void jumpXZoomTo(const float& offset)
            {
                _data.zoom_transition.jumpTo(_float_2_int(offset), _data.zoom_transition.getTargetPoint().y);
            }
            inline void jumpYZoomTo(const float& offset)
            {
                _data.zoom_transition.jumpTo(_data.zoom_transition.getTargetPoint().x, _float_2_int(offset));
            }

            /**
             * @brief Move to target offset smoothly.
             *
             * @param xOffset
             * @param yOffset
             */
            void moveOffsetTo(const float& xOffset, const float& yOffset);
            inline void moveXOffsetTo(const float& offset)
            {
                moveOffsetTo(offset, _int_2_float(getOffsetTransition().getTargetPoint().y));
            }
            inline void moveYOffsetTo(const float& offset)
            {
                moveOffsetTo(_int_2_float(getOffsetTransition().getTargetPoint().x), offset);
            }

            /**
             * @brief Jump to target offset with on transition.
             *
             * @param xOffset
             * @param yOffset
             */
            void jumpOffsetTo(const float& xOffset, const float& yOffset);
            inline void jumpXOffsetTo(const float& offset)
            {
                jumpOffsetTo(offset, _int_2_float(getOffsetTransition().getTargetPoint().y));
            }
            inline void jumpYOffsetTo(const float& offset)
            {
                jumpOffsetTo(_int_2_float(getOffsetTransition().getTargetPoint().x), offset);
            }

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
             * @param rawX
             * @param rawY
             * @return const Vector2D_t&
             */
            const Vector2D_t& getChartPoint(const float& rawX, const float& rawY);

            /**
             * @brief Check if is the point inside of chart.
             *
             * @param chartX
             * @param chartY
             * @return true
             * @return false
             */
            bool isInChart(const int& chartX, const int& chartY);
            inline bool isInchart(const Vector2D_t& chartPoint) { return isInChart(chartPoint.x, chartPoint.y); }

            /**
             * @brief Get the zoom value from range to target.
             * zoom = (max - min) / target.
             *
             * @param minY
             * @param maxY
             * @return const float&
             */
            const float& getZoomByRange(const float& min, const float& max, const float& target);

            /**
             * @brief Move y's zoom and offset to fit the target range smoothly.
             *
             * @param minY
             * @param maxY
             */
            void moveYIntoRange(const float& minY, const float& maxY);

        public:
            virtual void onUpdate(const TimeSize_t& currentTime) {}
            virtual void onReadInput() {}
            virtual void onRender() {}
        };
    } // namespace Chart
} // namespace SmoothUIToolKit