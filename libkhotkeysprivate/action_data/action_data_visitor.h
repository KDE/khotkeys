#ifndef ACTION_DATA_VISITOR_H
#define ACTION_DATA_VISITOR_H
/**
 * SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

namespace KHotKeys
{
class ActionData;
class ActionDataBase;
class ActionDataGroup;
class Generic_action_data;
class MenuEntryShortcutActionData;
class SimpleActionData;
template<typename T, typename A> class SimpleActionDataHelper;

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class ActionDataVisitor
{
public:
    ActionDataVisitor();

    virtual ~ActionDataVisitor();

    virtual void visitActionDataBase(ActionDataBase *base);

    virtual void visitActionData(ActionData *base) = 0;

    virtual void visitActionDataGroup(ActionDataGroup *group) = 0;

    virtual void visitGenericActionData(Generic_action_data *data) = 0;

    virtual void visitMenuentryShortcutActionData(MenuEntryShortcutActionData *data) = 0;

    virtual void visitSimpleActionData(SimpleActionData *data) = 0;

}; // ActionDataVisitor

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class ActionDataConstVisitor
{
public:
    ActionDataConstVisitor();

    virtual ~ActionDataConstVisitor();

    virtual void visitActionDataBase(const ActionDataBase *base);

    virtual void visitActionData(const ActionData *base) = 0;

    virtual void visitActionDataGroup(const ActionDataGroup *group) = 0;

    virtual void visitGenericActionData(const Generic_action_data *data) = 0;

    virtual void visitMenuentryShortcutActionData(const MenuEntryShortcutActionData *data) = 0;

    virtual void visitSimpleActionData(const SimpleActionData *data) = 0;

    template<typename T, typename A> KHotKeys::ActionDataBase *visitSimpleActionDataHelper(const KHotKeys::SimpleActionDataHelper<T, A> *object);

private:
}; // ActionDataConstVisitor

} // KHotKeys

#endif /* ACTION_DATA_VISITOR_H */
