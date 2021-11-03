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
    ~GestureTriggerWidget() override;

    KHotKeys::GestureTrigger *trigger() override;
    const KHotKeys::GestureTrigger *trigger() const override;

    bool isChanged() const override;

private:
    void doCopyFromObject() override;
    void doCopyToObject() override;

    Ui::GestureTriggerWidget ui;

    bool hasChanged;

private Q_SLOTS:

    void slotGestureHasChanged();
};

#endif /* #ifndef GESTURE_TRIGGER_WIDGET_H */
