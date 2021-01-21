/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef HOTKEYS_TREE_VIEW_H
#define HOTKEYS_TREE_VIEW_H

#include "libkhotkeysfwd.h"

#include "actions/actions.h"
#include "triggers/triggers.h"

#include <QMenu>
#include <QTreeView>

class KHotkeysModel;

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class HotkeysTreeView : public QTreeView
{
    Q_OBJECT

public:
    /**
     * Default constructor
     */
    HotkeysTreeView(QWidget *parent = nullptr);

    /**
     * Destructor
     */
    virtual ~HotkeysTreeView();

    /**
     * The user requested a context menu
     */
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

    /**
     * Set a new model
     */
    void setModel(QAbstractItemModel *model) Q_DECL_OVERRIDE;
    KHotkeysModel *model();

protected:
    void mouseReleaseEvent(QMouseEvent *me) Q_DECL_OVERRIDE;

private Q_SLOTS:

    void modelReset();
};

#endif /* #ifndef HOTKEYS_TREE_VIEW_H */
