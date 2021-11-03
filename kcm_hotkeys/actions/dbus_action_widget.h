#ifndef DBUS_ACTION_WIDGET_H
#define DBUS_ACTION_WIDGET_H
/* SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "action_widget_base.h"
#include "ui_dbus_action_widget.h"

#include "actions/actions.h"

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class DbusActionWidget : public ActionWidgetBase
{
    Q_OBJECT

    typedef ActionWidgetBase Base;

public:
    /**
     * Default constructor
     */
    DbusActionWidget(KHotKeys::DBusAction *action, QWidget *parent = nullptr);

    /**
     * Destructor
     */
    ~DbusActionWidget() override;

    KHotKeys::DBusAction *action() override;
    const KHotKeys::DBusAction *action() const override;

    bool isChanged() const override;

public Q_SLOTS:

    void launchDbusBrowser() const;
    void execCommand() const;

protected:
    void doCopyFromObject() override;
    void doCopyToObject() override;

    Ui::DbusActionWidget ui;
};

#endif /* #ifndef DBUS_ACTION_WIDGET_H */
