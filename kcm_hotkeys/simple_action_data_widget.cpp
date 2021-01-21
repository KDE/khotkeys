/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "simple_action_data_widget.h"

#include "actions/command_url_action_widget.h"
#include "actions/dbus_action_widget.h"
#include "actions/keyboard_input_action_widget.h"
#include "actions/menuentry_action_widget.h"
#include "triggers/gesture_trigger_widget.h"
#include "triggers/shortcut_trigger_widget.h"
#include "triggers/window_trigger_widget.h"

#include <QDebug>

SimpleActionDataWidget::SimpleActionDataWidget(QWidget *parent)
    : HotkeysWidgetBase(parent)
    , currentTrigger(nullptr)
    , currentAction(nullptr)
{
}

SimpleActionDataWidget::~SimpleActionDataWidget()
{
    delete currentTrigger;
    delete currentAction;
}

bool SimpleActionDataWidget::isChanged() const
{
    return (currentTrigger && currentTrigger->isChanged()) || (currentAction && currentAction->isChanged()) || Base::isChanged();
}

void SimpleActionDataWidget::doCopyFromObject()
{
    Base::doCopyFromObject();

    if (currentTrigger) {
        currentTrigger->copyFromObject();
    }

    if (currentAction) {
        currentAction->copyFromObject();
    }
}

void SimpleActionDataWidget::doCopyToObject()
{
    Base::doCopyToObject();

    if (currentTrigger) {
        currentTrigger->copyToObject();
    }

    if (currentAction) {
        currentAction->copyToObject();
    }
}

void SimpleActionDataWidget::setActionData(KHotKeys::SimpleActionData *pData)
{
    _data = pData;

    // Now go and work on the trigger
    delete currentTrigger;
    currentTrigger = nullptr;

    if (KHotKeys::Trigger *trg = data()->trigger()) {
        switch (trg->type()) {
        case KHotKeys::Trigger::ShortcutTriggerType:
            qDebug() << "1";
            currentTrigger = new ShortcutTriggerWidget(static_cast<KHotKeys::ShortcutTrigger *>(trg));
            break;

        case KHotKeys::Trigger::WindowTriggerType:
            qDebug() << "2";
            currentTrigger = new WindowTriggerWidget(static_cast<KHotKeys::WindowTrigger *>(trg));
            break;

        case KHotKeys::Trigger::GestureTriggerType:
            qDebug() << "3";
            currentTrigger = new GestureTriggerWidget(static_cast<KHotKeys::GestureTrigger *>(trg));
            break;

        default:
            qDebug() << "Unknown trigger type";
        };
    }

    if (currentTrigger) {
        connect(currentTrigger, SIGNAL(changed(bool)), this, SLOT(slotChanged()));
        extend(currentTrigger, i18n("Trigger"));
    }

    // Now go and work on the action
    delete currentAction;
    currentAction = nullptr;

    if (KHotKeys::Action *act = data()->action()) {
        switch (act->type()) {
        case KHotKeys::Action::MenuEntryActionType:
            currentAction = new MenuentryActionWidget(static_cast<KHotKeys::MenuEntryAction *>(act));
            break;

        case KHotKeys::Action::DBusActionType:
            currentAction = new DbusActionWidget(static_cast<KHotKeys::DBusAction *>(act));
            break;

        case KHotKeys::Action::CommandUrlActionType:
            currentAction = new CommandUrlActionWidget(static_cast<KHotKeys::CommandUrlAction *>(act));
            break;

        case KHotKeys::Action::KeyboardInputActionType:
            currentAction = new KeyboardInputActionWidget(static_cast<KHotKeys::KeyboardInputAction *>(act));
            break;

        default:
            qDebug() << "Unknown action type";
        };
    }

    if (currentAction) {
        connect(currentAction, SIGNAL(changed(bool)), this, SLOT(slotChanged()));
        extend(currentAction, i18n("Action"));
    }

    Base::copyFromObject();
}

#include "moc_simple_action_data_widget.cpp"
