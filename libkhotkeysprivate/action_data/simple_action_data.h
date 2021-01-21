/*
    SPDX-License-Identifier: GPL-2.0-only
    SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
 */

#ifndef SIMPLE_ACTION_DATA_H
#define SIMPLE_ACTION_DATA_H

#include "action_data/action_data.h"

#include "actions/actions.h"
#include "triggers/triggers.h"

namespace KHotKeys
{
class Q_DECL_EXPORT SimpleActionData : public ActionData
{
    typedef ActionData base;

public:
    SimpleActionData(ActionDataGroup *parent_P, const QString &name_P = QString(), const QString &comment_P = QString());

    /**
     * Visitor pattern
     * @reimp
     */
    void accept(ActionDataVisitor *visitor) override;
    void accept(ActionDataConstVisitor *visitor) const override;

    //! The action associated with this hotkey
    virtual const Action *action() const;
    virtual Action *action();

    //! The trigger for this hotkey
    virtual const Trigger *trigger() const;
    virtual Trigger *trigger();

    void set_action(Action *action_P);
    void set_trigger(Trigger *trigger_P);

protected:
    void doEnable() override;

    void doDisable() override;

}; // class SimpleActionData

/**
 * A template adding convenience methods to SimpleActionData.
 */
template<typename T, typename A> class Q_DECL_EXPORT SimpleActionDataHelper : public SimpleActionData
{
    typedef SimpleActionData base;

public:
    SimpleActionDataHelper(ActionDataGroup *parent_P, const QString &name_P, const QString &comment_P)
        : base(parent_P, name_P, comment_P)
    {
    }

    //! The action associated with this hotkey
    const A *action() const override;
    A *action() override;

    //! The trigger for this hotkey
    const T *trigger() const override;
    T *trigger() override;

    void set_action(Action *action_P);
    void set_trigger(Trigger *trigger_P);
};

// ==========================================================================
// TEMPLATE METHOD DEFINITIONS

template<typename T, typename A> void SimpleActionDataHelper<T, A>::set_action(Action *action_P)
{
    Q_ASSERT(dynamic_cast<A *>(action_P));
    base::set_action(action_P);
}

template<typename T, typename A> void SimpleActionDataHelper<T, A>::set_trigger(Trigger *trigger_P)
{
    Q_ASSERT(dynamic_cast<T *>(trigger_P));
    base::set_trigger(trigger_P);
}

template<typename T, typename A> const A *SimpleActionDataHelper<T, A>::action() const
{
    if (actions() == nullptr || actions()->isEmpty())
        return nullptr;
    return dynamic_cast<const A *>(actions()->first());
}

template<typename T, typename A> A *SimpleActionDataHelper<T, A>::action()
{
    if (actions() == nullptr || actions()->isEmpty())
        return nullptr;
    return dynamic_cast<A *>(actions()->first());
}

template<typename T, typename A> const T *SimpleActionDataHelper<T, A>::trigger() const
{
    if (triggers() == nullptr || triggers()->isEmpty())
        return nullptr;
    return dynamic_cast<const T *>(triggers()->first());
}

template<typename T, typename A> T *SimpleActionDataHelper<T, A>::trigger()
{
    if (triggers() == nullptr || triggers()->isEmpty())
        return nullptr;
    return dynamic_cast<T *>(triggers()->first());
}

} // namespace KHotKeys

#endif
