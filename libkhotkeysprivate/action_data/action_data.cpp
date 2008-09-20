/****************************************************************************

 KHotKeys
 
 Copyright (C) 1999-2001 Lubos Lunak <l.lunak@kde.org>

 Distributed under the terms of the GNU General Public License version 2.
 
****************************************************************************/

#include "action_data/action_data.h"

#include "actions/actions.h"
#include "triggers/triggers.h"

#include <kconfiggroup.h>
#include <kdebug.h>


namespace KHotKeys
{


ActionData::ActionData( KConfigGroup& cfg_P, ActionDataGroup* parent_P )
    : ActionDataBase( cfg_P, parent_P )
    {
    KConfigGroup triggersGroup( cfg_P.config(), cfg_P.name() + "Triggers" );
    _triggers = new Trigger_list( triggersGroup, this );
    KConfigGroup actionsGroup( cfg_P.config(), cfg_P.name() + "Actions" );
    _actions = new ActionList( actionsGroup, this );
    }


ActionData::~ActionData()
    {
//    kDebug() << "~ActionData" << this;
    delete _triggers;
    delete _actions;
    // CHECKME jeste remove z parenta ?
    }


ActionData::ActionData( ActionDataGroup* parent_P, const QString& name_P,
    const QString& comment_P, Trigger_list* triggers_P, Condition_list* conditions_P,
    ActionList* actions_P, bool enabled_P )
    : ActionDataBase( parent_P, name_P, comment_P, conditions_P, enabled_P ),
    _triggers( triggers_P ), _actions( actions_P )
    {
    }


const Trigger_list* ActionData::triggers() const
    {
//    Q_ASSERT( _triggers != 0 );
    return _triggers;
    }


void ActionData::aboutToBeErased()
    {
    _triggers->aboutToBeErased();
    _actions->aboutToBeErased();
    }

const ActionList* ActionData::actions() const
    {
//    Q_ASSERT( _actions != 0 );
    return _actions;
    }


void ActionData::cfg_write( KConfigGroup& cfg_P ) const
    {
    ActionDataBase::cfg_write( cfg_P );

    // Write triggers if available
    if (triggers())
        {
        KConfigGroup triggersGroup( cfg_P.config(), cfg_P.name() + "Triggers" );
        triggers()->cfg_write( triggersGroup );
        }
    // Write actions if available
    if (actions())
        {
        KConfigGroup actionsGroup( cfg_P.config(), cfg_P.name() + "Actions" );
        actions()->cfg_write( actionsGroup );
        }
    }


void ActionData::execute()
    {
    for( ActionList::Iterator it = _actions->begin();
         it != _actions->end();
         ++it )
        (*it)->execute();
// CHECKME nebo nejak zpozdeni ?
    }


void ActionData::add_trigger( Trigger* trigger_P )
    {
    _triggers->append( trigger_P );
    }


void ActionData::add_triggers( Trigger_list* triggers_P )
    {
    while (!triggers_P->isEmpty())
        {
        _triggers->append( triggers_P->takeFirst() );
        }
    Q_ASSERT( triggers_P->isEmpty());
    delete triggers_P;
    }


void ActionData::set_triggers( Trigger_list* triggers_P )
    {
    Q_ASSERT( _triggers == 0 );
    _triggers = triggers_P;
    }


void ActionData::add_action( Action* action_P, Action* after_P )
    {
    int index = 0;
    for( ActionList::Iterator it = _actions->begin();
         it != _actions->end();
         ++it )
        {
        ++index;
        if( *it == after_P )
            break;
        }
    _actions->insert( index, action_P );
    }


void ActionData::add_actions( ActionList* actions_P, Action* after_P )
    {
    int index = 0;
    for( ActionList::Iterator it = _actions->begin();
         it != _actions->end();
         ++it )
        {
        ++index;
        if( *it == after_P )
            break;
        }

    while (!actions_P->empty())
        {
        // Insert the actions to _actions after removing them from actions_P
        // to prevent their deletion upon delete actions_P below.
        _actions->insert( ++index, actions_P->takeFirst() );
        }
    Q_ASSERT( actions_P->isEmpty());
    delete actions_P;
    }


void ActionData::set_actions( ActionList* actions_P )
    {
    Q_ASSERT( _actions == 0 );
    _actions = actions_P;
    }


void ActionData::update_triggers()
    {
    bool activate = conditions_match() && enabled( false );
    kDebug() << "### Update triggers: " << name() << ":" << activate;
    for( Trigger_list::Iterator it = _triggers->begin();
         it != _triggers->end();
         ++it )
        {
//        kDebug() << "Going over the triggers";
        (*it)->activate( activate );
        }
    }


} // namespace KHotKeys