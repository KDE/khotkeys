/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "hotkeys_tree_view.h"
#include "hotkeys_context_menu.h"

#include "hotkeys_model.h"

#include "action_data/action_data_group.h"
#include "action_data/simple_action_data.h"

#include "KDE/KLocale"
#include "KDE/KDebug"

#include <QContextMenuEvent>


HotkeysTreeView::HotkeysTreeView( QWidget *parent )
    : QTreeView(parent)
    {
    setObjectName("khotkeys treeview");
    setAllColumnsShowFocus(true);
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    }


HotkeysTreeView::~HotkeysTreeView()
    {}


void
HotkeysTreeView::contextMenuEvent( QContextMenuEvent *event )
    {
    QModelIndex index = indexAt(event->pos());
    // KHotKeys::ActionDataBase *item = model()->indexToActionDataBase(index);
    HotkeysTreeViewContextMenu menu( index, this );
    menu.exec(event->globalPos());
    }


void
HotkeysTreeView::modelReset()
    {
    resizeColumnToContents(KHotkeysModel::NameColumn);
    }


KHotkeysModel *HotkeysTreeView::model()
    {
    return dynamic_cast<KHotkeysModel*>( QTreeView::model() );
    }


void
HotkeysTreeView::setModel( QAbstractItemModel *model )
    {
    if (!dynamic_cast<KHotkeysModel*>( model ))
        {
        Q_ASSERT(dynamic_cast<KHotkeysModel*>( model ));
        return;
        }
    QTreeView::setModel(model);

    setAllColumnsShowFocus(true);
    setAlternatingRowColors(true);

    setSelectionBehavior( QAbstractItemView::SelectRows );
    setSelectionMode( QAbstractItemView::SingleSelection );

    connect(
        model, SIGNAL(modelReset()),
        this, SLOT(modelReset()));

    resizeColumnToContents(KHotkeysModel::EnabledColumn);
    resizeColumnToContents(KHotkeysModel::NameColumn);
    }

void
HotkeysTreeView::mouseReleaseEvent(QMouseEvent *me)
    {
    if (me->button() == Qt::LeftButton && !indexAt(me->pos()).isValid()) {
        clearSelection();
        setCurrentIndex(QModelIndex());
    }
    QTreeView::mouseReleaseEvent(me);
    }

#include "moc_hotkeys_tree_view.cpp"
