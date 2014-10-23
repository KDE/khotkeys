#include <QApplication>
#include <QDBusMessage>
#include <QDBusConnection>
#include <QDBusReply>
#include <QDebug>

#include "kded.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QDBusInterface kdedInterface("org.kde.kded5","/kded","org.kde.kded5");
    QDBusReply<QStringList> reply =  kdedInterface.call("loadedModules");

    if (reply.value().contains("khotkeys")) {
        qDebug() << "The khotkeys module is already running.";
        qDebug() << "To unload it run:";
        qDebug() << "qdbus org.kde.kded5 /kded org.kde.kded5.unloadModule khotkeys";
        exit(-1);
    }

    KHotKeysModule module(&app, QVariantList());
    return app.exec();
}