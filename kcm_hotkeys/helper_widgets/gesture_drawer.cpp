/****************************************************************************

 KHotKeys

 Copyright (C) 2003 Mike Pilone <mpilone@slac.com>
 Copyright (C) 2003 Lubos Lunak <l.lunak@kde.org>
 Copyright (C) 2009 Michael Jansen <kde@michael-jansen.biz>

 Distributed under the terms of the GNU General Public License version 2.

****************************************************************************/

#include <QtGui/QColor>
#include <QtGui/QPainter>
#include <QtGui/QFrame>
#include <QtGui/QPaintEvent>

#include "gesture_drawer.h"

GestureDrawer::GestureDrawer(QWidget *parent, const char *name)
  : QFrame(parent), _data(QString())
    {
    setObjectName(name);
    QPalette p;
    p.setColor( backgroundRole(), palette().color( QPalette::Base ) );
    setPalette( p );
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setMinimumSize(30, 30);
    }


GestureDrawer::~GestureDrawer()
    {
    }


QString GestureDrawer::code() const
    {
    return _data;
    }


void GestureDrawer::setCode(const QString &data)
    {
    _data = data;

    repaint();
    }


void GestureDrawer::paintEvent(QPaintEvent *ev)
    {
  // Iterate through the data points and draw a line to each of them
    quint32 startCell = 0;
    quint32 endCell = 0;
    QPoint startPoint;
    QPoint endPoint;

    QPainter p(this);

    if (_data.length() > 0)
        {
        startCell = QString(_data[0]).toUInt();
        }

    for (Q_INT32 index = 1; index < _data.length(); ++index)
        {
        endCell = QString(_data[index]).toUInt();

        startPoint = lookupCellCoords(startCell);
        endPoint = lookupCellCoords(endCell);

        if (index == 1)
            {
      // Draw something to show the starting point
            p.drawRect(startPoint.x()-2, startPoint.y()-2, 4, 4);
            p.fillRect(startPoint.x()-2, startPoint.y()-2, 4, 4,
                       QBrush(Qt::black));
            }

        p.drawLine(startPoint, endPoint);
        drawArrowHead(startPoint, endPoint, p);

        startCell = endCell;
        }

    p.end();

    QFrame::paintEvent(ev);
    }

QPoint GestureDrawer::lookupCellCoords(quint32 cell)
    {
  // First divide the widget into thirds, horizontally and vertically
    quint32 w = width();
    quint32 h = height();

    quint32 wThird = w / 3;
    quint32 hThird = h / 3;

    switch(cell)
        {
        case 1:
            return QPoint(wThird/2, 2*hThird+hThird/2);

        case 2:
            return QPoint(wThird+wThird/2, 2*hThird+hThird/2);

        case 3:
            return QPoint(2*wThird+wThird/2, 2*hThird+hThird/2);

        case 4:
            return QPoint(wThird/2, hThird+hThird/2);

        case 5:
            return QPoint(wThird+wThird/2, hThird+hThird/2);

        case 6:
            return QPoint(2*wThird+wThird/2, hThird+hThird/2);

        case 7:
            return QPoint(wThird/2, hThird/2);

        case 8:
            return QPoint(wThird+wThird/2, hThird/2);

        case 9:
            return QPoint(2*wThird+wThird/2, hThird/2);
        }

    return QPoint(0, 0);
    }

void GestureDrawer::drawArrowHead(QPoint &start, QPoint &end,
                                  QPainter &p)
    {
    int deltaX = end.x() - start.x();
    int deltaY = end.y() - start.y();

    if (deltaY == 0)
        {
    // horizontal line
        int offset = 0;
        if (deltaX > 0)
          offset = -3;
        else
          offset = 3;

        p.drawLine(QPoint(end.x()+offset, end.y()+2), end);
        p.drawLine(QPoint(end.x()+offset, end.y()-2), end);
        }
    else if (deltaX == 0)
        {
    // vertical line
        int offset = 0;
        if (deltaY > 0)
          offset = -3;
        else
          offset = +3;

        p.drawLine(QPoint(end.x()+2, end.y()+offset), end);
        p.drawLine(QPoint(end.x()-2, end.y()+offset), end);
        }
    else
        {
        // diagonal - The math would be pretty complex, so don't do anything
        }

    }

#include "moc_gesture_drawer.cpp"