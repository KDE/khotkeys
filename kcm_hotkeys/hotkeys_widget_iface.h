/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef HOTKEYS_WIDGET_IFACE
#define HOTKEYS_WIDGET_IFACE

#include "libkhotkeysfwd.h"

#include <QSignalMapper>
#include <QWidget>

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class HotkeysWidgetIFace : public QWidget
{
    Q_OBJECT

public:
    /**
     * Default constructor
     */
    HotkeysWidgetIFace(QWidget *parent = nullptr);

    /**
     * Destructor
     */
    virtual ~HotkeysWidgetIFace();

    virtual bool isChanged() const = 0;
    void copyFromObject();
    void copyToObject();

    virtual void apply();

Q_SIGNALS:

    virtual void changed(bool) const;

public Q_SLOTS:

    virtual void slotChanged(const QString &what = "Nothing");

protected:
    QSignalMapper *_changedSignals;

    virtual void doCopyFromObject() = 0;
    virtual void doCopyToObject() = 0;
};

#endif /* #ifndef HOTKEYS_WIDGET_BASE_H */
