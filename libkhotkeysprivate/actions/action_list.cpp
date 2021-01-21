/*
   SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-only
*/

#include "actions.h"

#include <kconfiggroup.h>
#include <ksharedconfig.h>

namespace KHotKeys
{
ActionList::ActionList(const QString &comment_P)
    : QList<Action *>()
    , _comment(comment_P)
{
}

void ActionList::aboutToBeErased()
{
    QListIterator<Action *> it(*this);
    while (it.hasNext()) {
        it.next()->aboutToBeErased();
    }
}

const QString &ActionList::comment() const
{
    return _comment;
}

ActionList::~ActionList()
{
    while (!isEmpty()) {
        delete takeFirst();
    }
}

void ActionList::cfg_write(KConfigGroup &cfg_P) const
{
    QString save_cfg_group = cfg_P.name();
    int i = 0;
    for (ActionList::ConstIterator it = begin(); it != end(); ++it) {
        KConfigGroup group(cfg_P.config(), save_cfg_group + QString::number(i++));
        (*it)->cfg_write(group);
    }
    cfg_P.writeEntry("ActionsCount", i);
}

} // namespace KHotKeys
