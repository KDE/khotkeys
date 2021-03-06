/*
   SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-only
*/

#include "conditions/active_window_condition.h"

#include "khotkeysglobal.h"
#include "windows_handler.h"
#include "windows_helper/window_selection_list.h"

#include <KConfig>
#include <KConfigGroup>
#include <QDebug>

namespace KHotKeys
{
Active_window_condition::Active_window_condition(KConfigGroup &cfg_P, Condition_list_base *parent_P)
    : Condition(cfg_P, parent_P)
{
    KConfigGroup windowConfig(cfg_P.config(), cfg_P.name() + "Window");
    _window = new Windowdef_list(windowConfig);
    init();
    set_match();
}

Active_window_condition::Active_window_condition(Windowdef_list *window_P, Condition_list_base *parent_P)
    : Condition(parent_P)
    , _window(window_P)
{
    init();
    set_match();
}

Active_window_condition::~Active_window_condition()
{
    disconnect(windows_handler, nullptr, this, nullptr);
    delete _window;
}

void Active_window_condition::active_window_changed(WId)
{
    set_match();
}

void Active_window_condition::cfg_write(KConfigGroup &cfg_P) const
{
    base::cfg_write(cfg_P);
    KConfigGroup windowConfig(cfg_P.config(), cfg_P.name() + "Window");
    window()->cfg_write(windowConfig);
    cfg_P.writeEntry("Type", "ACTIVE_WINDOW"); // overwrites value set in base::cfg_write()
}

Active_window_condition *Active_window_condition::copy() const
{
    qDebug();
    return new Active_window_condition(window()->copy());
}

const QString Active_window_condition::description() const
{
    return i18n("Active window: ") + window()->comment();
}

void Active_window_condition::init()
{
    connect(windows_handler, SIGNAL(active_window_changed(WId)), this, SLOT(active_window_changed(WId)));
}

bool Active_window_condition::match() const
{
    return is_match;
}

void Active_window_condition::set_match()
{
    is_match = window()->match(Window_data(windows_handler->active_window()));
    updated();
}

const Windowdef_list *Active_window_condition::window() const
{
    return _window;
}

Windowdef_list *Active_window_condition::window()
{
    return _window;
}

} // namespace KHotKeys
