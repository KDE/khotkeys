#ifndef COMMAND_URL_ACTION_WIDGET_H
#define COMMAND_URL_ACTION_WIDGET_H
/* Copyright (C) 2008 Michael Jansen <kde@michael-jansen.biz>

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
