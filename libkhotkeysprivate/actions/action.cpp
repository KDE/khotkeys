/*
   SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-only
*/

#include "actions.h"

#include <KConfigGroup>
#include <QDebug>

namespace KHotKeys {


ActionVisitor::~ActionVisitor()
    {}


Action::Action( ActionData* data_P )
    : data( data_P )
    {
    }


Action::~Action()
    {
    }


void Action::aboutToBeErased()
    {
    // Nothing to do yet.
    }

void Action::cfg_write( KConfigGroup& cfg_P ) const
    {
    cfg_P.writeEntry( "Type", "ERROR" ); // derived classes should call with their type
    }


} // namespace KHotKeys

