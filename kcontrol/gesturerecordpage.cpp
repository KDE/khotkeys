/****************************************************************************

 KHotKeys
 
 Copyright (C) 2003 Mike Pilone <mpilone@slac.com>
 Copyright (C) 2003 Lubos Lunak <l.lunak@kde.org>

 Distributed under the terms of the GNU General Public License version 2.
 
****************************************************************************/

#include <qwidget.h>
#include <qlabel.h>
#include <qpushbutton.h>

#include <klocale.h>
#include <kmessagebox.h>

#include "gesturerecordpage.h"
#include "gesturerecorder.h"
#include "gesturedrawer.h"

namespace KHotKeys
{

GestureRecordPage::GestureRecordPage(const QString &gesture,
                                     QWidget *parent, const char *name)
  : QVBox(parent, name),
    _recorder(NULL), _resetButton(NULL),
    _tryOne(NULL), _tryTwo(NULL), _tryThree(NULL), _gest(QString::null),
    _tryCount(1)
    {
    QString message;

    message = i18n("Draw the gesture you would like to record below. Press "
                   "and hold the left mouse button while drawing, and release "
                   "when you have finished.\n\n"
                   "You will be required to draw the gesture 3 times. After "
                   "each drawing, if they match, the indicators below will "
                   "change to represent which step you are on.\n\n"
                   "If at any point they do not match, you will be required to "
                   "restart. If you want to force a restart, use the reset "
                   "button below.\n\nDraw here:");

    QLabel *label = new QLabel(message, this, "label");
    label->setAlignment(QLabel::AlignLeft | QLabel::WordBreak |
                        QLabel::AlignVCenter);

    _recorder = new GestureRecorder(this, "recorder");
    _recorder->setMinimumHeight(150);
    setStretchFactor(_recorder, 1);
    connect(_recorder, SIGNAL(recorded(const QString &)),
            this, SLOT(slotRecorded(const QString &)));

    QHBox *hBox = new QHBox(this, "hbox");

    _tryOne = new GestureDrawer(hBox, "tryOne");
    _tryTwo = new GestureDrawer(hBox, "tryTwo");
    _tryThree = new GestureDrawer(hBox, "tryThree");

    QWidget *spacer = new QWidget(hBox, "spacer");
    hBox->setStretchFactor(spacer, 1);

    _resetButton = new QPushButton(i18n("&Reset"), hBox, "resetButton");
    connect(_resetButton, SIGNAL(clicked()),
            this, SLOT(slotResetClicked()));



  // initialize
    if (!gesture.isNull())
        {
        slotRecorded(gesture);
        slotRecorded(gesture);
        slotRecorded(gesture);
        }
    else
        emit gestureRecorded(false);
    }

GestureRecordPage::~GestureRecordPage()
    {
    }

void GestureRecordPage::slotRecorded(const QString &data)
    {
    switch (_tryCount)
        {
        case 1:
            {
            _gest = data;
            _tryOne->setData(_gest);
            _tryCount++;
            }
        break;

    case 2:
            {
            if (_gest == data)
                {
                _tryTwo->setData(data);
                _tryCount++;
                }
            else
                {
                KMessageBox::sorry(this, i18n("Your gestures did not match."));
                slotResetClicked();
                }
            break;
            }

        case 3:
            {
            if (_gest == data)
                {
                _tryThree->setData(data);
                _tryCount++;
                emit gestureRecorded(true);
                }
            else
                {
                KMessageBox::sorry(this, i18n("Your gestures did not match."));
                slotResetClicked();
                }
            break;
            }
        default:
            KMessageBox::information(this, i18n("You have already completed the three required drawings. Either press 'Ok' to save or 'Reset' to try again."));
        }
    }

void GestureRecordPage::slotResetClicked()
    {
    _gest = QString::null;

    _tryOne->setData(QString::null);
    _tryTwo->setData(QString::null);
    _tryThree->setData(QString::null);

    _tryCount = 1;

    emit gestureRecorded(false);
    }

} // namespace KHotKeys

#include "gesturerecordpage.moc"
