/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef KCMHOTKEYS_H
#define KCMHOTKEYS_H

#include <KCModule>

#include <QModelIndex>

class KCMHotkeysPrivate;
class QWidget;

namespace KHotKeys {
    class ActionDataBase;
}

/**
 * @brief KCMHotkeys KDE KCM Hotkeys Configuration Module
 * @author Michael Jansen <kde@michael-jansen.biz>
 * @date 2008-03-07
 */
class KCMHotkeys : public KCModule
    {
    Q_OBJECT

public:

    /**
     * Create the module.
     *
     * @param parent Parent widget
     */
    KCMHotkeys( QWidget *parent, const QVariantList &arg );

    /**
     * Destroy the module
     */
    virtual ~KCMHotkeys();

    /**
     * Set all settings back to defaults.
     */
    void defaults() Q_DECL_OVERRIDE;

    /**
     * Load all settings. 
     */
    void load() Q_DECL_OVERRIDE;

    /**
     * Save the settings
     */
    void save() Q_DECL_OVERRIDE;



public Q_SLOTS:

    void slotChanged();

    void slotReset();

    /**
     * Call when the current item has changed
     */
    void currentChanged( const QModelIndex &current, const QModelIndex &previous );

    /**
     * Show global settings dialog
     */
    void showGlobalSettings();

private:

    KCMHotkeysPrivate *d;
};

#endif /* #ifndef KCMHOTKEYS_HPP */
