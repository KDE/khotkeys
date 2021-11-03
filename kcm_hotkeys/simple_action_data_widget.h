/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef SIMPLE_ACTION_DATA_WIDGET_H
#define SIMPLE_ACTION_DATA_WIDGET_H

#include "hotkeys_widget_base.h"

#include "action_data/simple_action_data.h"

#include <QWidget>

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class SimpleActionDataWidget : public HotkeysWidgetBase
{
    Q_OBJECT

    typedef HotkeysWidgetBase Base;

public:
    /**
     * Default constructor
     */
    SimpleActionDataWidget(QWidget *parent = nullptr);

    /**
     * Edit \a action.
     */
    void setActionData(KHotKeys::SimpleActionData *action);

    KHotKeys::SimpleActionData *data()
    {
        return static_cast<KHotKeys::SimpleActionData *>(_data);
    }

    const KHotKeys::SimpleActionData *data() const
    {
        return static_cast<const KHotKeys::SimpleActionData *>(_data);
    }

    /**
     * Destructor
     */
    ~SimpleActionDataWidget() override;

    bool isChanged() const override;

protected:
    void doCopyFromObject() override;
    void doCopyToObject() override;

private:
    HotkeysWidgetIFace *currentTrigger;
    HotkeysWidgetIFace *currentAction;
};

#endif /* #ifndef SIMPLE_ACTION_DATA_WIDGET_H */
