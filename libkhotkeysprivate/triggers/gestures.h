/*
    SPDX-License-Identifier: GPL-2.0-only
    SPDX-FileCopyrightText: 1999-2002 Lubos Lunak <l.lunak@kde.org>
 */

#ifndef _GESTURES_H_
#define _GESTURES_H_

#include <QAbstractNativeEventFilter>
#include <QMap>
#include <QPointer>
#include <QTimer>
#include <qwindowdefs.h>

#include "windows_handler.h"

namespace KHotKeys
{
class Gesture;
class ActionData;

Q_DECL_EXPORT extern QPointer<Gesture> gesture_handler;

/**
 * A PointQuintet represents a point in the gesture,
 * saving not only coordinates but also the relation to the successor.
 * The coordinates x and y are mainly used for drawing the stroke,
 * the rest is used by the gesture matching algoritm.
 */

class PointQuintet
{
public:
    // at which percentage of the stroke length does the point occur?
    // 100%=1
    qreal s;
    // relative distance to the successor (s+delta_s is s of the next point)
    qreal delta_s;
    // angle to successor in units of pi
    qreal angle;
    // coordinates scaled to a square box. each goes from 0 to 1
    qreal x, y;
};

typedef QVector<PointQuintet> StrokePoints;

/**
 * The Stroke saves the raw data of the mouse movement. It gets sent the coordinates and
 * records them while preparing for processing them. The method processData()
 * returns the processed version of this raw data.
 */

class Q_DECL_EXPORT Stroke
{
public:
    // largest number of points allowed to be sampled
    enum {
        MAX_POINTS = 5000,
    };

    Stroke();
    ~Stroke();
    bool record(int x, int y);

    StrokePoints processData();
    void reset();

protected:
    // metrics for input stroke
    int min_x, min_y;
    int max_x, max_y;
    int point_count;

    struct point {
        int x;
        int y;
    };

    point *points;
};

/**
 * The Gesture class manages the mouse grabbing and sends its data to a Stroke.
 * Then it emits the Stroke's processed data so that instances of GestureTrigger
 * can handle it.
 */

class Q_DECL_EXPORT Gesture : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    Gesture(bool enabled_P, QObject *parent_P);
    virtual ~Gesture();
    void enable(bool enable_P);
    void set_mouse_button(unsigned int button_P);
    void set_timeout(int time_P);
    void set_exclude(Windowdef_list *windows_P);
    void register_handler(QObject *receiver_P, const char *slot_P);
    void unregister_handler(QObject *receiver_P, const char *slot_P);

protected:
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *) Q_DECL_OVERRIDE;

private Q_SLOTS:
    void stroke_timeout();
    void active_window_changed(WId window_P);
    void handleScore(ActionData *const data, const qreal score);
Q_SIGNALS:
    void handle_gesture(const StrokePoints &gesture);

private:
    void update_grab();
    void grab_mouse(bool grab_P);
    void mouse_replay(bool release_P);
    bool _enabled;
    Stroke stroke;
    int start_x, start_y;
    QTimer nostroke_timer;
    bool recording;
    unsigned int button;
    int timeout;

    // two variables to help determine which action belongs to
    // the best-fitting gesture.
    qreal maxScore;
    ActionData *bestFit;

    Windowdef_list *exclude;
    QMap<QObject *, bool> handlers; // bool is just a dummy
};

} // namespace KHotKeys

#endif
