/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef MENUENTRY_ACTION_WIDGET_H
#define MENUENTRY_ACTION_WIDGET_H

#include "action_widget_base.h"
#include "ui_menuentry_action_widget.h"

#include "libkhotkeysfwd.h"

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class MenuentryActionWidget : public ActionWidgetBase
{
    Q_OBJECT

    typedef ActionWidgetBase Base;

public:
    /**
     * Default constructor
     */
    MenuentryActionWidget(KHotKeys::MenuEntryAction *action, QWidget *parent = nullptr);

    /**
     * Destructor
     */
    ~MenuentryActionWidget() override;

    KHotKeys::MenuEntryAction *action() override;
    const KHotKeys::MenuEntryAction *action() const override;

    bool isChanged() const override;

public Q_SLOTS:

    void selectApplicationClicked();

protected:
    void doCopyFromObject() override;
    void doCopyToObject() override;

    QString storage_id;

    Ui::MenuentryActionWidget ui;
};

#endif /* #ifndef MENUENTRY_ACTION_WIDGET_H */
