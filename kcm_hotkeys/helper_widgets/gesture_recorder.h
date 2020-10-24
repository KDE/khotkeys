/*
    SPDX-License-Identifier: GPL-2.0-only
    SPDX-FileCopyrightText: 2003 Mike Pilone <mpilone@slac.com>
    SPDX-FileCopyrightText: 2003 Lubos Lunak <l.lunak@kde.org>
    SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>
 */

#ifndef GESTURE_RECORDER_H
#define GESTURE_RECORDER_H

#include "triggers/gestures.h"

#include <QFrame>

class QMouseEvent;

/**
 * This widget tracks mouse movements when the left mouse button has been
 * pressed while the cursor was over the widget.
 * The events are sent to a Stroke. When the mouse button is released the Stroke
 * is instructed to process the data; the processed data will then be emitted in
 * a "recorded" signal.
 */

class GestureRecorder : public QFrame
    {
    Q_OBJECT

    public:

        GestureRecorder(QWidget *parent, const char *name="FIXXXXXMMEEEEEEEEEEEEE");
        ~GestureRecorder();

    protected:

        void mousePressEvent(QMouseEvent *) Q_DECL_OVERRIDE;
        void mouseReleaseEvent(QMouseEvent *) Q_DECL_OVERRIDE;
        void mouseMoveEvent(QMouseEvent *) Q_DECL_OVERRIDE;
        void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

    Q_SIGNALS:

        void recorded(const KHotKeys::StrokePoints &data);

    private:
        bool _mouseButtonDown;
        KHotKeys::Stroke stroke;
    };

#endif
