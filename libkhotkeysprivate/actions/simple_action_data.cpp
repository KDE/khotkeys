/****************************************************************************

 KHotKeys
 
 Copyright (C) 1999-2001 Lubos Lunak <l.lunak@kde.org>

 Distributed under the terms of the GNU General Public License version 2.
 
****************************************************************************/

#include "action_data.h"
#include "actions.h"

#include <kconfiggroup.h>


namespace KHotKeys
{


// Dbus_shortcut_action_data

template<> KDE_EXPORT
void Simple_action_data< Shortcut_trigger, Dbus_action >
    ::cfg_write( KConfigGroup& cfg_P ) const
    {
    base::cfg_write( cfg_P );
    cfg_P.writeEntry( "Type", "DBUS_SHORTCUT_ACTION_DATA" );
    }

// Keyboard_input_shortcut_action_data

template<> KDE_EXPORT
void Simple_action_data< Shortcut_trigger, Keyboard_input_action >
    ::cfg_write( KConfigGroup& cfg_P ) const
    {
    base::cfg_write( cfg_P );
    cfg_P.writeEntry( "Type", "KEYBOARD_INPUT_SHORTCUT_ACTION_DATA" );
    }

// Activate_window_shortcut_action_data

template<> KDE_EXPORT
void Simple_action_data< Shortcut_trigger, Activate_window_action >
    ::cfg_write( KConfigGroup& cfg_P ) const
    {
    base::cfg_write( cfg_P );
    cfg_P.writeEntry( "Type", "ACTIVATE_WINDOW_SHORTCUT_ACTION_DATA" );
    }

} // namespace KHotKeys