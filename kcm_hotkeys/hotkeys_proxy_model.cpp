/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "hotkeys_proxy_model.h"
#include "hotkeys_model.h"


struct KHotkeysProxyModelPrivate
    {
    KHotkeysProxyModelPrivate( KHotkeysProxyModel *host );

    //! Our host
    KHotkeysProxyModel *q;

    }; // class KHotkeysProxyModelPrivate


KHotkeysProxyModelPrivate::KHotkeysProxyModelPrivate( KHotkeysProxyModel *host )
    : q(host)
    {}



KHotkeysProxyModel::KHotkeysProxyModel( QObject *parent )
    : QSortFilterProxyModel(parent)
     ,d( new KHotkeysProxyModelPrivate(this) )
    {}


KHotkeysProxyModel::~KHotkeysProxyModel()
    {
    delete d; d=0;
    }


bool KHotkeysProxyModel::filterAcceptsRow( int source_row, const QModelIndex &source_parent ) const
    {
    Q_UNUSED(source_row);
    Q_UNUSED(source_parent);
    return true;
    }


// Convert index to ActionDataBase
KHotKeys::ActionDataBase *KHotkeysProxyModel::indexToActionDataBase( const QModelIndex &index ) const
    {
    return sourceModel()->indexToActionDataBase( mapToSource(index) );
    }


// Convert index to ActionDataGroup
KHotKeys::ActionDataGroup *KHotkeysProxyModel::indexToActionDataGroup( const QModelIndex &index ) const
    {
    return sourceModel()->indexToActionDataGroup( mapToSource(index) );
    }


// Return the source model
KHotkeysModel *KHotkeysProxyModel::sourceModel() const
    {
    return static_cast<KHotkeysModel*>( QSortFilterProxyModel::sourceModel() );
    }


#include "moc_hotkeys_proxy_model.cpp"
