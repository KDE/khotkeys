/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "action_widget_base.h"


ActionWidgetBase::ActionWidgetBase( KHotKeys::Action *action, QWidget *parent )
        : HotkeysWidgetIFace(parent)
         ,_action(action)
    {}


ActionWidgetBase::~ActionWidgetBase()
    {}


#include "moc_action_widget_base.cpp"

