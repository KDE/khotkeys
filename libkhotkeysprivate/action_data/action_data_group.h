/*
    SPDX-License-Identifier: GPL-2.0-only
    SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
 */

#ifndef ACTION_DATA_GROUP_H
#define ACTION_DATA_GROUP_H

#include "action_data_base.h"
#include "actions/actions.h"
#include "triggers/triggers.h"

#include "QList"

class KHotkeysModel;

namespace KHotKeys
{
/**
 * A group of \c ActionDataBase objects
 *
 * # The group can contain actions or action groups.
 * # The group has its own list of conditions. These conditions apply to all children.
 */
class Q_DECL_EXPORT ActionDataGroup : public ActionDataBase
{
    Q_OBJECT

public:
    enum system_group_t {
        SYSTEM_NONE, //!< TODO
        SYSTEM_MENUENTRIES, //!< Shortcuts for menu entries.
        SYSTEM_ROOT, //!< TODO
        /* last one*/ SYSTEM_MAX, //!< End of enum marker
    }; // don't remove entries

    /**
     * Create a \c ActionDataGroup object.
     *
     * \param parent_P  A ActionDataGroup or 0. If provided this action is
     *        registered with the group.
     * \param name_P    Name for the object.
     * \param comment_P Comment for the object.
     * \param condition_P Conditions for the object or 0
     * \param system_group_t Group type
     * \param enabled_P Is the action enabled?
     */
    ActionDataGroup(ActionDataGroup *parent_P,
                    const QString &name_P = QString(),
                    const QString &comment_P = QString(),
                    Condition_list *conditions_P = nullptr,
                    system_group_t system_group_P = SYSTEM_NONE);

    virtual ~ActionDataGroup();

    /**
     * Visitor pattern
     */
    void accept(ActionDataVisitor *visitor) Q_DECL_OVERRIDE;
    void accept(ActionDataConstVisitor *visitor) const Q_DECL_OVERRIDE;

    void update_triggers() Q_DECL_OVERRIDE;

    /**
     * What kind of actions are allowed for this group?
     */
    Action::ActionTypes allowedActionTypes() const;

    /**
     * What kind of trigger are allowed for this group?
     */
    Trigger::TriggerTypes allowedTriggerTypes() const;

    /**
     * Get a shallow copy of the list of children.
     */
    const QList<ActionDataBase *> children() const;

    /**
     * Number of children.
     */
    int size() const;

    /**
     * @reimp
     */
    void aboutToBeErased() Q_DECL_OVERRIDE;

    /**
     * Is this a system group?
     *
     * @{
     */
    bool is_system_group() const;
    system_group_t system_group() const;
    void set_system_group(system_group_t group);
    //@}

    // CHECKME : Why this?
    using ActionDataBase::set_conditions; // make public

    //! Add a child to this collection
    void add_child(ActionDataBase *child_P, int position);

    //! Add a child to this collection
    void add_child(ActionDataBase *child_P);

    //! Remove a child from this collection
    void remove_child(ActionDataBase *child_P);

Q_SIGNALS:

    void stateChanged(bool isEnabled);

protected:
    //! The children
    QList<ActionDataBase *> _list;

    //! System group type
    system_group_t _system_group; // e.g. menuedit entries, can't be deleted or renamed

    void doEnable() Q_DECL_OVERRIDE;

    void doDisable() Q_DECL_OVERRIDE;
};

} // namespace KHotKeys

#endif
