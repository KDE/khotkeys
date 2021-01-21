#ifndef GESTURE_WIDGET_H
#define GESTURE_WIDGET_H
/* SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
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
