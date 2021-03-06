/*
    SPDX-License-Identifier: GPL-2.0-only
    SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
 */

#ifndef _ACTIONS_H_
#define _ACTIONS_H_

#include <QList>
#include <QTimer>

#include <KService>

class KConfig;
class KConfigGroup;

#include "khotkeysglobal.h"

namespace KHotKeys
{
class ActionData;
class Windowdef_list;

class ActionVisitor
{
public:
    virtual ~ActionVisitor() = 0;
};

// this one is a base for all "real" resulting actions, e.g. running a command,
// ActionData instances usually contain at least one Action
class Q_DECL_EXPORT Action
{
    Q_DISABLE_COPY(Action)

public:
    /**
     * A enum for all possible action types.
     *
     * @see type()
     */
    enum ActionType {
        ActivateWindowActionType = 0x01, //!< @see ActivateWindowAction
        CommandUrlActionType = 0x02, //!< @see CommandUrlAction
        DBusActionType = 0x04, //!< @see DBusAction
        KeyboardInputActionType = 0x08, //!< @see KeyboardInputAction
        MenuEntryActionType = 0x10, //!< @see MenuEntryAction
        ActionListType = 0x11, //!< @see ActionList
        AllTypes = 0xEF, //!< All types. For convenience
    };

    Q_DECLARE_FLAGS(ActionTypes, ActionType)

    /**
     * Create a action
     */
    Action(ActionData *data_P);

    virtual ~Action();

    /**
     * Acyclic visitor pattern
     */
    virtual void accept(ActionVisitor &) = 0;

    /**
     * Execute the action.
     */
    virtual void execute() = 0;

    /**
     * Have a look what's inside.
     *
     * @return the type of the action.
     */
    virtual ActionType type() = 0;

    /**
     * Returns a short descriptions of the action.
     *
     * The description is generated and can't be set.
     *
     * @return a description for this action
     */
    virtual const QString description() const = 0;

    /**
     * Write the actions configuration to @p cfg_P.
     */
    virtual void cfg_write(KConfigGroup &cfg_P) const;

    /**
     * Return a copy of the action.
     *
     * This is a real deep copy.
     */
    virtual Action *copy(ActionData *data_P) const = 0;

    /**
     * The action is about to be erased permanently
     */
    virtual void aboutToBeErased();

protected:
    /**
     * The action data corresponding to this action.
     */
    ActionData *const data;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Action::ActionTypes)

class Q_DECL_EXPORT ActionList : public QList<Action *>
{
    Q_DISABLE_COPY(ActionList)

public:
    ActionList(const QString &comment = QString());

    ~ActionList();
    void cfg_write(KConfigGroup &cfg_P) const;
    //! Some convenience typedef
    typedef QList<Action *>::Iterator Iterator;
    typedef QList<Action *>::ConstIterator ConstIterator;
    const QString &comment() const;

    /**
     * @reimp
     */
    void aboutToBeErased();

private:
    QString _comment;
};

class CommandUrlAction;
class CommandUrlActionVisitor
{
public:
    virtual ~CommandUrlActionVisitor();
    virtual void visit(CommandUrlAction &) = 0;
};

class Q_DECL_EXPORT CommandUrlAction : public Action
{
    typedef Action base;

public:
    CommandUrlAction(ActionData *data_P, const QString &command_url_P = QString());
    void cfg_write(KConfigGroup &cfg_P) const Q_DECL_OVERRIDE;
    void execute() Q_DECL_OVERRIDE;
    const QString description() const Q_DECL_OVERRIDE;

    //! The command url to trigger
    void set_command_url(const QString &command_url);
    QString command_url() const;

    ActionType type() Q_DECL_OVERRIDE
    {
        return CommandUrlActionType;
    }
    Action *copy(ActionData *data_P) const Q_DECL_OVERRIDE;

    /**
     * Acyclic visitor pattern
     */
    void accept(ActionVisitor &) Q_DECL_OVERRIDE;

private:
    QString _command_url;
};

class MenuEntryAction;
class MenuEntryActionVisitor
{
public:
    virtual ~MenuEntryActionVisitor();
    virtual void visit(MenuEntryAction &) = 0;
};

class Q_DECL_EXPORT MenuEntryAction : public CommandUrlAction
{
    typedef CommandUrlAction base;

public:
    MenuEntryAction(ActionData *data_P, const QString &menuentry_P = QString());
    void cfg_write(KConfigGroup &cfg_P) const Q_DECL_OVERRIDE;
    void execute() Q_DECL_OVERRIDE;

    // The service we trigger
    KService::Ptr service() const;
    void set_service(KService::Ptr);

