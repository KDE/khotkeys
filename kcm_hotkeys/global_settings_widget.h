/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef GLOBAL_SETTINGS_WIDGET_H
#define GLOBAL_SETTINGS_WIDGET_H

#include <ui_global_settings_widget.h>

#include "hotkeys_widget_iface.h"

#include <KSharedConfig>


class KHotkeysModel;


/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class GlobalSettingsWidget : public HotkeysWidgetIFace
    {
    Q_OBJECT

public:

    /**
     * Default constructor
     */
    GlobalSettingsWidget(QWidget *parent = nullptr);

    /**
     * Destructor
     */
    ~GlobalSettingsWidget();

    /**
     * Set the model we configure
     */
    void setModel(KHotkeysModel *);

private Q_SLOTS:

    bool isChanged() const Q_DECL_OVERRIDE;

protected:

    void doCopyFromObject() Q_DECL_OVERRIDE;
    void doCopyToObject() Q_DECL_OVERRIDE;

private:

    KSharedConfigPtr _config;
    KHotkeysModel *_model;
    Ui::GlobalSettingsWidget ui;

};

#endif /* #ifndef GLOBAL_SETTINGS_WIDGET_H */
