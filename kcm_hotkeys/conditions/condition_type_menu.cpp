/* SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "condition_type_menu.h"

#include <KLocalizedString>

ConditionTypeMenu::ConditionTypeMenu(QWidget *parent)
    : QMenu(parent)
{
    addAction(i18nc("Condition type", "Active Window ..."))->setData(ACTIVE_WINDOW);
    addAction(i18nc("Condition type", "Existing Window ..."))->setData(EXISTING_WINDOW);
    addAction(i18nc("Condition type", "And"))->setData(AND);
    addAction(i18nc("Condition type", "Or"))->setData(OR);
    addAction(i18nc("Condition type", "Not"))->setData(NOT);
}

ConditionTypeMenu::~ConditionTypeMenu()
{
}

#include "moc_condition_type_menu.cpp"
