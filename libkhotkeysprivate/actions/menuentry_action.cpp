/*
   SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-only
*/

#include "action_data/action_data.h"
#include "actions.h"

#include <KConfigGroup>
#include <KMessageBox>
#include <KRun>
#include <QDebug>
#include <QUrl>

namespace KHotKeys
{
MenuEntryActionVisitor::~MenuEntryActionVisitor()
{
}

MenuEntryAction::MenuEntryAction(ActionData *data_P, const QString &menuentry_P)
    : CommandUrlAction(data_P, menuentry_P)
{
}

void MenuEntryAction::accept(ActionVisitor &visitor)
{
    if (MenuEntryActionVisitor *v = dynamic_cast<MenuEntryActionVisitor *>(&visitor)) {
        v->visit(*this);
    } else {
        qDebug() << "Visitor error";
    }
}

void MenuEntryAction::cfg_write(KConfigGroup &cfg_P) const
{
    base::cfg_write(cfg_P);
    cfg_P.writeEntry("Type", "MENUENTRY"); // overwrites value set in base::cfg_write()
}

KService::Ptr MenuEntryAction::service() const
{
    if (!_service) {
        const_cast<MenuEntryAction *>(this)->_service = KService::serviceByStorageId(command_url());
    }
    return _service;
}

void MenuEntryAction::set_service(KService::Ptr service)
{
    _service = service;
    if (service) {
        set_command_url(service->storageId());
    } else {
        set_command_url(QString());
    }
}

void MenuEntryAction::execute()
{
    if (!service()) {
        KMessageBox::sorry(nullptr, i18n("No service configured."), i18n("Input Action: %1", data->comment()));
        return;
    }

    if (!KRun::run(*service(), {}, nullptr)) {
        KMessageBox::sorry(nullptr, i18n("Failed to start service '%1'.", service()->name()), i18n("Input Action: %1", data->comment()));
        return;
    }
}

Action *MenuEntryAction::copy(ActionData *data_P) const
{
    return new MenuEntryAction(data_P, command_url());
}

const QString MenuEntryAction::description() const
{
    return i18n("Menu entry: ") + (service() ? service()->comment() : QString());
}

} // namespace KHotKeys
