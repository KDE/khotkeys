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
    CommandUrlActionWidget( KHotKeys::CommandUrlAction *action, QWidget *parent = nullptr );

    /**
     * Destructor
     */
    virtual ~CommandUrlActionWidget();

    KHotKeys::CommandUrlAction *action() Q_DECL_OVERRIDE;
    const KHotKeys::CommandUrlAction *action() const Q_DECL_OVERRIDE;

    bool isChanged() const Q_DECL_OVERRIDE;

protected:

    void doCopyFromObject() Q_DECL_OVERRIDE;
    void doCopyToObject() Q_DECL_OVERRIDE;

    Ui::CommandUrlActionWidget ui;

};


#endif /* #ifndef COMMAND_URL_ACTION_WIDGET_H */
