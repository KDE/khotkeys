/*
   SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-only
*/

#include "actions.h"

#include "input.h"
#include "windows_handler.h"
#include "shortcuts_handler.h"
#include "windows_helper/window_selection_list.h"

#include <KConfigGroup>
#include <KSharedConfig>
#include <QDebug>

// #include <X11/X.h>
#include <X11/Xlib.h>
#include <QX11Info>

/*
*/

namespace KHotKeys {

KeyboardInputActionVisitor::~KeyboardInputActionVisitor()
    {}


KeyboardInputAction::KeyboardInputAction(
        ActionData* data_P,
        const QString& input_P,
        Windowdef_list* dest_window_P,
        bool active_window_P)
    :   Action( data_P ),
        _input( input_P ),
        _dest_window( dest_window_P )
    {
    if (dest_window_P) _destination = SpecificWindow;
    else if (active_window_P) _destination = ActiveWindow;
    else _destination = ActionWindow;

    if (!_dest_window) _dest_window = new Windowdef_list;
    }


KeyboardInputAction::~KeyboardInputAction()
    {
    delete _dest_window;
    }


void KeyboardInputAction::accept(ActionVisitor& visitor)
    {
    if (KeyboardInputActionVisitor *v = dynamic_cast<KeyboardInputActionVisitor*>(&visitor))
        {
        v->visit(*this);
        }
    else
        {
        qDebug() << "Visitor error";
        }
    }


const QString& KeyboardInputAction::input() const
    {
    return _input;
    }


void KeyboardInputAction::setDestination(const DestinationWindow & dest)
    {
    _destination = dest;
    }


void KeyboardInputAction::setDestinationWindowRules(Windowdef_list *list)
    {
    if (_dest_window)
        delete _dest_window;

    _dest_window = list;
    }


void KeyboardInputAction::setInput(const QString &input)
    {
    _input = input;
    }


const Windowdef_list* KeyboardInputAction::dest_window() const
    {
    return _dest_window;
    }


Windowdef_list* KeyboardInputAction::dest_window()
    {
    return _dest_window;
    }


KeyboardInputAction::DestinationWindow KeyboardInputAction::destination() const
    {
    return _destination;
    }


void KeyboardInputAction::cfg_write( KConfigGroup& cfg_P ) const
    {
    base::cfg_write( cfg_P );
    cfg_P.writeEntry( "Type", "KEYBOARD_INPUT" ); // overwrites value set in base::cfg_write()
    cfg_P.writeEntry( "Input", input());

    cfg_P.writeEntry( "DestinationWindow", int(_destination) );

    if( _destination == SpecificWindow && dest_window() != nullptr )
        {
        KConfigGroup windowGroup( cfg_P.config(), cfg_P.name() + "DestinationWindow" );
        dest_window()->cfg_write( windowGroup );
        }
    }


void KeyboardInputAction::execute()
    {
    qDebug();

    if( input().isEmpty())
        {
        qDebug() << "Input is empty";
        return;
        }

    Window w = InputFocus;
    switch (_destination)
        {
        case SpecificWindow:
            Q_ASSERT(dest_window());
            w = windows_handler->find_window(dest_window());
            if (w == None) w = InputFocus;
            break;

        case ActionWindow:
            w = windows_handler->action_window();
            if (w == None) w = InputFocus;
            break;

        case ActiveWindow:
            // Nothing to do because w is InputFocus already
            break;

        default:
            Q_ASSERT(false);
        }

    int last_index = -1, start = 0;
    while(( last_index = input().indexOf( ':', last_index + 1 )) != -1 ) // find next ';'
        {
        QString key = input().mid( start, last_index - start ).trimmed();
        keyboard_handler->send_macro_key( key, w );
        start = last_index + 1;
        }
    // and the last one
    QString key = input().mid( start, input().length()).trimmed();
    keyboard_handler->send_macro_key( key, w ); // the rest
    if (QX11Info::isPlatformX11())
        XFlush( QX11Info::display());
    }


const QString KeyboardInputAction::description() const
    {
    QString tmp = input();
    tmp.replace( '\n', ' ' );
    tmp.truncate( 30 );
    return i18n( "Keyboard input: " ) + tmp;
    }


Action* KeyboardInputAction::copy( ActionData* data_P ) const
    {
    return new KeyboardInputAction(
            data_P,
            input(),
            dest_window() ? dest_window()->copy() : nullptr,
            _destination == ActiveWindow);
    }

} // namespace KHotKeys

