#ifndef EDIT_GESTURE_DIALOG_H
#define EDIT_GESTURE_DIALOG_H
/* SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "helper_widgets/gesture_recorder.h"
#include "triggers/gestures.h"


#include <QDialog>

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
/**
 * This dialog is what pops up after clicking the edit button. It contains
 * a GestureRecorder to enable the input of a new gesture.
 */
class EditGestureDialog : public QDialog
    {
    Q_OBJECT

public:

    /**
     * Default constructor
     */
    EditGestureDialog(const KHotKeys::StrokePoints &pointData, QWidget *parent=nullptr);

    /**
     * Destructor
     */
    virtual ~EditGestureDialog();

    KHotKeys::StrokePoints pointData() const;

private Q_SLOTS:

    void recorded(const KHotKeys::StrokePoints &data);

private:

    GestureRecorder _recorder;
    KHotKeys::StrokePoints _pointData;

    };


#endif /* #ifndef EDIT_GESTURE_DIALOG_H */
