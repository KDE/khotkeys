/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "trigger_widget_base.h"

TriggerWidgetBase::TriggerWidgetBase(KHotKeys::Trigger *trigger, QWidget *parent)
    : HotkeysWidgetIFace(parent)
    , _trigger(trigger)
{
    // Safety net to catch use-after-free. The triggers are not held or managed by us nor our parent.
    // Makes them easier to spot, unlike https://bugs.kde.org/show_bug.cgi?id=443656
    auto qObject = dynamic_cast<QObject *>(trigger);
    if (qObject) {
        connect(qObject, &QObject::destroyed, this, [this] {
            _trigger = nullptr;
        });
    }
}

TriggerWidgetBase::~TriggerWidgetBase()
{
}

#include "moc_trigger_widget_base.cpp"
