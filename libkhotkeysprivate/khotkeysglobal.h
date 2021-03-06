/*
    SPDX-License-Identifier: GPL-2.0-only
    SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
 */

#ifndef _KHOTKEYSGLOBAL_H_
#define _KHOTKEYSGLOBAL_H_

#define KHOTKEYS_CONFIG_FILE "khotkeysrc"

#include <KLocalizedString>

#include <QPointer>

class QObject;

namespace KHotKeys
{
class WindowsHandler;
class ShortcutsHandler;

Q_DECL_EXPORT extern QPointer<ShortcutsHandler> keyboard_handler;
extern QPointer<WindowsHandler> windows_handler;

// CHECKME hmms :(
Q_DECL_EXPORT bool khotkeys_active();
Q_DECL_EXPORT void khotkeys_set_active(bool active_P);

QString get_menu_entry_from_path(const QString &path_P);

Q_DECL_EXPORT void init_global_data(bool active_P, QObject *owner_P);

const char MENU_EDITOR_ENTRIES_GROUP_NAME[] = I18N_NOOP("Menu Editor entries");

//***************************************************************************
// Inline
//***************************************************************************

} // namespace KHotKeys

#endif
