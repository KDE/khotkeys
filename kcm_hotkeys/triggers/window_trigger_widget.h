/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef WINDOW_TRIGGER_WIDGET_H
#define WINDOW_TRIGGER_WIDGET_H

#include "trigger_widget_base.h"

#include "ui_window_trigger_widget.h"

class WindowDefinitionListWidget;

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class WindowTriggerWidget : public TriggerWidgetBase
{
    Q_OBJECT

    typedef TriggerWidgetBase Base;

public:
    /**
     * Default constructor
     */
    WindowTriggerWidget(KHotKeys::WindowTrigger *trigger, QWidget *parent = nullptr);

    /**
     * Destructor
     */
    virtual ~WindowTriggerWidget();

    KHotKeys::WindowTrigger *trigger() Q_DECL_OVERRIDE;
    const KHotKeys::WindowTrigger *trigger() const Q_DECL_OVERRIDE;

    bool isChanged() const Q_DECL_OVERRIDE;

private Q_SLOTS:

    void slotWindowSelectionChanged(bool) const;

private:
    void doCopyFromObject() Q_DECL_OVERRIDE;
    void doCopyToObject() Q_DECL_OVERRIDE;

    Ui::WindowTriggerWidget window_trigger_ui;

    WindowDefinitionListWidget *_windowdef_widget;
};

#endif /* #ifndef WINDOW_TRIGGER_WIDGET_H */
