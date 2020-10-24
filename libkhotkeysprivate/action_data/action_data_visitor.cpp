/**
 * SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "action_data/action_data_visitor.h"

#include "action_data/action_data_base.h"

#include <QDebug>

namespace KHotKeys {

ActionDataVisitor::ActionDataVisitor()
    {}


ActionDataVisitor::~ActionDataVisitor()
    {}


void ActionDataVisitor::visitActionDataBase(ActionDataBase *action)
    {
    qDebug() << action->name();
    Q_ASSERT(false);
    }



ActionDataConstVisitor::ActionDataConstVisitor()
    {}


ActionDataConstVisitor::~ActionDataConstVisitor()
    {}


void ActionDataConstVisitor::visitActionDataBase(const ActionDataBase *action)
    {
    qDebug() << action->name();
    Q_ASSERT(false);
    }

} // KHotKeys



