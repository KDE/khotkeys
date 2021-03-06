#ifndef GESTURE_TRIGGER_WIDGET_H
#define GESTURE_TRIGGER_WIDGET_H
/* SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
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
    GestureTriggerWidget(KHotKeys::GestureTrigger *trigger, QWidget *parent = nullptr);

    /**
     * Destructor
     */
    virtual ~GestureTriggerWidget();

    KHotKeys::GestureTrigger *trigger() Q_DECL_OVERRIDE;
    const KHotKeys::GestureTrigger *trigger() const Q_DECL_OVERRIDE;

    bool isChanged() const Q_DECL_OVERRIDE;

private:
    void doCopyFromObject() Q_DECL_OVERRIDE;
    void doCopyToObject() Q_DECL_OVERRIDE;

    Ui::GestureTriggerWidget ui;

    bool hasChanged;

private Q_SLOTS:

    void slotGestureHasChanged();
};

#endif /* #ifndef GESTURE_TRIGGER_WIDGET_H */
