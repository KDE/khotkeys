/**
 * SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
 * SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "menuentry_shortcut_action_data.h"

#include "action_data/action_data_visitor.h"
#include "conditions/conditions.h"

#include <QDebug>
#include <kconfiggroup.h>

namespace KHotKeys
{
MenuEntryShortcutActionData::MenuEntryShortcutActionData(ActionDataGroup *parent,
                                                         const QString &name,
                                                         const QString &comment,
                                                         const QKeySequence &shortcut,
                                                         const QString &menuentry)
    : base(parent, name, comment)
{
    set_action(new MenuEntryAction(this, menuentry));
    set_trigger(new ShortcutTrigger(this, shortcut));
}

MenuEntryShortcutActionData::MenuEntryShortcutActionData(ActionDataGroup *parent, const QString &name, const QString &comment)
    : base(parent, name, comment)
{
}

void MenuEntryShortcutActionData::accept(ActionDataVisitor *visitor)
{
    visitor->visitMenuentryShortcutActionData(this);
}

void MenuEntryShortcutActionData::accept(ActionDataConstVisitor *visitor) const
{
    visitor->visitMenuentryShortcutActionData(this);
}

} // namespace KHotKeys
