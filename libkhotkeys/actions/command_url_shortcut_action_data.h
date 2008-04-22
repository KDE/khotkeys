/****************************************************************************

 KHotKeys

 Copyright (C) 1999-2001 Lubos Lunak <l.lunak@kde.org>

 Distributed under the terms of the GNU General Public License version 2.

****************************************************************************/

#ifndef COMMAND_URL_SHORTCUT_ACTION_DATA_H
#define COMMAND_URL_SHORTCUT_ACTION_DATA_H

#include "simple_action_data.h"


namespace KHotKeys {

class KDE_EXPORT Command_url_shortcut_action_data
    : public Simple_action_data< Shortcut_trigger, CommandUrlAction >
    {
        typedef Simple_action_data< Shortcut_trigger, CommandUrlAction > base;
    public:
        Command_url_shortcut_action_data( ActionDataGroup* parent_P, const QString& name_P,
            const QString& comment_P, bool enabled_P = true );
        Command_url_shortcut_action_data( ActionDataGroup* parent_P, const QString& name_P,
            const QString& comment_P, const KShortcut& shortcut_P, const QString& command_url_P,
            bool enabled_P = true );
        Command_url_shortcut_action_data( KConfigGroup& cfg_P, ActionDataGroup* parent_P );
    };


} // namespace KHotKeys

#endif

