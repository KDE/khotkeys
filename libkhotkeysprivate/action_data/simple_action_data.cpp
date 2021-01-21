/**
 * SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
 * SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "simple_action_data.h"

#include "action_data/action_data_visitor.h"
#include "conditions/conditions.h"
#include "conditions/conditions_list.h"

#include <KConfigGroup>

namespace KHotKeys
{
SimpleActionData::SimpleActionData(ActionDataGroup *parent_P, const QString &name_P, const QString &comment_P)
    : ActionData(parent_P, name_P, comment_P, nullptr, new Condition_list("", this), nullptr)
{
}

void SimpleActionData::accept(ActionDataVisitor *visitor)
{
    visitor->visitSimpleActionData(this);
}

void SimpleActionData::accept(ActionDataConstVisitor *visitor) const
{
    visitor->visitSimpleActionData(this);
}

void SimpleActionData::doEnable()
{
    if (trigger()) {
        trigger()->enable();
        update_triggers();
    }
}

void SimpleActionData::doDisable()
{
    if (trigger()) {
        trigger()->disable();
        update_triggers();
    }
}

void SimpleActionData::set_action(Action *action_P)
{
    ActionList *tmp = new ActionList("Simple_action_data");
    tmp->append(action_P);
    set_actions(tmp);
}

void SimpleActionData::set_trigger(Trigger *trigger_P)
{
    Trigger_list *tmp = new Trigger_list("Simple_action");
    tmp->append(trigger_P);
    set_triggers(tmp);
}

const Action *SimpleActionData::action() const
{
    if (actions() == nullptr || actions()->isEmpty())
        return nullptr;
    return actions()->first();
}

Action *SimpleActionData::action()
{
    if (actions() == nullptr || actions()->isEmpty())
        return nullptr;
    return actions()->first();
}

const Trigger *SimpleActionData::trigger() const
{
    if (triggers() == nullptr || triggers()->isEmpty())
        return nullptr;

    return triggers()->first();
}

Trigger *SimpleActionData::trigger()
{
    if (triggers() == nullptr || triggers()->isEmpty())
        return nullptr;

    return triggers()->first();
}

} // namespace KHotKeys
