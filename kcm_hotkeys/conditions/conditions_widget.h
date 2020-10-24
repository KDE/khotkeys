#ifndef CONDITIONS_WIDGET_H
#define CONDITIONS_WIDGET_H
/* SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include <QMap>
#include <QWidget>


#include "ui_conditions_widget.h"

class QAction;
class QTreeWidgetItem;

namespace KHotKeys {
    class Condition_list;
    class Condition;
}


/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class ConditionsWidget : public QWidget
    {
    Q_OBJECT

public:

    /**
     * Default constructor
     */
    ConditionsWidget(QWidget *parent = nullptr);

    /**
     * Destructor
     */
    virtual ~ConditionsWidget();

    void copyFromObject();
    void copyToObject();

    void setConditionsList(KHotKeys::Condition_list *list);

    //! Are there uncommitted changes?
    bool hasChanges() const;

Q_SIGNALS:

    void changed(bool);

private Q_SLOTS:

    void slotNew(QAction*);
    void slotEdit();
    void slotDelete();

private:

    // Emit the changed(bool) signal if our changed status changes
    void emitChanged(bool);

    //! The original
    KHotKeys::Condition_list *_conditions_list;

    //! The working copy
    KHotKeys::Condition_list *_working;

    //! User Interface Definition
    Ui::ConditionsWidget ui;

    //! Are there uncommited changes?
    bool _changed;

    //! Map between treewidgetitems and conditions
    QMap<QTreeWidgetItem*, KHotKeys::Condition*> _items;

};


#endif /* #ifndef CONDITIONS_WIDGET_H */
