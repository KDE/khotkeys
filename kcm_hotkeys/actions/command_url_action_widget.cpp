/* SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "command_url_action_widget.h"

#include <KLineEdit>

CommandUrlActionWidget::CommandUrlActionWidget(KHotKeys::CommandUrlAction *action, QWidget *parent)
    : Base(action, parent)
{
    ui.setupUi(this);

    connect(ui.command, SIGNAL(textChanged(QString)), _changedSignals, SLOT(map()));
    _changedSignals->setMapping(ui.command, "command");
}

CommandUrlActionWidget::~CommandUrlActionWidget()
{
}

KHotKeys::CommandUrlAction *CommandUrlActionWidget::action()
{
    return static_cast<KHotKeys::CommandUrlAction *>(_action);
}

const KHotKeys::CommandUrlAction *CommandUrlActionWidget::action() const
{
    return static_cast<const KHotKeys::CommandUrlAction *>(_action);
}

void CommandUrlActionWidget::doCopyFromObject()
{
    Q_ASSERT(action());
    ui.command->lineEdit()->setText(action()->command_url());
}

void CommandUrlActionWidget::doCopyToObject()
{
    Q_ASSERT(action());
    action()->set_command_url(ui.command->lineEdit()->text());
}

bool CommandUrlActionWidget::isChanged() const
{
    Q_ASSERT(action());
    return action()->command_url() != ui.command->lineEdit()->text();
}

#include "moc_command_url_action_widget.cpp"
