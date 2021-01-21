/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "shortcut_trigger_widget.h"

#include "action_data/action_data.h"
#include "triggers/triggers.h"

#include <QKeySequence>

#include <KGlobalAccel>
#include <QDebug>

ShortcutTriggerWidget::ShortcutTriggerWidget(KHotKeys::ShortcutTrigger *trigger, QWidget *parent)
    : TriggerWidgetBase(trigger, parent)
{
    shortcut_trigger_ui.setupUi(this);

    shortcut_trigger_ui.shortcut->setCheckForConflictsAgainst(
        // Don't know why that is necessary but it doesn't compile
        // without.
        KKeySequenceWidget::ShortcutTypes(KKeySequenceWidget::GlobalShortcuts | KKeySequenceWidget::StandardShortcuts));

    connect(shortcut_trigger_ui.shortcut, SIGNAL(keySequenceChanged(QKeySequence)), _changedSignals, SLOT(map()));
    _changedSignals->setMapping(shortcut_trigger_ui.shortcut, "shortcut");

    // If the global shortcuts is changed outside of the dialog just copy the
    // new key sequencence. It doesn't matter if the user changed the sequence
    // here.
    connect(KGlobalAccel::self(), &KGlobalAccel::globalShortcutChanged, this, &ShortcutTriggerWidget::_k_globalShortcutChanged);
}

ShortcutTriggerWidget::~ShortcutTriggerWidget()
{
}

KHotKeys::ShortcutTrigger *ShortcutTriggerWidget::trigger()
{
    return static_cast<KHotKeys::ShortcutTrigger *>(_trigger);
}

const KHotKeys::ShortcutTrigger *ShortcutTriggerWidget::trigger() const
{
    return static_cast<const KHotKeys::ShortcutTrigger *>(_trigger);
}

void ShortcutTriggerWidget::doCopyFromObject()
{
    Q_ASSERT(trigger());
    shortcut_trigger_ui.shortcut->setKeySequence(trigger()->primaryShortcut());
}

void ShortcutTriggerWidget::doCopyToObject()
{
    Q_ASSERT(trigger());
    trigger()->set_key_sequence(shortcut_trigger_ui.shortcut->keySequence());
}

bool ShortcutTriggerWidget::isChanged() const
{
    Q_ASSERT(trigger());
    return QKeySequence(trigger()->primaryShortcut(), QKeySequence::PortableText) != shortcut_trigger_ui.shortcut->keySequence();
}

void ShortcutTriggerWidget::_k_globalShortcutChanged(QAction *action, const QKeySequence &seq)
{
    shortcut_trigger_ui.shortcut->setKeySequence(seq);
}

#include "moc_shortcut_trigger_widget.cpp"
