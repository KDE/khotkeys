/****************************************************************************

 KHotKeys
 
 Copyright (C) 1999-2001 Lubos Lunak <l.lunak@kde.org>

 Distributed under the terms of the GNU General Public License version 2.
 
****************************************************************************/

#include "action_data_group.h"
#include "actions/actions.h"

#include <kconfiggroup.h>
#include <kdebug.h>


namespace KHotKeys
{

ActionDataGroup::ActionDataGroup(
        KConfigGroup& cfg_P,
        ActionDataGroup* parent_P)
            : ActionDataBase( cfg_P, parent_P )
              ,_list()
              ,_system_group()

    {
    unsigned int system_group_tmp = cfg_P.readEntry( "SystemGroup", 0 );

    // Correct wrong values
    if(system_group_tmp >= SYSTEM_MAX)
        {
        system_group_tmp = 0;
        }

    _system_group = static_cast< system_group_t >( system_group_tmp );
    }


ActionDataGroup::ActionDataGroup(
        ActionDataGroup* parent_P,
        const QString& name_P,
        const QString& comment_P,
        Condition_list* conditions_P,
        system_group_t system_group_P,
        bool enabled_P)
            : ActionDataBase(parent_P, name_P, comment_P, conditions_P, enabled_P)
              ,_list()
              ,_system_group(system_group_P)
    {}


ActionDataGroup::~ActionDataGroup()
    {
    qDeleteAll(_list);
    _list.clear();
    }



Action::ActionTypes ActionDataGroup::allowedActionTypes() const
    {
    switch (_system_group)
        {
        case SYSTEM_MENUENTRIES:
            return Action::MenuEntryActionType;

        default:
            return Action::AllTypes;
        }
    }


Trigger::TriggerTypes ActionDataGroup::allowedTriggerTypes() const
    {
    switch (_system_group)
        {
        case SYSTEM_MENUENTRIES:
            return Trigger::ShortcutTriggerType;

        default:
            return Trigger::AllTypes;
        }
    }



bool ActionDataGroup::is_system_group() const
    {
    return _system_group != SYSTEM_NONE;
    }


ActionDataGroup::system_group_t ActionDataGroup::system_group() const
    {
    return _system_group;
    }


void ActionDataGroup::add_child(ActionDataBase* child_P)
    {
    // Just make sure we don't get the same child twice
    Q_ASSERT(!_list.contains(child_P));
    _list.append( child_P );
    }


void ActionDataGroup::aboutToBeErased()
    {
    Q_FOREACH( ActionDataBase *child, _list)
        {
        child->aboutToBeErased();
        }
    }


const QList<ActionDataBase*> ActionDataGroup::children() const
    {
    return _list;
    }


void ActionDataGroup::remove_child( ActionDataBase* child_P )
    {
    _list.removeAll( child_P ); // is not auto-delete
    }


int ActionDataGroup::size() const
    {
    return _list.size();
    }


void ActionDataGroup::cfg_write( KConfigGroup& cfg_P ) const
    {
    kDebug() << "Writing group " << cfg_P.name();
    ActionDataBase::cfg_write( cfg_P );
    cfg_P.writeEntry( "SystemGroup", int(system_group()));
    cfg_P.writeEntry( "Type", "ACTION_DATA_GROUP" );
    }


void ActionDataGroup::update_triggers()
    {
    Q_FOREACH(ActionDataBase *child, children())
        {
        child->update_triggers();
        }
    }


} // namespace KHotKeys