/*
   SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-only
*/
#include "conditions/existing_window_condition.h"

#include "windows_helper/window_selection_list.h"

#include "windows_handler.h"
#include "khotkeysglobal.h"


namespace KHotKeys {

Existing_window_condition::Existing_window_condition( KConfigGroup& cfg_P, Condition_list_base* parent_P )
    : Condition( cfg_P, parent_P )
    {
    KConfigGroup windowConfig( cfg_P.config(), cfg_P.name() + "Window" );
    _window = new Windowdef_list( windowConfig );
    init();
    set_match();
    }


Existing_window_condition::Existing_window_condition( Windowdef_list* window_P,
    Condition_list_base* parent_P )
    : Condition( parent_P ), _window( window_P ), is_match( false )
    {
    init();
    set_match();
    }


Existing_window_condition::~Existing_window_condition()
    {
    disconnect( windows_handler, nullptr, this, nullptr );
    delete _window;
    }


void Existing_window_condition::cfg_write( KConfigGroup& cfg_P ) const
    {
    base::cfg_write( cfg_P );
    KConfigGroup windowConfig( cfg_P.config(), cfg_P.name() + "Window" );
    window()->cfg_write( windowConfig );
    cfg_P.writeEntry( "Type", "EXISTING_WINDOW" ); // overwrites value set in base::cfg_write()
    }


Existing_window_condition* Existing_window_condition::copy() const
    {
    return new Existing_window_condition(window()->copy());
    }


const QString Existing_window_condition::description() const
    {
    return i18n( "Existing window: " ) + window()->comment();
    }


void Existing_window_condition::init()
    {
    connect( windows_handler, SIGNAL(window_added(WId)), this, SLOT(window_added(WId)));
    connect( windows_handler, SIGNAL(window_removed(WId)), this, SLOT(window_removed(WId)));
    }


bool Existing_window_condition::match() const
    {
    return is_match;
    }


void Existing_window_condition::set_match( WId w_P )
    {
    if( w_P != None && !is_match )
        is_match = window()->match( Window_data( w_P ));
    else
        is_match = windows_handler->find_window( window()) != None;
    updated();
    }


const Windowdef_list* Existing_window_condition::window() const
    {
    return _window;
    }


Windowdef_list* Existing_window_condition::window()
    {
    return _window;
    }


void Existing_window_condition::window_added( WId w_P )
    {
    set_match( w_P );
    }


void Existing_window_condition::window_removed( WId )
    {
    set_match();
    }


} // namespace KHotKeys
