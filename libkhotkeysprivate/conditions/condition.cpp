/*
   SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-only
*/

#include "conditions/conditions.h"

#include "conditions/active_window_condition.h"
#include "conditions/existing_window_condition.h"
#include "conditions/conditions_visitor.h"

#include <KConfigGroup>
#include <QDebug>

namespace KHotKeys {

Condition::Condition( Condition_list_base* parent )
    : _parent(nullptr)
    {
    if (parent)
        {
        parent->append(this);
        Q_ASSERT(_parent);
        }
    }


Condition::Condition( KConfigGroup&, Condition_list_base* parent )
    : _parent(nullptr)
    {
    if (parent)
        {
        parent->append(this);
        Q_ASSERT(_parent);
        }
    }


Condition::~Condition()
    {
    if( _parent ) _parent->removeAll( this );
    }


void Condition::cfg_write( KConfigGroup& cfg_P ) const
    {
    cfg_P.writeEntry( "Type", "ERROR" );
    }


Condition* Condition::create_cfg_read( KConfigGroup& cfg_P, Condition_list_base* parent_P )
    {
    QString type = cfg_P.readEntry( "Type" );
    if( type == "ACTIVE_WINDOW" )
        return new Active_window_condition( cfg_P, parent_P );
    if( type == "EXISTING_WINDOW" )
        return new Existing_window_condition( cfg_P, parent_P );
    if( type == "NOT" )
        return new Not_condition( cfg_P, parent_P );
    if( type == "AND" )
        return new And_condition( cfg_P, parent_P );
    if( type == "OR" )
        return new Or_condition( cfg_P, parent_P );
    qWarning() << "Unknown Condition type read from cfg file\n";
    return nullptr;
    }


const Condition_list_base* Condition::parent() const
    {
    return _parent;
    }


Condition_list_base* Condition::parent()
    {
    return _parent;
    }


void Condition::reparent(Condition_list_base *parent)
    {
    if (_parent == parent) return;

    if (_parent) _parent->removeAll(this);
    _parent = parent;
    if (_parent) _parent->append(this);
    }


void Condition::updated() const
    {
    if (!khotkeys_active() || !_parent)
        {
        return;
        }

    _parent->updated();
    }


void Condition::visit( ConditionsVisitor *visitor )
    {
    visitor->visitCondition( this );
    }


} // namespace KHotKeys
