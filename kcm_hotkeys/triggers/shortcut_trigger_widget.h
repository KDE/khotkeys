#ifndef SHORTCUT_TRIGGER_WIDGET_H
#define SHORTCUT_TRIGGER_WIDGET_H
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

#include "trigger_widget_base.h"
#include "ui_shortcut_trigger_widget.h"

class QKeySequence;

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class ShortcutTriggerWidget : public TriggerWidgetBase
    {
    Q_OBJECT

    typedef TriggerWidgetBase Base;

public:

    /**
     * Default constructor
     */
    ShortcutTriggerWidget(KHotKeys::ShortcutTrigger *trigger, QWidget *parent = NULL);

    /**
     * Destructor
     */
    virtual ~ShortcutTriggerWidget();

    KHotKeys::ShortcutTrigger *trigger() Q_DECL_OVERRIDE;
    const KHotKeys::ShortcutTrigger *trigger() const Q_DECL_OVERRIDE;


    bool isChanged() const Q_DECL_OVERRIDE;

private Q_SLOTS:

    //! Invoked if the global shortcut is changed for the corresponding
    //  shortcut trigger
    void _k_globalShortcutChanged(const QKeySequence &);

private:

    void doCopyFromObject() Q_DECL_OVERRIDE;
    void doCopyToObject() Q_DECL_OVERRIDE;


    Ui::ShortcutTriggerWidget shortcut_trigger_ui;

};

#endif /* #ifndef SHORTCUT_TRIGGER_WIDGET_H */
