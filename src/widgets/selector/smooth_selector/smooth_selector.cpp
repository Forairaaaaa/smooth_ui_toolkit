/**
 * @file smooth_selector.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-20
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "smooth_selector.h"
#include "smooth_option.h"

using namespace SmoothUIToolKit::Widgets::Selector;

void SmoothSelector::onGoTo()
{
    // Get selected widget frame
    auto target_frame = ((SmoothOption*)getSelectedWidget())->getTransition().getTargetPoint();
    getTransition().moveTo(target_frame);
}
