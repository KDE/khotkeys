/* SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "daemon.h"

#include <memory>

#include "khotkeysglobal.h"

#include <QDBusConnection>
#include <QDBusError>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QDBusReply>

#include "KDE/KDebug"
#include "KDE/KLocale"
#include <KConfig>
#include <KConfigGroup>

namespace KHotKeys
{
namespace Daemon
{
bool isEnabled()
{
    KConfig khotkeysrc(KHOTKEYS_CONFIG_FILE);
    KConfigGroup main(&khotkeysrc, "Main");
    return !main.readEntry("Disabled", false);
}

static QDBusInterface *Kded()
{
    QDBusInterface *iface = new QDBusInterface("org.kde.kded5", "/kded", "org.kde.kded5");
    if (!iface->isValid()) {
        QDBusError err = iface->lastError();
        if (err.isValid()) {
            qCritical() << "Failed to contact kded [" << err.name() << "]:" << err.message();
        }
    }
    return iface;
}

bool isRunning()
{
    std::unique_ptr<QDBusInterface> kded(Kded());
    if (!kded->isValid()) {
        return false;
    }

    // I started with checking if i could get a valid /KHotKeys Interface. But
    // it resisted to work. So lets do the other thing.
    QDBusReply<QStringList> modules = kded->call("loadedModules");
    return modules.value().contains("khotkeys");
}

bool reload()
{
    // No kded no reload
    std::unique_ptr<QDBusInterface> kded(Kded());
    if (!kded->isValid()) {
        return false;
    }

    // Inform kdedkhotkeys demon to reload settings
    QDBusConnection bus = QDBusConnection::sessionBus();
    QDBusInterface iface("org.kde.kded5", "/modules/khotkeys", "org.kde.khotkeys", bus);
    if (!iface.isValid()) {
        QDBusError err = iface.lastError();
        if (err.isValid()) {
            qCritical() << err.name() << ":" << err.message();
        }
        return start();
    }

    QDBusMessage reply = iface.call("reread_configuration");
    QDBusError err = iface.lastError();
    if (err.isValid()) {
        qCritical() << err.name() << ":" << err.message();
        return false;
    }

    return true;
}

bool start()
{
    std::unique_ptr<QDBusInterface> kded(Kded());
    if (!kded->isValid()) {
        return false;
    }
    QDBusReply<bool> reply = kded->call("loadModule", "khotkeys");
    QDBusError err = reply.error();

    if (err.isValid()) {
        qCritical() << "Unable to start server org.kde.khotkeys (kded module) [" << err.name() << "]:" << err.message();
        return false;
    }

    Q_ASSERT(reply.isValid());

    if (reply.value()) {
        return true;
    } else {
        qCritical() << "Unable to start server org.kde.khotkeys (kded module)";
        return false;
    }
}

bool stop()
{
    if (!isRunning()) {
        return true;
    }

    std::unique_ptr<QDBusInterface> kded(Kded());
    if (!kded->isValid()) {
        return false;
    }

    QDBusReply<bool> reply = kded->call("unloadModule", "khotkeys");
    QDBusError err = reply.error();

    if (err.isValid()) {
        qCritical() << "Error when stopping khotkeys kded module [" << err.name() << "]:" << err.message();
        return false;
    }

    Q_ASSERT(reply.isValid());

    if (reply.value()) {
        return true;
    } else {
        qCritical() << "Failed to stop server org.kde.khotkeys (kded module)";
        return false;
    }
}

}
} // namespace KHotKeys::Daemon
