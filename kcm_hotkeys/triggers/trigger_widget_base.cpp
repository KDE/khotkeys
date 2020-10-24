/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "trigger_widget_base.h"


TriggerWidgetBase::TriggerWidgetBase( KHotKeys::Trigger *trigger, QWidget *parent )
        : HotkeysWidgetIFace(parent)
         ,_trigger(trigger)
    {}

TriggerWidgetBase::~TriggerWidgetBase()
    {}

#include "moc_trigger_widget_base.cpp"
