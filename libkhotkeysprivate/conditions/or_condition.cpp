/*
   SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-only
*/

#include "conditions.h"

#include <KConfigGroup>

namespace KHotKeys {

Or_condition::Or_condition( KConfigGroup& cfg_P, Condition_list_base* parent_P )
    : Condition_list_base( cfg_P, parent_P )
    {}


Or_condition::Or_condition( Condition_list_base* parent_P )
    : Condition_list_base( parent_P )
    {}


bool Or_condition::match() const
    {
    if( count() == 0 ) // empty => ok
        return true;
    for( ConstIterator it(begin());
         it != end();
         ++it )
        if( (*it)->match()) // OR
            return true;
    return false;
    }


void Or_condition::cfg_write( KConfigGroup& cfg_P ) const
    {
    base::cfg_write( cfg_P );
    cfg_P.writeEntry( "Type", "OR" ); // overwrites value set in base::cfg_write()
    }


Or_condition* Or_condition::copy() const
    {
    Or_condition* ret = new Or_condition();
    for( ConstIterator it(begin());
         it != end();
         ++it )
        ret->append( (*it)->copy());
    return ret;
    }


const QString Or_condition::description() const
    {
    return i18nc( "Or_condition", "Or" );
    }


} // namespace KHotKeys
