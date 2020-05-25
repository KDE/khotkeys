/*
   Copyright (C) 1999-2001 Lubos Lunak <l.lunak@kde.org>
   Copyright (C) 2008 Michael Jansen <kde@michael-jansen.biz>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "actions/actions.h"
#include "action_data/action_data.h"

#include <KAuthorized>
#include <KConfigGroup>
#include <KDialogJobUiDelegate>
#include <KIO/ApplicationLauncherJob>
#include <KIO/CommandLauncherJob>
#include <KRun>
#include <KService>
#include <KUriFilter>

#include <QApplication>
#include <QDebug>
#include <QUrl>

namespace KHotKeys {

CommandUrlActionVisitor::~CommandUrlActionVisitor()
    {}


CommandUrlAction::CommandUrlAction( ActionData* data_P, const QString& command_url_P )
    : Action( data_P ), _command_url( command_url_P )
    {
    }


QString CommandUrlAction::command_url() const
    {
    return _command_url;
    }


void CommandUrlAction::accept(ActionVisitor& visitor)
    {
    if (CommandUrlActionVisitor *v = dynamic_cast<CommandUrlActionVisitor*>(&visitor))
        {
        v->visit(*this);
        }
    else
        {
        qDebug() << "Visitor error";
        }
    }


void CommandUrlAction::cfg_write( KConfigGroup& cfg_P ) const
    {
    base::cfg_write( cfg_P );
    cfg_P.writeEntry( "CommandURL", command_url());
    cfg_P.writeEntry( "Type", "COMMAND_URL" ); // overwrites value set in base::cfg_write()
    }


Action* CommandUrlAction::copy( ActionData* data_P ) const
    {
    return new CommandUrlAction( data_P, command_url());
    }


const QString CommandUrlAction::description() const
    {
    return i18n( "Command/URL : " ) + command_url();
    }


void CommandUrlAction::execute()
    {
    if( command_url().isEmpty())
        return;
    new KRun(QUrl(command_url()), QApplication::activeWindow());
    }


void CommandUrlAction::set_command_url( const QString &command )
    {
    _command_url = command;
    }

} // namespace KHotKeys
