#ifndef MENUENTRY_SHORTCUT_ACTION_DATA_H
#define MENUENTRY_SHORTCUT_ACTION_DATA_H
/**
 * SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
 * SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "actions/actions.h"
#include "simple_action_data.h"
#include "triggers/triggers.h"

namespace KHotKeys
{
class Q_DECL_EXPORT MenuEntryShortcutActionData : public SimpleActionDataHelper<ShortcutTrigger, MenuEntryAction>
{
public:
    typedef SimpleActionDataHelper<ShortcutTrigger, MenuEntryAction> base;

    MenuEntryShortcutActionData(ActionDataGroup *parent, const QString &name = QString(), const QString &comment = QString());

    MenuEntryShortcutActionData(ActionDataGroup *parent, const QString &name, const QString &comment, const QKeySequence &shortcut, const QString &command_url);

    /**
     * Visitor pattern
     * @reimp
     */
    void accept(ActionDataVisitor *visitor) Q_DECL_OVERRIDE;
    void accept(ActionDataConstVisitor *visitor) const Q_DECL_OVERRIDE;
};

} // namespace KHotKeys

#endif /* MENUENTRY_SHORTCUT_ACTION_DATA_H */
