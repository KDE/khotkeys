/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "global_settings_widget.h"

#include "hotkeys_model.h"
#include "settings.h"

#include <KConfigGroup>
#include <KDesktopFile>
#include <KGlobal>
#include <QDebug>

#include <QStandardPaths>

GlobalSettingsWidget::GlobalSettingsWidget(QWidget *parent)
    : HotkeysWidgetIFace(parent)
    , _model(nullptr)
{
    ui.setupUi(this);

    QString path = QStandardPaths::locate(QStandardPaths::GenericDataLocation, "kde5/services/kded/khotkeys.desktop");
    if (KDesktopFile::isDesktopFile(path)) {
        _config = KSharedConfig::openConfig(path, KConfig::NoGlobals, QStandardPaths::GenericDataLocation);
    }

    connect(ui.enabled, SIGNAL(stateChanged(int)), _changedSignals, SLOT(map()));
    _changedSignals->setMapping(ui.enabled, "enabled");

    connect(ui.gestures_group, SIGNAL(clicked(bool)), _changedSignals, SLOT(map()));
    _changedSignals->setMapping(ui.gestures_group, "gestures_enabled");

    connect(ui.gestures_timeout, SIGNAL(valueChanged(int)), _changedSignals, SLOT(map()));
    _changedSignals->setMapping(ui.gestures_timeout, "gestures_timeout");

    connect(ui.gestures_button, SIGNAL(currentIndexChanged(int)), _changedSignals, SLOT(map()));
    _changedSignals->setMapping(ui.gestures_button, "gestures_button");
}

GlobalSettingsWidget::~GlobalSettingsWidget()
{
}

void GlobalSettingsWidget::doCopyFromObject()
{
    if (_config) {
        KConfigGroup file(_config, "Desktop Entry");
        ui.enabled->setChecked(file.readEntry("X-KDE-Kded-autoload", false));
    }

    ui.gestures_group->setVisible(_model);
    if (_model) {
        KHotKeys::Settings *settings = _model->settings();
        Q_ASSERT(settings);
        ui.gestures_group->setChecked(!settings->areGesturesDisabled());
        ui.gestures_button->setCurrentIndex(settings->gestureMouseButton() - 2);
        ui.gestures_timeout->setValue(settings->gestureTimeOut());
    }
}

void GlobalSettingsWidget::doCopyToObject()
{
    if (_config) {
        KConfigGroup file(_config, "Desktop Entry");
        file.writeEntry("X-KDE-Kded-autoload", ui.enabled->checkState() == Qt::Checked);
        _config->sync();
    }

    if (_model) {
        KHotKeys::Settings *settings = _model->settings();
        Q_ASSERT(settings);
        ui.gestures_group->isChecked() ? settings->enableGestures() : settings->disableGestures();
        settings->setGestureMouseButton(ui.gestures_button->currentIndex() + 2);
        settings->setGestureTimeOut(ui.gestures_timeout->value());
    }
}

bool GlobalSettingsWidget::isChanged() const
{
    if (_config) {
        KConfigGroup file(_config, "Desktop Entry");
        bool enabled = file.readEntry("X-KDE-Kded-autoload", false);

        if (enabled != ui.enabled->isChecked()) {
            return true;
        }
    }

    if (_model) {
        KHotKeys::Settings *settings = _model->settings();
        Q_ASSERT(settings);
        if ((!settings->areGesturesDisabled()) != ui.gestures_group->isChecked() //
            || settings->gestureMouseButton() - 2 != ui.gestures_button->currentIndex() //
            || settings->gestureTimeOut() != ui.gestures_timeout->value()) {
            return true;
        }
    }

    return false;
}

void GlobalSettingsWidget::setModel(KHotkeysModel *model)
{
    _model = model;
    doCopyFromObject();
}

#include "moc_global_settings_widget.cpp"
