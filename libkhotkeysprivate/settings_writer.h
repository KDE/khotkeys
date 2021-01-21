#ifndef SETTINGS_WRITER_H
#define SETTINGS_WRITER_H
/**
 * SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
 * SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **/

#include "action_data/action_data_visitor.h"

#include <QStack>

#include "settings.h"

class KConfigBase;
class KConfigGroup;

namespace KHotKeys
{
/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class SettingsWriter : public ActionDataConstVisitor
{
public:
    SettingsWriter(const Settings *settings, ActionState state, const QString &id = QString(), bool allowMerging = false);

    void exportTo(const ActionDataBase *element, KConfigBase &config);

    void writeTo(KConfigBase &cfg);

    void visitActionDataBase(const ActionDataBase *base) Q_DECL_OVERRIDE;

    void visitActionData(const ActionData *group) Q_DECL_OVERRIDE;

    void visitActionDataGroup(const ActionDataGroup *group) Q_DECL_OVERRIDE;

    void visitGenericActionData(const Generic_action_data *data) Q_DECL_OVERRIDE;

    void visitMenuentryShortcutActionData(const MenuEntryShortcutActionData *data) Q_DECL_OVERRIDE;

    void visitSimpleActionData(const SimpleActionData *data) Q_DECL_OVERRIDE;

private:
    const Settings *_settings;

    QStack<KConfigGroup *> _stack;

    ActionState _state;

    QString _importId;

    bool _allowMerging;

    bool _export;

    // Disable copying
    SettingsWriter(const SettingsWriter &);
    SettingsWriter &operator=(const SettingsWriter &);

}; // SettingsWriter

} // namespace KHotKeys

#endif /* SETTINGS_WRITER_H */
