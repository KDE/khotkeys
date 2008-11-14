/*
   Copyright (C) 2008 Michael Jansen <kde@michael-jansen.biz>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/
#ifndef TRIGGER_WIDGET_BASE_H
#define TRIGGER_WIDGET_BASE_H

#include "hotkeys_widget_iface.h"

#include "libkhotkeysfwd.h"
#include "triggers/triggers.h"


/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class TriggerWidgetBase : public HotkeysWidgetIFace
    {
    Q_OBJECT

public:

    /**
     * Default constructor
     */

    /**
     * Destructor
     */
    virtual ~TriggerWidgetBase();

    virtual KHotKeys::Trigger * trigger() { return _trigger; }
    virtual const KHotKeys::Trigger * trigger() const { return _trigger; }

protected:

    TriggerWidgetBase( KHotKeys::Trigger *trigger, QWidget *parent = 0 );

    KHotKeys::Trigger *_trigger;

    };

#endif /* #ifndef TRIGGER_WIDGET_BASE_H */
