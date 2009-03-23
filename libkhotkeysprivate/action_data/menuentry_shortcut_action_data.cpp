/****************************************************************************

 KHotKeys
 
 Copyright (C) 1999-2001 Lubos Lunak <l.lunak@kde.org>

 Distributed under the terms of the GNU General Public License version 2.
 
****************************************************************************/

#include "menuentry_shortcut_action_data.h"

#include "action_data/action_data_visitor.h"
#include "actions/actions.h"
#include "conditions/conditions.h"

#include <kconfiggroup.h>
#include <kdebug.h>

namespace KHotKeys
{


template<> KDE_EXPORT
void Simple_action_data< ShortcutTrigger, MenuEntryAction >
    ::cfg_write( KConfigGroup& cfg_P ) const
    {
    base::cfg_write( cfg_P );
    cfg_P.writeEntry( "Type", "MENUENTRY_SHORTCUT_ACTION_DATA" );
    }


MenuEntryShortcutActionData::MenuEntryShortcutActionData( 
        ActionDataGroup* parent_P,
        const QString& name_P,
        const QString& comment_P,
        const KShortcut& shortcut_P,
        const QString& menuentry_P,
        bool enabled_P )
    : Simple_action_data< ShortcutTrigger, MenuEntryAction >(
        parent_P,
        name_P,
        comment_P,
        enabled_P )
    {
    set_action( new MenuEntryAction( this, menuentry_P ));
    set_trigger( new ShortcutTrigger( this, shortcut_P ));
    }


MenuEntryShortcutActionData::MenuEntryShortcutActionData( ActionDataGroup* parent_P,
    const QString& name_P, const QString& comment_P, bool enabled_P )
    : Simple_action_data< ShortcutTrigger, MenuEntryAction >( parent_P, name_P,
        comment_P, enabled_P )
    {
    }


MenuEntryShortcutActionData::MenuEntryShortcutActionData( KConfigGroup& cfg_P,
    ActionDataGroup* parent_P )
    : Simple_action_data< ShortcutTrigger, MenuEntryAction >( cfg_P, parent_P )
    {
    }


void MenuEntryShortcutActionData::accept(ActionDataVisitor *visitor) const
    {
    visitor->visitMenuentryShortcutActionData(this);
    }



} // namespace KHotKeys
