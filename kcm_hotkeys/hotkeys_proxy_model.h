/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef KHOTKEYSPROXYMODEL_H
#define KHOTKEYSPROXYMODEL_H

#include "libkhotkeysfwd.h"

#include <QSortFilterProxyModel>

class KHotkeysProxyModelPrivate;
class KHotkeysModel;

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class KHotkeysProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    /**
     * Default constructor
     */
    KHotkeysProxyModel(QObject *parent);

    /**
     * Destructor
     */
    virtual ~KHotkeysProxyModel();

    /**
     * Returns true if the item in column @a column should be included in
     * the model.
     */
    bool filterAcceptsRow(int source_column, const QModelIndex &source_parent) const Q_DECL_OVERRIDE;

    /**
     * Get the KHotKeys::ActionDataBase behind the index.
     */
    KHotKeys::ActionDataBase *indexToActionDataBase(const QModelIndex &index) const;

    /**
     * Get the KHotKeys::ActionDataBase behind the index or 0.
     *
     * Getting 0 doesn't mean the index is invalid. It means you provided a
     * action object.
     */
    KHotKeys::ActionDataGroup *indexToActionDataGroup(const QModelIndex &index) const;

    /**
     * Return the source model. Casted to the correct class.
     */
    KHotkeysModel *sourceModel() const;

private:
    //! Implementation details
    KHotkeysProxyModelPrivate *d;
};

#endif /* #ifndef KHOTKEYSPROXYMODEL_HPP */
