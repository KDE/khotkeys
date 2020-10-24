/* SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "keyboard_input_action_widget.h"

#include <QDebug>

KeyboardInputActionWidget::KeyboardInputActionWidget(
        KHotKeys::KeyboardInputAction *action,
        QWidget *parent)
    :   Base( action, parent )
    {
    ui.setupUi(this);

    connect(
        ui.input, SIGNAL(textChanged()),
        _changedSignals, SLOT(map()) );
    _changedSignals->setMapping(ui.input, "input" );

    connect(
            ui.windowdef_list, SIGNAL(changed(bool)),
        _changedSignals, SLOT(map()) );
    _changedSignals->setMapping(ui.windowdef_list, "windowdef_list" );

    connect(
            ui.active_radio, SIGNAL(clicked(bool)),
        _changedSignals, SLOT(map()) );
    _changedSignals->setMapping(ui.active_radio, "active_radio" );

    connect(
            ui.action_radio, SIGNAL(clicked(bool)),
        _changedSignals, SLOT(map()) );
    _changedSignals->setMapping(ui.action_radio, "action_radio" );

    connect(
            ui.specific_radio, SIGNAL(clicked(bool)),
        _changedSignals, SLOT(map()) );
    _changedSignals->setMapping(ui.specific_radio, "specific_radio" );
    }



KeyboardInputActionWidget::~KeyboardInputActionWidget()
    {
    }


KHotKeys::KeyboardInputAction *KeyboardInputActionWidget::action()
    {
    Q_ASSERT(dynamic_cast<KHotKeys::KeyboardInputAction*>(_action));
    return static_cast<KHotKeys::KeyboardInputAction*>(_action);
    }


const KHotKeys::KeyboardInputAction *KeyboardInputActionWidget::action() const
    {
    Q_ASSERT(dynamic_cast<KHotKeys::KeyboardInputAction*>(_action));
    return static_cast<const KHotKeys::KeyboardInputAction*>(_action);
    }


void KeyboardInputActionWidget::doCopyFromObject()
    {
    Q_ASSERT(action());
    ui.input->setText(action()->input());
    ui.windowdef_list->setWindowDefinitions(action()->dest_window());
    ui.windowdef_list->copyFromObject();

    switch (action()->destination())
        {
        case KHotKeys::KeyboardInputAction::SpecificWindow:
            ui.specific_radio->setChecked(true);
            break;

        case KHotKeys::KeyboardInputAction::ActiveWindow:
            ui.active_radio->setChecked(true);
            break;

        case KHotKeys::KeyboardInputAction::ActionWindow:
            ui.action_radio->setChecked(true);
            break;

        default:
            Q_ASSERT(false);
            ui.action_radio->setChecked(true);
        }

    }


void KeyboardInputActionWidget::doCopyToObject()
    {
    Q_ASSERT(action());
    action()->setInput(ui.input->toPlainText());
    if (ui.action_radio->isChecked())
        {
        action()->setDestination(KHotKeys::KeyboardInputAction::ActionWindow);
        action()->dest_window()->clear();
        }
    else if (ui.active_radio->isChecked())
        {
        action()->setDestination(KHotKeys::KeyboardInputAction::ActiveWindow);
        action()->dest_window()->clear();
        }
    else
        {
        action()->setDestination(KHotKeys::KeyboardInputAction::SpecificWindow);
        ui.windowdef_list->copyToObject();
        }
    }


bool KeyboardInputActionWidget::isChanged() const
    {
    Q_ASSERT(action());

    if (ui.input->toPlainText() != action()->input()) return true;

    switch (action()->destination())
        {
        case KHotKeys::KeyboardInputAction::ActionWindow:
            return !ui.action_radio->isChecked();

        case KHotKeys::KeyboardInputAction::ActiveWindow:
            return !ui.active_radio->isChecked();

        case KHotKeys::KeyboardInputAction::SpecificWindow:
            return !ui.specific_radio->isChecked()
                || ui.windowdef_list->isChanged();
        }

    return false;
    }

#include "moc_keyboard_input_action_widget.cpp"
