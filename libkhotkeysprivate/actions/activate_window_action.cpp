/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-only
*/

#include "actions.h"
#include "windows_handler.h"
#include "windows_helper/window_selection_list.h"

#include <KConfigGroup>
#include <KSharedConfig>
#include <QDebug>

namespace KHotKeys {


ActivateWindowActionVisitor::~ActivateWindowActionVisitor()
    {}


ActivateWindowAction::ActivateWindowAction( ActionData* data_P,
    const Windowdef_list* window_P )
    : Action( data_P ), _window( window_P )
    {
    }


void ActivateWindowAction::accept(ActionVisitor& visitor)
    {
    if (ActivateWindowActionVisitor *v = dynamic_cast<ActivateWindowActionVisitor*>(&visitor))
        {
        v->visit(*this);
        }
    else
        {
        qDebug() << "Visitor error";
        }
    }


const Windowdef_list* ActivateWindowAction::window() const
    {
    return _window;
    }


ActivateWindowAction::~ActivateWindowAction()
    {
    delete _window;
    }


void ActivateWindowAction::cfg_write( KConfigGroup& cfg_P ) const
    {
    base::cfg_write( cfg_P );
    cfg_P.writeEntry( "Type", "ACTIVATE_WINDOW" ); // overwrites value set in base::cfg_write()
    KConfigGroup windowGroup( cfg_P.config(), cfg_P.name() + "Window" );
    window()->cfg_write( windowGroup );
    }


void ActivateWindowAction::execute()
    {
    if( window()->match( windows_handler->active_window()))
        return; // is already active
    WId win_id = windows_handler->find_window( window());
    if( win_id != XCB_WINDOW_NONE )
        windows_handler->activate_window( win_id );
    }


const QString ActivateWindowAction::description() const
    {
    return i18n( "Activate window: " ) + window()->comment();
    }


Action* ActivateWindowAction::copy( ActionData* data_P ) const
    {
    return new ActivateWindowAction( data_P, window()->copy());
    }


void ActivateWindowAction::set_window_list(Windowdef_list *list)
    {
    delete _window;
    _window = list;
    }

} // namespace KHotKeys

