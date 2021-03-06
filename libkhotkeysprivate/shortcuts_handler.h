/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef SHORTCUTSHANDLER_H
#define SHORTCUTSHANDLER_H

#include <KActionCollection>

#include <X11/X.h>
#include <fixx11h.h>

class KAction;
class QKeySequence;

namespace KHotKeys
{
/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class ShortcutsHandler : public QObject
{
    Q_OBJECT

public:
    enum HandlerType {
        Active, //!< Create real actions
        Configuration,
    }; //!< Create configuration actions ( not active )

    /**
     * Default constructor
     *
     * \param Should
     */
    ShortcutsHandler(HandlerType type = Active, QObject *parent = nullptr);

    /**
     * Destructor
     */
    ~ShortcutsHandler();

    /**
     * Create a action.
     *
     * The action stays in the ownership of this class. Do not delete.
     *
     * \param id        Persistent id for the action
     * \param name      Name for the action. Is used in the global shortcut
     *                  configuration dialog
     * \param shortcut  Shortcut that triggers the action
     *
     * \return The new action or 0 if an error occurred.
     *
     * \see KAction::registerGlobalShortcut()
     */
    QAction *addAction(const QString &id, const QString &text, const QKeySequence &shortcut);

    /**
     * Remove a action from the collection.
     *
     * \param id        Persistent id for the action
     *
     * \return The action or 0 if not found.
     */
    QAction *getAction(const QString &id);

    /**
     * Remove a action from the collection.
     *
     * \param id        Persistent id for the action
     *
     * \return true if the action was removed.
     */
    bool removeAction(const QString &id);

    /**
     * From Kbd.
     *
     * \warning Does nothing, returns false
     */
    bool send_macro_key(const QKeySequence &key, Window window_P);

Q_SIGNALS:

    /**
     * One of the actions shortcuts was changed.
     */
    void shortcutChanged() const;

private:
    HandlerType _type;

    KActionCollection *_actions;
};

} // namespace KHotKeys

#endif /* #ifndef SHORTCUTSHANDLER_H */
