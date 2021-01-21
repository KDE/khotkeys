/* SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "gesture_widget.h"
#include "helper_widgets/edit_gesture_dialog.h"

GestureWidget::GestureWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    connect(ui.edit_button, SIGNAL(clicked(bool)), SLOT(edit()));
}

GestureWidget::~GestureWidget()
{
}

void GestureWidget::edit()
{
    EditGestureDialog dia(ui.gesture->pointData());
    switch (dia.exec()) {
    case QDialog::Accepted:
        setPointData(dia.pointData(), true);
        break;

    case QDialog::Rejected:
        break;

    default:
        Q_ASSERT(false);
    }
}

KHotKeys::StrokePoints GestureWidget::pointData() const
{
    return ui.gesture->pointData();
}

void GestureWidget::setPointData(const KHotKeys::StrokePoints &data, bool emitSignal)
{
    ui.gesture->setPointData(data);
    if (emitSignal)
        emit changed();
}

#include "moc_gesture_widget.cpp"
