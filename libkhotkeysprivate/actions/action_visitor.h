#ifndef ACTION_VISITOR_H
#define ACTION_VISITOR_H
/**
 * SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

namespace KHotKeys
{
class Action;
class ActionList;
class ActivateWindowAction;
class CommandUrlAction;
class DBusAction;
class KeyboardInputAction;
class MenuEntryAction;

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class ActionVisitor
{
public:
    ActionVisitor();
    virtual ~ActionVisitor();

private:
    virtual void visit(Action *) = 0 virtual void visit(ActionList *) = 0 virtual void visit(ActivateWindowAction *) = 0 virtual void visit(
        CommandUrlAction *) = 0 virtual void visit(DBusAction *) = 0 virtual void visit(KeyboardInputAction *) = 0 virtual void visit(MenuEntryAction *) = 0

        virtual void visit(Action *) const = 0 virtual void visit(ActionList *) const = 0 virtual void visit(ActivateWindowAction *)
            const = 0 virtual void visit(CommandUrlAction *) const = 0 virtual void visit(DBusAction *) const = 0 virtual void visit(
                KeyboardInputAction *) const = 0 virtual void visit(MenuEntryAction *) const = 0
}; // ActionVisitor

} // namespace KHotKeys

#endif /* ACTION_VISITOR_H */
