/**
 * @file selector.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-20
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "selelctor.h"

using namespace SmoothUIToolKit::Widgets::Selector;

SmoothUIToolKit::Widgets::WidgetBase* SelectorBase::getHoveringWidget()
{
    if (_selector_base_data.current_widget == nullptr)
        return nullptr;
    if (_selector_base_data.hovering_option_index < 0)
        return nullptr;
    return _selector_base_data.current_widget->getChildren()[_selector_base_data.hovering_option_index];
}

bool SelectorBase::isHoveringOptionSelected()
{
    auto hovering_widget = getHoveringWidget();
    if (hovering_widget == nullptr)
        return false;
    return ((OptionBase*)hovering_widget)->isSelected();
}

void SelectorBase::enter(WidgetBase* widget)
{
    if (widget == nullptr)
        return;

    // Set current widget
    _selector_base_data.current_widget = widget;
    onEnter();

    // Select first widget
    if (!_selector_base_data.current_widget->isLeaf())
        goTo(0);
}

bool SelectorBase::back()
{
    if (_selector_base_data.current_widget->isRoot())
        return false;
    _selector_base_data.current_widget = _selector_base_data.current_widget->getParent();
    onBack();
    return true;
}

void SelectorBase::goLast()
{
    if (getOptionNum() == 0)
        return;

    int new_index = _selector_base_data.hovering_option_index - 1;
    if (new_index < 0)
        new_index = _selector_base_data.move_in_loop ? getOptionNum() - 1 : 0;

    goTo(new_index);
    onGoLast();
}

void SelectorBase::goNext()
{
    if (getOptionNum() == 0)
        return;

    int new_index = _selector_base_data.hovering_option_index + 1;
    if (new_index >= getOptionNum())
        new_index = _selector_base_data.move_in_loop ? 0 : getOptionNum() - 1;

    goTo(new_index);
    onGoNext();
}

void SelectorBase::goTo(int optionIndex)
{
    if (getOptionNum() == 0)
        return;
    if (optionIndex < 0 || optionIndex > (getOptionNum() - 1))
        return;

    _selector_base_data.hovering_option_index = optionIndex;
    onGoTo();

    // Hover option
    ((OptionBase*)getHoveringWidget())->hover();
}

void SelectorBase::selectOption()
{
    auto hovering_widget = getHoveringWidget();
    if (hovering_widget == nullptr)
        return;

    ((OptionBase*)hovering_widget)->select();
    onSelectOption();
}

void SelectorBase::unSelectOption()
{
    auto hovering_widget = getHoveringWidget();
    if (hovering_widget == nullptr)
        return;

    ((OptionBase*)hovering_widget)->unSelect();
    onUnSelectOption();
}
