/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
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
    ~TriggerWidgetBase() override;

    virtual KHotKeys::Trigger *trigger()
    {
        return _trigger;
    }
    virtual const KHotKeys::Trigger *trigger() const
    {
        return _trigger;
    }

protected:
    TriggerWidgetBase(KHotKeys::Trigger *trigger, QWidget *parent = nullptr);

    KHotKeys::Trigger *_trigger;
};

#endif /* #ifndef TRIGGER_WIDGET_BASE_H */
