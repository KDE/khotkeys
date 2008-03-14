/****************************************************************************

 KHotKeys
 
 Copyright (C) 1999-2002 Lubos Lunak <l.lunak@kde.org>

 Distributed under the terms of the GNU General Public License version 2.
 
****************************************************************************/

#define _GESTURE_TRIGGERS_TAB_CPP_



#include "gesture_triggers_tab.h"

#include <QPushButton>
#include <QLineEdit>

#include <triggers.h>
#include <actions.h> 
#include <action_data.h>

#include "kcmkhotkeys.h"
#include "gesturedrawer.h"
#include "gesturerecordpage.h"

namespace KHotKeys
{

Gesture_triggers_tab::Gesture_triggers_tab( QWidget* parent_P, const char* name_P )
    : Gesture_triggers_tab_ui( parent_P )
    {
    setObjectName(name_P);
    clear_data();
    connect(gesture_edit_button1,SIGNAL(clicked()),this,SLOT(edit_gesture_pressed1()));
    connect(gesture_edit_button2,SIGNAL(clicked()),this,SLOT(edit_gesture_pressed2()));
    connect(gesture_edit_button3,SIGNAL(clicked()),this,SLOT(edit_gesture_pressed3()));

    // KHotKeys::Module::changed()
    connect( gesture_edit_button1, SIGNAL( clicked()),
        module, SLOT( changed()));
    connect( gesture_edit_button2, SIGNAL( clicked()),
        module, SLOT( changed()));
    connect( gesture_edit_button3, SIGNAL( clicked()),
        module, SLOT( changed()));
    } 

void Gesture_triggers_tab::clear_data()
    {
    gesture1 = gesture2 = gesture3 = QString();
    gesture_lineedit1->clear();
    gesture_lineedit2->clear();
    gesture_lineedit3->clear();
    gesture_drawer1->setData( QString() );
    gesture_drawer2->setData( QString() );
    gesture_drawer3->setData( QString() );
    }
    
void Gesture_triggers_tab::set_data( const Trigger_list* triggers_P )
    {
    // FIXME: Rework this code
    if( triggers_P == 0 )
        {
        clear_data();
        return;
        }
    Gesture_trigger* trig = 0;
    Trigger_list::ConstIterator it = triggers_P->begin();
    if ( trig != 0 && it != triggers_P->end() )
        {
        Q_ASSERT( dynamic_cast< Gesture_trigger* >( *it ));
        trig = static_cast< Gesture_trigger* >( *it );
        }
    else
        trig = 0;
    gesture1 = trig ? trig->gesturecode() : QString();
    gesture_lineedit1->setText( gesture1 );
    gesture_drawer1->setData( gesture1 );
    ++it;
    if ( trig != 0 && it != triggers_P->end() )
        {
        Q_ASSERT( dynamic_cast< Gesture_trigger* >( *it ));
        trig = static_cast< Gesture_trigger* >( *it );
        }
    else
        trig = 0;
    gesture2 = trig ? trig->gesturecode() : QString();
    gesture_lineedit2->setText( gesture2 );
    gesture_drawer2->setData( gesture2 );
    ++it;
    if ( trig != 0 && it != triggers_P->end() )
        {
        Q_ASSERT( dynamic_cast< Gesture_trigger* >( *it ));
        trig = static_cast< Gesture_trigger* >( *it );
        }
    else
        trig = 0;
    gesture3 = trig ? trig->gesturecode() : QString();
    gesture_lineedit3->setText( gesture3 );
    gesture_drawer3->setData( gesture3 );
    }
    
Trigger_list* Gesture_triggers_tab::get_data( Action_data* data_P ) const
    {
    Trigger_list* ret = new Trigger_list( "Gesture_triggers" );
    if( !gesture1.isEmpty())
        ret->append( new Gesture_trigger( data_P, gesture1 ));
    if( !gesture2.isEmpty())
        ret->append( new Gesture_trigger( data_P, gesture2 ));
    if( !gesture3.isEmpty())
        ret->append( new Gesture_trigger( data_P, gesture3 ));
    return ret;
    }

void Gesture_triggers_tab::edit_gesture_pressed1()
    {
    Gesture_edit_dialog dlg( gesture1 );
    gesture1 = dlg.edit_gesture();
    gesture_lineedit1->setText( gesture1 );
    gesture_drawer1->setData( gesture1 );
    }

void Gesture_triggers_tab::edit_gesture_pressed2()
    {
    Gesture_edit_dialog dlg( gesture2 );
    gesture2 = dlg.edit_gesture();
    gesture_lineedit2->setText( gesture2 );
    gesture_drawer2->setData( gesture2 );
    }

void Gesture_triggers_tab::edit_gesture_pressed3()
    {
    Gesture_edit_dialog dlg( gesture3 );
    gesture3 = dlg.edit_gesture();
    gesture_lineedit3->setText( gesture3 );
    gesture_drawer3->setData( gesture3 );
    }

// Gesture_edit_dialog

Gesture_edit_dialog::Gesture_edit_dialog( const QString& gesture_P )
    : KDialog( 0 ), // CHECKME caption
        _gesture( gesture_P ), _page( 0 )
    {
    setModal( true );
    setButtons( Ok | Cancel );
    _page = new GestureRecordPage( _gesture,
                                  this, "GestureRecordPage");
   
//    connect(_page, SIGNAL(gestureRecorded(bool)), // allow clearing the gesture
//            this, SLOT(enableButtonOk(bool)));
   
    setMainWidget( _page );
    }

QString Gesture_edit_dialog::edit_gesture()
    {
    if( exec())
        return _page->getGesture();
    else
        return _gesture;
    }
    
} // namespace KHotKeys

#include "gesture_triggers_tab.moc"
