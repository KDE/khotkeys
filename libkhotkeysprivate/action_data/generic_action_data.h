/****************************************************************************

 KHotKeys

 Copyright (C) 1999-2001 Lubos Lunak <l.lunak@kde.org>

 Distributed under the terms of the GNU General Public License version 2.

****************************************************************************/

#ifndef GENERIC_ACTION_DATA_H
#define GENERIC_ACTION_DATA_H

#include "action_data.h"


namespace KHotKeys {

class ActionDataGroup;

class Q_DECL_EXPORT Generic_action_data
    : public ActionData
    {
    typedef ActionData base;

    public:

        Generic_action_data(
                ActionDataGroup* parent_P,
                const QString& name_P = QString(),
                const QString& comment_P = QString(),
                Trigger_list* triggers_P = nullptr,
                Condition_list* conditions_P = nullptr,
                ActionList* actions_P = nullptr);

        ~Generic_action_data();

        /**
         * Visitor pattern
         * @reimp
         */
        void accept(ActionDataVisitor *visitor) Q_DECL_OVERRIDE;
        void accept(ActionDataConstVisitor *visitor) const Q_DECL_OVERRIDE;

        // CHECKME: Why this?
        using ActionDataBase::set_conditions; // make public
        using ActionData::add_trigger; // make public
        using ActionData::add_triggers; // make public
        using ActionData::set_triggers; // make public
        using ActionData::add_action; // make public
        using ActionData::add_actions; // make public
        using ActionData::set_actions; // make public
    };

} // namespace KHotKeys

#endif
