/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef ACTION_WIDGET_BASE_H
#define ACTION_WIDGET_BASE_H

#include "hotkeys_widget_iface.h"

#include "libkhotkeysfwd.h"
#include "actions/actions.h"


/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class ActionWidgetBase : public HotkeysWidgetIFace
    {
    Q_OBJECT

public:

    /**
     * Destructor
     */
    virtual ~ActionWidgetBase();

    virtual KHotKeys::Action * action() { return _action; }
    virtual const KHotKeys::Action * action() const { return _action; }

protected:

    ActionWidgetBase( KHotKeys::Action *action, QWidget *parent = nullptr );

    KHotKeys::Action *_action;

    };

#endif /* #ifndef ACTION_WIDGET_BASE_H */

