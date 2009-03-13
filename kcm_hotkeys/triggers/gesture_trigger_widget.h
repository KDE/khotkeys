#ifndef GESTURE_TRIGGER_WIDGET_H
#define GESTURE_TRIGGER_WIDGET_H
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

#include "trigger_widget_base.h"
#include "ui_gesture_trigger_widget.h"


/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
/**
 * This widget links the GestureTrigger and the GestureWidget by copying the
 * point data from one to the other as needed.
 */

class GestureTriggerWidget : public TriggerWidgetBase
    {
    Q_OBJECT

    typedef TriggerWidgetBase Base;

public:

    /**
     * Default constructor
     */
    GestureTriggerWidget(KHotKeys::GestureTrigger *trigger, QWidget *parent = NULL);

    /**
     * Destructor
     */
    virtual ~GestureTriggerWidget();

    KHotKeys::GestureTrigger *trigger();
    const KHotKeys::GestureTrigger *trigger() const;

    virtual bool isChanged() const;

private:

    virtual void doCopyFromObject();
    virtual void doCopyToObject();

    Ui::GestureTriggerWidget ui;

    bool hasChanged;

private Q_SLOTS:

    void slotGestureHasChanged();
    };


#endif /* #ifndef GESTURE_TRIGGER_WIDGET_H */
