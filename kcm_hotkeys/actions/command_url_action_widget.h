#ifndef COMMAND_URL_ACTION_WIDGET_H
#define COMMAND_URL_ACTION_WIDGET_H
/* SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "action_widget_base.h"
#include "ui_command_url_action_widget.h"

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class CommandUrlActionWidget : public ActionWidgetBase
{
    Q_OBJECT

    typedef ActionWidgetBase Base;

public:
    /**
     * Default constructor
     */
    CommandUrlActionWidget(KHotKeys::CommandUrlAction *action, QWidget *parent = nullptr);

    /**
     * Destructor
     */
    ~CommandUrlActionWidget() override;

    KHotKeys::CommandUrlAction *action() override;
    const KHotKeys::CommandUrlAction *action() const override;

    bool isChanged() const override;

protected:
    void doCopyFromObject() override;
    void doCopyToObject() override;

    Ui::CommandUrlActionWidget ui;
};

#endif /* #ifndef COMMAND_URL_ACTION_WIDGET_H */
