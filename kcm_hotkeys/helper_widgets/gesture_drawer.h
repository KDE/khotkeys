/*
    SPDX-License-Identifier: GPL-2.0-only
    SPDX-FileCopyrightText: 2003 Mike Pilone <mpilone@slac.com>
    SPDX-FileCopyrightText: 2003 Lubos Lunak <l.lunak@kde.org>
    SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>
 */

#ifndef GESTURE_DRAWER_H
#define GESTURE_DRAWER_H

#include "triggers/gestures.h"

#include <QFrame>

#include <QEvent>
#include <QPoint>
#include <QSize>
#include <QWidget>

/**
 * This widget provides the service of drawing the processed point data of the
 * gesture.
 */

class GestureDrawer : public QFrame
{
    Q_OBJECT

public:
    GestureDrawer(QWidget *parent, const char *name = nullptr);
    ~GestureDrawer() override;

    void setPointData(const KHotKeys::StrokePoints &data);
    KHotKeys::StrokePoints pointData() const;

    QSize sizeHint() const override
    {
        return QSize(30, 30);
    }

protected:
    void paintEvent(QPaintEvent *ev) override;

private:
    KHotKeys::StrokePoints _data;
};

#endif
