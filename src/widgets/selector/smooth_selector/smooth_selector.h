/**
 * @file smooth_selector.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-20
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../../smooth_widget/smooth_widget.h"
#include "../base/selelctor.h"

namespace SmoothUIToolKit
{
    namespace Widgets
    {
        namespace Selector
        {
            class SmoothSelector : public SmoothWidgetBase, public SelectorBase
            {
            public:
                // Override to fit new class structure

                bool isHoveringOptionSelected() override;

                void selectOption() override;
                
                void unSelectOption() override;

                /**
                 * @brief Override to add option frame matching
                 *
                 */
                virtual void onGoTo() override;

                /**
                 * @brief Move to option with transition
                 *
                 * @param optionIndex
                 */
                virtual void moveTo(int optionIndex);

                /**
                 * @brief Jump to option without transition
                 *
                 * @param optionIndex
                 */
                virtual void jumpTo(int optionIndex);

            public:
                virtual void onMoveTo() {}
                virtual void onJumpTo() {}
            };
        } // namespace Selector
    }     // namespace Widgets
} // namespace SmoothUIToolKit
