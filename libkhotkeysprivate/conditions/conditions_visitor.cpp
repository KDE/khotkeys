/* SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>
   SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>

   SPDX-License-Identifier: LGPL-2.0-only
*/

#include "conditions/conditions_visitor.h"
#include "conditions/conditions_list_base.h"

namespace KHotKeys {

ConditionsVisitor::ConditionsVisitor( bool recurse )
    :   _recurse(recurse)
    {}


ConditionsVisitor::~ConditionsVisitor()
    {}


} // namespace KHotKeys
