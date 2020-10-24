/* SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dbus_action_widget.h"

#include <KDialogJobUiDelegate>
#include <KIO/CommandLauncherJob>

DbusActionWidget::DbusActionWidget(
    KHotKeys::DBusAction *action,
    QWidget *parent )
        : Base(action, parent)
    {
    ui.setupUi(this);

    connect(
        ui.application, SIGNAL(textChanged(QString)),
        _changedSignals, SLOT(map()) );
    _changedSignals->setMapping(ui.application, "application" );
    connect(
        ui.object, SIGNAL(textChanged(QString)),
        _changedSignals, SLOT(map()) );
    _changedSignals->setMapping(ui.object, "object" );
    connect(
        ui.function, SIGNAL(textChanged(QString)),
        _changedSignals, SLOT(map()) );
    _changedSignals->setMapping(ui.function, "function" );
    connect(
        ui.arguments, SIGNAL(textChanged(QString)),
        _changedSignals, SLOT(map()) );
    _changedSignals->setMapping(ui.arguments, "arguments" );

    connect(
        ui.launchButton, SIGNAL(clicked()),
        this, SLOT(launchDbusBrowser()) );
    connect(
        ui.execButton, SIGNAL(clicked()),
        this, SLOT(execCommand()) );
    }


DbusActionWidget::~DbusActionWidget()
    {
    }


KHotKeys::DBusAction *DbusActionWidget::action()
    {
    return static_cast<KHotKeys::DBusAction*>(_action);
    }


const KHotKeys::DBusAction *DbusActionWidget::action() const
    {
    return static_cast<const KHotKeys::DBusAction*>(_action);
    }


void DbusActionWidget::doCopyFromObject()
    {
    Q_ASSERT(action());
    ui.application->setText( action()->remote_application() );
    ui.object->setText( action()->remote_object() );
    ui.function->setText( action()->called_function() );
    ui.arguments->setText( action()->arguments() );
    }


void DbusActionWidget::doCopyToObject()
    {
    Q_ASSERT(action());
    action()->set_remote_application( ui.application->text() );
    action()->set_remote_object( ui.object->text() );
    action()->set_called_function( ui.function->text() );
    action()->set_arguments( ui.arguments->text() );
    }


void DbusActionWidget::execCommand() const
    {
    KHotKeys::DBusAction action(
        nullptr,
        ui.application->text(),
        ui.object->text(),
        ui.function->text(),
        ui.arguments->text() );

    // TODO: Error handling
    action.execute();
    }


bool DbusActionWidget::isChanged() const
    {
    Q_ASSERT(action());
    return ui.application->text() != action()->remote_application()
        || ui.object->text()      != action()->remote_object()
        || ui.function->text()    != action()->called_function()
        || ui.arguments->text()   != action()->arguments();
    }


void DbusActionWidget::launchDbusBrowser() const
    {
        auto *job = new KIO::CommandLauncherJob("qdbusviewer");
        job->setUiDelegate(new KDialogJobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, window()));
        job->start();
    }


#include "moc_dbus_action_widget.cpp"
