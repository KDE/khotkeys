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
    ~ShortcutTriggerWidget() override;

    KHotKeys::ShortcutTrigger *trigger() override;
    const KHotKeys::ShortcutTrigger *trigger() const override;

    bool isChanged() const override;

private Q_SLOTS:

    //! Invoked if the global shortcut is changed for the corresponding
    //  shortcut trigger
    void _k_globalShortcutChanged(QAction *action, const QKeySequence &seq);

private:
    void doCopyFromObject() override;
    void doCopyToObject() override;

    Ui::ShortcutTriggerWidget shortcut_trigger_ui;
};

#endif /* #ifndef SHORTCUT_TRIGGER_WIDGET_H */
