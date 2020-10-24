/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef KHOTKEYSMODEL_H
#define KHOTKEYSMODEL_H

#include "libkhotkeysfwd.h"
#include "settings.h"

#include <QAbstractItemModel>


/**
 */
class KHotkeysModel : public QAbstractItemModel
    {
    Q_OBJECT

    public:

    enum ItemType {
        Other                          //!< Some unknown action type
        ,ActionDataGroup               //!< A shortcut group
        ,SimpleActionData
    };

    enum Column {
        NameColumn,
        EnabledColumn,
        IsGroupColumn,
        TypeColumn };

    /**
     * Default constructor
     *
     * @param 
     */
    KHotkeysModel( QObject *parent = nullptr );

    /**
     * Destructor
     */
    virtual ~KHotkeysModel();

    /**
     * \group Qt Model/View Framework methods
     */
    //@{
    QModelIndex index( int, int, const QModelIndex &parent = QModelIndex() ) const Q_DECL_OVERRIDE;
    QModelIndex parent( const QModelIndex &index ) const Q_DECL_OVERRIDE;
    int rowCount( const QModelIndex &index ) const Q_DECL_OVERRIDE;
    int columnCount( const QModelIndex &index ) const Q_DECL_OVERRIDE;
    QVariant headerData( int section, Qt::Orientation, int role = Qt::DisplayRole ) const Q_DECL_OVERRIDE;
    QVariant data( const QModelIndex &index, int role = Qt::DisplayRole ) const Q_DECL_OVERRIDE;
    bool setData( const QModelIndex &index, const QVariant &value, int role ) Q_DECL_OVERRIDE;
    Qt::ItemFlags flags( const QModelIndex &index ) const Q_DECL_OVERRIDE;
    //@}

    /**
     * \group Drag and Drop Support
     */
    //@{
    bool dropMimeData(
            const QMimeData *data
            ,Qt::DropAction action
            ,int row
            ,int column
            ,const QModelIndex &parent) Q_DECL_OVERRIDE;
    QMimeData *mimeData(const QModelIndexList &indexes) const Q_DECL_OVERRIDE;
    QStringList mimeTypes() const Q_DECL_OVERRIDE;
    //@}

    /**
     * Add a group as child of @a parent.
     *
     * @return the index for the new group
     */
    QModelIndex addGroup( const QModelIndex &parent );

    /**
     * Export the input actions into @a config.
     */
    void exportInputActions(
            const QModelIndex &index,
            KConfigBase &config,
            const QString& id,
            const KHotKeys::ActionState state,
            bool allowMerging);

    /**
     *Import the input actions from @a config.
     */
    void importInputActions(const QModelIndex &index, KConfigBase const &config);

    /**
     * Get the KHotKeys::ActionDataBase behind the index.
     */
    KHotKeys::ActionDataBase *indexToActionDataBase( const QModelIndex &index ) const;

    /**
     * Get the KHotKeys::ActionDataBase behind the index or 0.
     *
     * Getting 0 doesn't mean the index is invalid. It means you provided a
     * action object.
     */
    KHotKeys::ActionDataGroup *indexToActionDataGroup( const QModelIndex &index ) const;

    /**
     * Insert @a data as a child of @a parent.
     */
    QModelIndex insertActionData( KHotKeys::ActionDataBase *data, const QModelIndex &parent );

    /**
     * Load the settings from the file
     */
    void load();

    /**
     * Move @p element to @p newGroup at @position.
     *
     * @param element  move this element
     * @param newGroup to this group
     * @param position and put it at this position. default is last
     *
     * @return @c true if moved, @c false if not.
     */
    bool moveElement(
            KHotKeys::ActionDataBase *element
            ,KHotKeys::ActionDataGroup *newGroup
            ,int position = -1);

    /**
     * Remove @a count rows starting with @a row under @a parent.
     */
    bool removeRows( int row, int count, const QModelIndex &parent ) Q_DECL_OVERRIDE;

    /**
     * Save the settings to the file
     */
    void save();

    /**
     * Return the settings we handle
     */
    KHotKeys::Settings *settings();

    void emitChanged( KHotKeys::ActionDataBase *item );

  private:

    KHotKeys::Settings _settings;
    KHotKeys::ActionDataGroup *_actions;

};

#endif /* #ifndef KHOTKEYSMODEL_HPP */
