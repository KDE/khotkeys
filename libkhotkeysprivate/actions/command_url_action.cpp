/*
   SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-only
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
#include <kworkspace.h>

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
    qDebug();
    if( command_url().isEmpty())
        return;
    KUriFilterData uri;
    QString cmd = command_url();
    static bool sm_ready = false;
    if( !sm_ready )
        {
        KWorkSpace::propagateSessionManager();
        sm_ready = true;
        }
//    int space_pos = command_url().find( ' ' );
//    if( command_url()[ 0 ] != '\'' && command_url()[ 0 ] != '"' && space_pos > -1
//        && command_url()[ space_pos - 1 ] != '\\' )
//        cmd = command_url().left( space_pos ); // get first 'word'
    uri.setData( cmd );
    KUriFilter::self()->filterUri( uri );
    if( uri.uri().isLocalFile() && !uri.uri().hasFragment() )
        cmd = uri.uri().toLocalFile();
    else
        cmd = uri.uri().url();
    switch( uri.uriType())
        {
        case KUriFilterData::LocalFile:
        case KUriFilterData::LocalDir:
        case KUriFilterData::NetProtocol:
        case KUriFilterData::Help:
            {
            ( void ) new KRun( uri.uri(),0L);
          break;
            }
        case KUriFilterData::Executable:
            {
            if (!KAuthorized::authorizeKAction("shell_access"))
                return;
            if( !uri.hasArgsAndOptions())
                {
                KService::Ptr service = KService::serviceByDesktopName( cmd );
                if( service )
                    {
                    auto *job = new KIO::ApplicationLauncherJob(service);
                    job->setUiDelegate(new KDialogJobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, nullptr));
                    job->start();
                  break;
                    }
                }
            // fall though
            }
        case KUriFilterData::Shell:
            {
            if (!KAuthorized::authorizeKAction("shell_access"))
                return;
            const QString exec = cmd + ( uri.hasArgsAndOptions() ? uri.argsAndOptions() : QString() );
            auto *job = new KIO::CommandLauncherJob(exec);
            job->setUiDelegate(new KDialogJobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, nullptr));
            job->setExecutable(cmd);
            job->setIcon(uri.iconName());
            job->start();
          break;
            }
        default: // error
          return;
        }
    }


void CommandUrlAction::set_command_url( const QString &command )
    {
    _command_url = command;
    }

} // namespace KHotKeys
