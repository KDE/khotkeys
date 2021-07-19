/*
    SPDX-License-Identifier: GPL-2.0-only
    SPDX-FileCopyrightText: 2003 Lubos Lunak <l.lunak@kde.org>
 */

#include "helper_widgets/window_selector.h"

#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QX11Info>

#include <X11/Xlib.h>
#include <fixx11h.h>
#include <xcb/xcb.h>

namespace KHotKeys
{
WindowSelector::WindowSelector(QObject *receiver_P, const char *slot_P)
{
    connect(this, SIGNAL(selected_signal(WId)), receiver_P, slot_P);
}

WindowSelector::~WindowSelector()
{
    qApp->desktop()->releaseMouse();
    QApplication::instance()->removeNativeEventFilter(this);
}

void WindowSelector::select()
{
    qApp->desktop()->grabMouse(QCursor(Qt::CrossCursor));
    QApplication::instance()->installNativeEventFilter(this);
}

bool WindowSelector::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(result)
    if (eventType != QByteArrayLiteral("xcb_generic_event_t")) {
        return false;
    }
    xcb_generic_event_t *event = reinterpret_cast<xcb_generic_event_t *>(message);
    if ((event->response_type & ~0x80) == XCB_BUTTON_PRESS) {
        xcb_button_press_event_t *e = reinterpret_cast<xcb_button_press_event_t *>(event);
        if (e->detail == XCB_BUTTON_INDEX_1) {
            if (WId window = findRealWindow(e->child)) {
                emit selected_signal(window);
            }
            deleteLater();
            return true;
        }
    }
    return false;
}

WId WindowSelector::findRealWindow(WId w, int depth)
{
    if (depth > 5)
        return None;
    static Atom wm_state = XInternAtom(QX11Info::display(), "WM_STATE", False);
    Atom type;
    int format;
    unsigned long nitems, after;
    unsigned char *prop;
    if (XGetWindowProperty(QX11Info::display(), w, wm_state, 0, 0, False, AnyPropertyType, &type, &format, &nitems, &after, &prop) == Success) {
        if (prop != nullptr)
            XFree(prop);
        if (type != None)
            return w;
    }
    Window root, parent;
    Window *children;
    unsigned int nchildren;
    Window ret = None;
    if (XQueryTree(QX11Info::display(), w, &root, &parent, &children, &nchildren) != 0) {
        for (unsigned int i = 0; i < nchildren && ret == None; ++i)
            ret = findRealWindow(children[i], depth + 1);
        if (children != nullptr)
            XFree(children);
    }
    return ret;
}

} // namespace KHotKeys
