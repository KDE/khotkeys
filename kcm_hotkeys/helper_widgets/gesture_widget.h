#ifndef GESTURE_WIDGET_H
#define GESTURE_WIDGET_H
/* Copyright (C) 2009 Michael Jansen <kde@michael-jansen.biz>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/


#include "ui_gesture_widget.h"

#include <QWidget>

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
/**
 * This widget contains the GestureDrawer and the edit button.
 */
class GestureWidget : public QWidget
    {
    Q_OBJECT

public:

    /**
     * Default constructor
     */
    GestureWidget(QWidget *parent = nullptr);

    /**
     * Destructor
     */
    virtual ~GestureWidget();

    void setPointData(const KHotKeys::StrokePoints &data, bool emitSignal);
    KHotKeys::StrokePoints pointData() const;

public Q_SLOTS:

    void edit();

Q_SIGNALS:

    void changed();

private:

    Ui::GestureWidget ui;

    };


#endif /* #ifndef GESTURE_WIDGET_H */
