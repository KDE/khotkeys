#ifndef CONDITION_TYPE_MENU_H
#define CONDITION_TYPE_MENU_H
/* SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include <QMenu>

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class ConditionTypeMenu : public QMenu
{
    Q_OBJECT

public:
    /**
     * Default constructor
     */
    ConditionTypeMenu(QWidget *parent = nullptr);

    /**
     * Destructor
     */
    virtual ~ConditionTypeMenu();

    enum ConditionType {
        ACTIVE_WINDOW,
        EXISTING_WINDOW,
        AND,
        OR,
        NOT,
    };
};

#endif /* #ifndef CONDITION_TYPE_MENU_H */
