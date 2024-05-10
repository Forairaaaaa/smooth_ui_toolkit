/**
 * @file smooth_widget.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "smooth_widget.h"

using namespace SmoothUIToolKit::Widgets;

void SmoothWidgetBase::popOut()
{
    onPopOut();
    iterateChildren([&](WidgetBase* child) { ((SmoothWidgetBase*)child)->popOut(); });
    _smooth_base_data.is_hiding = false;
}

void SmoothWidgetBase::hide()
{
    onHide();
    iterateChildren([&](WidgetBase* child) { ((SmoothWidgetBase*)child)->hide(); });
    _smooth_base_data.is_hiding = true;
}

bool SmoothWidgetBase::isHidden()
{
    // Self check
    if (!isTransitionFinish())
        return false;
    if (!_smooth_base_data.is_hiding)
        return false;

    // Children check
    for (const auto& i : _base_data.children)
    {
        if (!((SmoothWidgetBase*)i)->isHidden())
            return false;
    }
    return true;
}

bool SmoothWidgetBase::isPoppedOut()
{
    // Self check
    if (!isTransitionFinish())
        return false;
    if (_smooth_base_data.is_hiding)
        return false;

    // Children check
    for (const auto& i : _base_data.children)
    {
        if (!((SmoothWidgetBase*)i)->isPoppedOut())
            return false;
    }
    return true;
}

bool SmoothWidgetBase::isHidding()
{
    if (_smooth_base_data.is_hiding && !isHidden())
        return true;
    return false;
}

bool SmoothWidgetBase::isPoppingOut()
{
    if (!_smooth_base_data.is_hiding && !isPoppedOut())
        return true;
    return false;
}

void SmoothWidgetBase::updateTransition(const TimeSize_t& currentTime)
{
    // Update transition
    _smooth_base_data.transition.update(currentTime);
    iterateChildren([&](WidgetBase* child) { ((SmoothWidgetBase*)child)->updateTransition(currentTime); });
}

void SmoothWidgetBase::update(const TimeSize_t& currentTime)
{
    updateTransition(currentTime);
    WidgetBase::update();
}
