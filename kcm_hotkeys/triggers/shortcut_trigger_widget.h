#ifndef SHORTCUT_TRIGGER_WIDGET_H
#define SHORTCUT_TRIGGER_WIDGET_H
/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include <QAction>

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
    ShortcutTriggerWidget(KHotKeys::ShortcutTrigger *trigger, QWidget *parent = nullptr);

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
    void _k_globalShortcutChanged(QAction *action, const QKeySequence &seq);

private:

    void doCopyFromObject() Q_DECL_OVERRIDE;
    void doCopyToObject() Q_DECL_OVERRIDE;


    Ui::ShortcutTriggerWidget shortcut_trigger_ui;

};

#endif /* #ifndef SHORTCUT_TRIGGER_WIDGET_H */
