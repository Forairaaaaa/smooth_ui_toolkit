/**
 * @file option.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-20
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../../../core/transition4d/transition4d.h"
#include "../../base/base.h"
#include <functional>

namespace SmoothUIToolKit
{
    namespace Widgets
    {
        namespace Selector
        {
            /**
             * @brief Provide selectable option behavior abstraction
             *
             */
            class OptionBase
            {
            private:
                struct OptionBaseData_t
                {
                    bool isHovering = false;
                    bool isSelected = false;
                };
                OptionBaseData_t _option_base_data;

            public:
                inline bool isHovering() { return _option_base_data.isHovering; }
                inline void hover()
                {
                    _option_base_data.isHovering = true;
                    onHover();
                }
                inline void unHover()
                {
                    _option_base_data.isHovering = false;
                    onUnHover();
                }

                inline bool isSelected() { return _option_base_data.isSelected; }
                inline void select()
                {
                    _option_base_data.isSelected = true;
                    onSelect();
                }
                inline void unSelect()
                {
                    _option_base_data.isSelected = false;
                    onUnSelect();
                }

            public:
                virtual void onHover() {}
                virtual void onUnHover() {}
                virtual void onPressed() {}
                virtual void onReleasd() {}
                virtual void onClicked() {}
                virtual void onSelect() {}
                virtual void onUnSelect() {}
            };
        } // namespace Selector
    }     // namespace Widgets
} // namespace SmoothUIToolKit