    const QString description() const Q_DECL_OVERRIDE;
    Action *copy(ActionData *data_P) const Q_DECL_OVERRIDE;
    ActionType type() Q_DECL_OVERRIDE
    {
        return Action::MenuEntryActionType;
    }

    /**
     * Acyclic visitor pattern
     */
    void accept(ActionVisitor &) Q_DECL_OVERRIDE;

private:
    KService::Ptr _service;
};

class DBusAction;
class DBusActionVisitor
{
public:
    virtual ~DBusActionVisitor();
    virtual void visit(DBusAction &) = 0;
};

class Q_DECL_EXPORT DBusAction : public Action
{
    typedef Action base;

public:
    DBusAction(ActionData *data_P,
               const QString &app_P = QString(),
               const QString &obj_P = QString(),
               const QString &call_P = QString(),
               const QString &args_P = QString());

    void cfg_write(KConfigGroup &cfg_P) const Q_DECL_OVERRIDE;
    void execute() Q_DECL_OVERRIDE;
    const QString remote_application() const;
    const QString remote_object() const;
    const QString called_function() const;
    const QString arguments() const;

    void set_remote_application(const QString &application);
    void set_remote_object(const QString &object);
    void set_called_function(const QString &function);
    void set_arguments(const QString &args);

    const QString description() const Q_DECL_OVERRIDE;
    Action *copy(ActionData *data_P) const Q_DECL_OVERRIDE;
    ActionType type() Q_DECL_OVERRIDE
    {
        return DBusActionType;
    }

    /**
     * Acyclic visitor pattern
     */
    void accept(ActionVisitor &) Q_DECL_OVERRIDE;

private:
    QString _application; // CHECKME QCString ?
    QString _object;
    QString _function;
    QString _arguments;
};

class KeyboardInputAction;
class KeyboardInputActionVisitor
{
public:
    virtual ~KeyboardInputActionVisitor();
    virtual void visit(KeyboardInputAction &) = 0;
};

class Q_DECL_EXPORT KeyboardInputAction : public Action
{
    typedef Action base;

public:
    /**
     * Where should we send the data too
     */
    enum DestinationWindow {
        ActiveWindow,
        SpecificWindow,
        ActionWindow,
    };

    KeyboardInputAction(ActionData *data_P, const QString &input_P = QString(), Windowdef_list *dest_window_P = nullptr, bool active_window_P = true);

    virtual ~KeyboardInputAction();
    void cfg_write(KConfigGroup &cfg_P) const Q_DECL_OVERRIDE;
    void execute() Q_DECL_OVERRIDE;

    const QString &input() const;
    void setInput(const QString &input);

    // send to specific window: dest_window != nullptr
    // send to active window: dest_window == nullptr && activeWindow() == true
    // send to action window: dest_window == nullptr && activeWindow() == false
    //

    DestinationWindow destination() const;
    void setDestination(const DestinationWindow &dest);

    const Windowdef_list *dest_window() const;
    Windowdef_list *dest_window();
    void setDestinationWindowRules(Windowdef_list *list);

    bool activeWindow() const;
    const QString description() const Q_DECL_OVERRIDE;
    Action *copy(ActionData *data_P) const Q_DECL_OVERRIDE;
    ActionType type() Q_DECL_OVERRIDE
    {
        return KeyboardInputActionType;
    }

    /**
     * Acyclic visitor pattern
     */
    void accept(ActionVisitor &) Q_DECL_OVERRIDE;

private:
    QString _input;
    Windowdef_list *_dest_window;

    //! Which window should get the input
    DestinationWindow _destination;
};

class ActivateWindowAction;
class ActivateWindowActionVisitor
{
public:
    virtual ~ActivateWindowActionVisitor();
    virtual void visit(ActivateWindowAction &) = 0;
};

class Q_DECL_EXPORT ActivateWindowAction : public Action
{
    typedef Action base;

public:
    ActivateWindowAction(ActionData *data_P, const Windowdef_list *window = nullptr);

    virtual ~ActivateWindowAction();
    void cfg_write(KConfigGroup &cfg_P) const Q_DECL_OVERRIDE;
    void execute() Q_DECL_OVERRIDE;

    const Windowdef_list *window() const;
    void set_window_list(Windowdef_list *list);

    const QString description() const Q_DECL_OVERRIDE;
    Action *copy(ActionData *data_P) const Q_DECL_OVERRIDE;
    ActionType type() Q_DECL_OVERRIDE
    {
        return ActivateWindowActionType;
    }

    /**
     * Acyclic visitor pattern
     */
    void accept(ActionVisitor &) Q_DECL_OVERRIDE;

private:
    const Windowdef_list *_window;
};

} // namespace KHotKeys

#endif
