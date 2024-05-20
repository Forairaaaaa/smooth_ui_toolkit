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
                void onGoTo() override;
            };
        } // namespace Selector
    }     // namespace Widgets
} // namespace SmoothUIToolKit
