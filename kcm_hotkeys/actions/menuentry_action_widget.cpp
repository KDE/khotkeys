/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "menuentry_action_widget.h"

#include <KOpenWithDialog>
#include <QDebug>

MenuentryActionWidget::MenuentryActionWidget(KHotKeys::MenuEntryAction *action, QWidget *parent)
    : ActionWidgetBase(action, parent)
    , storage_id()
{
    ui.setupUi(this);

    connect(ui.applicationButton, SIGNAL(clicked()), this, SLOT(selectApplicationClicked()));

    connect(ui.application, SIGNAL(textChanged(QString)), _changedSignals, SLOT(map()));
    _changedSignals->setMapping(ui.application, "application");
}

MenuentryActionWidget::~MenuentryActionWidget()
{
}

KHotKeys::MenuEntryAction *MenuentryActionWidget::action()
{
    Q_ASSERT(dynamic_cast<KHotKeys::MenuEntryAction *>(_action));
    return static_cast<KHotKeys::MenuEntryAction *>(_action);
}

const KHotKeys::MenuEntryAction *MenuentryActionWidget::action() const
{
    Q_ASSERT(dynamic_cast<KHotKeys::MenuEntryAction *>(_action));
    return static_cast<const KHotKeys::MenuEntryAction *>(_action);
}

void MenuentryActionWidget::doCopyFromObject()
{
    Q_ASSERT(action());
    KService::Ptr service = action()->service();

    if (service) {
        ui.application->setText(service->name());
        storage_id = service->storageId();
    } else {
        ui.application->setText(QString());
        storage_id = QString();
    }
}

void MenuentryActionWidget::doCopyToObject()
{
    Q_ASSERT(action());
    action()->set_service(KService::serviceByStorageId(storage_id));
}

bool MenuentryActionWidget::isChanged() const
{
    Q_ASSERT(action());

    bool changed;

    // There could be no service set, so be careful!
    if (action()->service()) {
        changed = ui.application->text() != action()->service()->name();
    } else {
        // No service set. If the string is not empty something changed.
        changed = !ui.application->text().isEmpty();
    }

    return changed;
}

void MenuentryActionWidget::selectApplicationClicked()
{
    KOpenWithDialog dlg;
    dlg.exec();

    KService::Ptr service = dlg.service();

    if (service) {
        ui.application->setText(service->name());
        storage_id = service->storageId();
    }
}

#include "moc_menuentry_action_widget.cpp"
