/* SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "gesture_trigger_widget.h"

GestureTriggerWidget::GestureTriggerWidget(KHotKeys::GestureTrigger *trigger, QWidget *parent)
    : TriggerWidgetBase(trigger, parent)
{
    ui.setupUi(this);

    connect(ui.gesture, SIGNAL(changed()), this, SLOT(slotGestureHasChanged()));

    connect(ui.gesture, SIGNAL(changed()), _changedSignals, SLOT(map()));
    _changedSignals->setMapping(ui.gesture, "gesture");

    hasChanged = false;
}

GestureTriggerWidget::~GestureTriggerWidget()
{
}

void GestureTriggerWidget::doCopyFromObject()
{
    Q_ASSERT(trigger());
    ui.gesture->setPointData(trigger()->pointData(), false);
    hasChanged = false;
    return;
}

void GestureTriggerWidget::doCopyToObject()
{
    Q_ASSERT(trigger());
    hasChanged = false;
    trigger()->setPointData(ui.gesture->pointData());
    return;
}

bool GestureTriggerWidget::isChanged() const
{
    Q_ASSERT(trigger());
    return hasChanged;
}

void GestureTriggerWidget::slotGestureHasChanged()
{
    hasChanged = true;
}

KHotKeys::GestureTrigger *GestureTriggerWidget::trigger()
{
    return static_cast<KHotKeys::GestureTrigger *>(_trigger);
}

const KHotKeys::GestureTrigger *GestureTriggerWidget::trigger() const
{
    return static_cast<const KHotKeys::GestureTrigger *>(_trigger);
}

#include "moc_gesture_trigger_widget.cpp"
