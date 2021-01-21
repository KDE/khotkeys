/*
    SPDX-License-Identifier: GPL-2.0-only
    SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
 */

#include "kded.h"

#include "action_data/action_data_group.h"
#include "action_data/menuentry_shortcut_action_data.h"
#include "actions/actions.h"

#include "shortcuts_handler.h"

#include "triggers/gestures.h"

#include <QDebug>
#include <kglobalaccel.h>
#include <kpluginfactory.h>
#include <kpluginloader.h>

#include <unistd.h>

#define COMPONENT_NAME "khotkeys"

K_PLUGIN_FACTORY_WITH_JSON(KHotKeysModuleFactory, "khotkeys.json", registerPlugin<KHotKeysModule>();)

using namespace KHotKeys;

// KhotKeysModule

KHotKeysModule::KHotKeysModule(QObject *parent, const QList<QVariant> &)
    : KDEDModule(parent)
    , actions_root(nullptr)
    , _settingsDirty(false)
    , _settings()
    , _initialized(false)
{
    // initialize
    qDebug() << "Installing the delayed initialization callback.";
    QMetaObject::invokeMethod(this, "initialize", Qt::QueuedConnection);
}

void KHotKeysModule::initialize()
{
    if (_initialized) {
        return;
    }

    qDebug() << "Delayed initialization.";
    _initialized = true;

    // Initialize the global data, grab keys
    KHotKeys::init_global_data(true, this);

    // If a shortcut was changed (global shortcuts kcm), save
    connect(keyboard_handler.data(), SIGNAL(shortcutChanged()), this, SLOT(scheduleSave()));

    // Read the configuration from file khotkeysrc
    reread_configuration();

    KGlobalAccel::cleanComponent(COMPONENT_NAME);

    if (_settings.update()) {
        save();
    }
}

KHotKeysModule::~KHotKeysModule()
{
    // actions_root belongs to _settings.
    actions_root = nullptr;
}

void KHotKeysModule::reread_configuration()
{
    qDebug() << "Reloading the khotkeys configuration";

    // Stop listening
    actions_root = nullptr; // Disables the dbus interface effectively
    KHotKeys::khotkeys_set_active(false);

    // Load the settings
    _settings.reread_settings(true);

    KHotKeys::gesture_handler->set_mouse_button(_settings.gestureMouseButton());
    KHotKeys::gesture_handler->set_timeout(_settings.gestureTimeOut());
    qDebug() << _settings.areGesturesDisabled();
    KHotKeys::gesture_handler->enable(!_settings.areGesturesDisabled());
    KHotKeys::gesture_handler->set_exclude(_settings.gesturesExclude());
    // FIXME: SOUND
    // KHotKeys::voice_handler->set_shortcut( _settings.voice_shortcut );
    actions_root = _settings.actions();
    KHotKeys::khotkeys_set_active(true);
}

SimpleActionData *KHotKeysModule::menuentry_action(const QString &storageId)
{
    ActionDataGroup *menuentries = _settings.get_system_group(ActionDataGroup::SYSTEM_MENUENTRIES);

    // Now try to find the action
    Q_FOREACH (ActionDataBase *element, menuentries->children()) {
        SimpleActionData *actionData = dynamic_cast<SimpleActionData *>(element);

        if (actionData && actionData->action()) {
            MenuEntryAction *action = dynamic_cast<MenuEntryAction *>(actionData->action());
            if (action && action->service() && (action->service()->storageId() == storageId)) {
                return actionData;
            }
        }
    }

    return nullptr;
}

QString KHotKeysModule::get_menuentry_shortcut(const QString &storageId)
{
    SimpleActionData *actionData = menuentry_action(storageId);

    // No action found
    if (actionData == nullptr)
        return "";

    // The action must have a shortcut trigger. but don't assume to much
    ShortcutTrigger *shortcutTrigger = dynamic_cast<ShortcutTrigger *>(actionData->trigger());

    Q_ASSERT(shortcutTrigger);
    if (shortcutTrigger == nullptr)
        return "";

    qDebug() << shortcutTrigger->primaryShortcut();

    return shortcutTrigger->primaryShortcut();
}

QString KHotKeysModule::register_menuentry_shortcut(const QString &storageId, const QString &sequence)
{
    qDebug() << storageId << "(" << sequence << ")";

    // Check the service we got. If it is invalid there is no need to
    // continue.
    KService::Ptr wantedService = KService::serviceByStorageId(storageId);
    if (!wantedService) {
        qCritical() << "Storage Id " << storageId << "not valid";
        return "";
    }

    // Look for the action
    SimpleActionData *actionData = menuentry_action(storageId);

    // No action found. Create on if sequence is != ""
    if (actionData == nullptr) {
        qDebug() << "No action found";

        // If the sequence is empty there is no need to create a action.
        if (sequence.isEmpty())
            return "";

        qDebug() << "Creating a new action";

        // Create the action
        ActionDataGroup *menuentries = _settings.get_system_group(ActionDataGroup::SYSTEM_MENUENTRIES);

        MenuEntryShortcutActionData *newAction =
            new MenuEntryShortcutActionData(menuentries, wantedService->name(), storageId, QKeySequence(sequence), storageId);

        newAction->enable();

        _settings.write();

        // Return the real shortcut
        return newAction->trigger()->primaryShortcut();
    }
    // We found a action
    else {
        if (sequence.isEmpty()) {
            qDebug() << "Deleting the action";
            actionData->aboutToBeErased();
            delete actionData;
            _settings.write();
            return "";
        } else {
            qDebug() << "Changing the action";
            // The action must have a shortcut trigger. but don't assume to much
            ShortcutTrigger *shortcutTrigger = dynamic_cast<ShortcutTrigger *>(actionData->trigger());
            Q_ASSERT(shortcutTrigger);
            if (shortcutTrigger == nullptr)
                return "";

            // Change the actionData
            shortcutTrigger->set_key_sequence(sequence);
            _settings.write();

            // Remove the resulting real shortcut
            return shortcutTrigger->primaryShortcut();
        }
    }

    Q_ASSERT(false);
    return "";
}

void KHotKeysModule::quit()
{
    deleteLater();
}

void KHotKeysModule::scheduleSave()
{
    if (!_settingsDirty) {
        _settingsDirty = true;
        QMetaObject::invokeMethod(this, "save", Qt::QueuedConnection);
    }
}

void KHotKeysModule::save()
{
    _settingsDirty = false;
    KHotKeys::khotkeys_set_active(false);
    _settings.write();
    KHotKeys::khotkeys_set_active(true);
}

void KHotKeysModule::declareConfigOutdated()
{
    Settings::isOutdated = true;
}

#include "kded.moc"
