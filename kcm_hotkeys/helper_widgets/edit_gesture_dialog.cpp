/* SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "edit_gesture_dialog.h"

#include <KLocalizedString>

#include <QLabel>
#include <QLayout>
#include <QDialogButtonBox>


EditGestureDialog::EditGestureDialog(const KHotKeys::StrokePoints &pointData, QWidget *parent)
    :   QDialog(parent)
        ,_recorder(this)
        ,_pointData(pointData)
    {
    setWindowTitle(i18n("Edit Gesture"));

    QString message(i18n(
                    "Draw the gesture you would like to record below. Press "
                    "and hold the left mouse button while drawing, and release "
                    "when you have finished."));

    QLabel *label = new QLabel(message, this);
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(&_recorder);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                       | QDialogButtonBox::Cancel);

    layout->addWidget(buttonBox);

    setLayout(layout);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(&_recorder, SIGNAL(recorded(KHotKeys::StrokePoints)),
            SLOT(recorded(KHotKeys::StrokePoints)));
    }


EditGestureDialog::~EditGestureDialog()
    {}


KHotKeys::StrokePoints EditGestureDialog::pointData() const
    {
    return _pointData;
    }


void EditGestureDialog::recorded(const KHotKeys::StrokePoints &data)
    {
    _pointData=data;
    accept();
    }


#include "moc_edit_gesture_dialog.cpp"
