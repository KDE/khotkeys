/*
   SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-only
*/

#include "conditions.h"

#include <KConfigGroup>
#include <QDebug>

namespace KHotKeys
{
And_condition::And_condition(KConfigGroup &cfg_P, Condition_list_base *parent_P)
    : Condition_list_base(cfg_P, parent_P)
{
}

And_condition::And_condition(Condition_list_base *parent_P)
    : Condition_list_base(parent_P)
{
}

void And_condition::cfg_write(KConfigGroup &cfg_P) const
{
    qDebug() << description() << " with " << count() << " children";
    ;
    base::cfg_write(cfg_P);
    cfg_P.writeEntry("Type", "AND"); // overwrites value set in base::cfg_write()
}

And_condition *And_condition::copy() const
{
    And_condition *ret = new And_condition();
    for (ConstIterator it = begin(); it != end(); ++it) {
        ret->append((*it)->copy());
    }
    return ret;
}

const QString And_condition::description() const
{
    return i18nc("And_condition", "And");
}

bool And_condition::match() const
{
    for (ConstIterator it = begin(); it != end(); ++it) {
        if (!(*it)->match()) {
            return false;
        }
    }
    return true; // all true (or empty)
}

} // namespace KHotKeys
