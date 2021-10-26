/*
    SPDX-License-Identifier: GPL-2.0-only
    SPDX-FileCopyrightText: 2003 Lubos Lunak <l.lunak@kde.org>
 */

#ifndef WINDOWSELECTOR_H
#define WINDOWSELECTOR_H

#include <QAbstractNativeEventFilter>
#include <QWidget>

namespace KHotKeys
{
class WindowSelector : public QWidget, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    WindowSelector(QObject *receiver, const char *slot);
    ~WindowSelector() override;
    void select();

    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;

Q_SIGNALS:
    void selected_signal(WId w);

private:
    WId findRealWindow(WId w, int depth = 0);
};

} // namespace KHotKeys

#endif
