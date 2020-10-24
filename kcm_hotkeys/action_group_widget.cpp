/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "action_group_widget.h"

#include "conditions/conditions_widget.h"

#include "action_data/action_data_group.h"

ActionGroupWidget::ActionGroupWidget( QWidget *parent )
    :   HotkeysWidgetBase(parent)
        ,_conditions(new ConditionsWidget)
    {
    extend(_conditions, i18n("Conditions"));
    connect(_conditions, SIGNAL(changed(bool)),
            SLOT(slotChanged()));
    }


ActionGroupWidget::~ActionGroupWidget()
    {
    _conditions = nullptr;
    }


void ActionGroupWidget::setActionData(KHotKeys::ActionDataGroup *group)
    {
    _data = group;

    // BUG: conditions copies twice from the original. Once in
    // setConditionsList and once because of the copyFromObject call below.
    Q_ASSERT(_conditions);
    _conditions->setConditionsList(group->conditions());

    Base::copyFromObject();
    }


void ActionGroupWidget::doCopyFromObject()
    {
    Q_ASSERT(data());
    Base::doCopyFromObject();

    Q_ASSERT(_conditions);
    _conditions->copyFromObject();
    }


void ActionGroupWidget::doCopyToObject()
    {
    Q_ASSERT(data());
    Base::doCopyToObject();

    Q_ASSERT(_conditions);
    _conditions->copyToObject();
    }


bool ActionGroupWidget::isChanged() const
    {
    return _conditions->hasChanges() || Base::isChanged();
    }


#include "moc_action_group_widget.cpp"
