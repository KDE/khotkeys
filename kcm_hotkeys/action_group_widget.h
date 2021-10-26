/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef ACTIONGROUPWIDGET_H
#define ACTIONGROUPWIDGET_H

#include "hotkeys_widget_base.h"

class ConditionsWidget;

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class ActionGroupWidget : public HotkeysWidgetBase
{
    Q_OBJECT

    typedef HotkeysWidgetBase Base;

public:
    /**
     * Default constructor
     */
    ActionGroupWidget(QWidget *parent = nullptr);

    /**
     * Destructor
     */
    ~ActionGroupWidget() override;

    /**
     * The associated action.
     */
    KHotKeys::ActionDataBase *data()
    {
        return static_cast<KHotKeys::ActionDataBase *>(_data);
    }

    const KHotKeys::ActionDataBase *data() const
    {
        return static_cast<const KHotKeys::ActionDataBase *>(_data);
    }

    //! Are there uncommitted changes?
    bool isChanged() const Q_DECL_OVERRIDE;

    void setActionData(KHotKeys::ActionDataGroup *group);

private:
    void doCopyFromObject() Q_DECL_OVERRIDE;
    void doCopyToObject() Q_DECL_OVERRIDE;

    //! Widget to change the conditions
    ConditionsWidget *_conditions;
};

#endif /* #ifndef ACTIONGROUPWIDGET_HPP */
