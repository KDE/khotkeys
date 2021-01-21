/*
    SPDX-FileCopyrightText: 2006 Volker Krause <volker.krause@rwth-aachen.de>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdedmodule_daemon_test.h"

#include "daemon/daemon.h"
#include "daemon/kded_module.h"

#include <qtest_kde.h>

#include <QDBusInterface>

void Test::initTestCase()
{
    daemonActive = KHotKeys::Daemon::isRunning();
    if (daemonActive) {
        qWarning() << "Shutting down a running daemon";
        KHotKeys::Daemon::stop();
    }
}

void Test::cleanupTestCase()
{
    if (daemonActive) {
        qWarning() << "Restarting the stopped daemon";
        KHotKeys::Daemon::start();
    }
}

void Test::testLoading()
{
    // Check loading/unloading. We have to do it more than once. When
    // something is amiss kded will crash after reloading it.
    QVERIFY(!KHotKeys::KdedModuleDaemon::isRunning());
    // 1st round
    QVERIFY(KHotKeys::KdedModuleDaemon::start());
    QVERIFY(KHotKeys::KdedModuleDaemon::isRunning());
    QVERIFY(KHotKeys::KdedModuleDaemon::stop());
    QVERIFY(!KHotKeys::KdedModuleDaemon::isRunning());
    // 2nd round
    QVERIFY(KHotKeys::KdedModuleDaemon::start());
    QVERIFY(KHotKeys::KdedModuleDaemon::isRunning());
    QVERIFY(KHotKeys::KdedModuleDaemon::stop());
    QVERIFY(!KHotKeys::KdedModuleDaemon::isRunning());
    // 3nd round
    QVERIFY(KHotKeys::KdedModuleDaemon::start());
    QVERIFY(KHotKeys::KdedModuleDaemon::isRunning());
    // Ensure kded is still there
    QVERIFY(QDBusInterface("org.kde.kded5", "/kded", "org.kde.kded5").isValid());
    QVERIFY(KHotKeys::KdedModuleDaemon::stop());
}

QTEST_MAIN(Test)
#include "moc_kdedmodule_daemon_test.cpp"
