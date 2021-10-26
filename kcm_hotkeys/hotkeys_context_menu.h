#ifndef HOTKEYS_CONTEXT_MENU_H
#define HOTKEYS_CONTEXT_MENU_H
/**
 * SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "actions/actions.h"
#include "triggers/triggers.h"

#include "libkhotkeysfwd.h"

#include <QMenu>
#include <QModelIndex>

class HotkeysTreeView;

class QModelIndex;
class QSignalMapper;

class HotkeysTreeViewContextMenu : public QMenu
{
    Q_OBJECT

public:
    HotkeysTreeViewContextMenu(const QModelIndex &index, HotkeysTreeView *parent = nullptr);
    HotkeysTreeViewContextMenu(HotkeysTreeView *parent = nullptr);

    ~HotkeysTreeViewContextMenu() override;

    //! Create a submenu per allowed trigger type
    void createTriggerMenus(KHotKeys::Trigger::TriggerTypes triggerTypes, KHotKeys::Action::ActionTypes actionTypes);

    //! Populate a trigger menu
    void populateTriggerMenu(QMenu *menu, QSignalMapper *mapper, KHotKeys::Action::ActionTypes types);

private Q_SLOTS:

    void slotAboutToShow();
    void slotAboutToShowForCurrent();
    void deleteAction();

    void exportAction();
    void importAction();

    void newGlobalShortcutActionAction(int);
    void newWindowTriggerActionAction(int);
    void newMouseGestureTriggerActionAction(int);
    void newGroupAction();

private:
    KHotKeys::Action *createActionFromType(int type, KHotKeys::SimpleActionData *data) const;

    QModelIndex _index;
    HotkeysTreeView *_view;
};

#endif /* HOTKEYS_CONTEXT_MENU_H */
