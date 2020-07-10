/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include <config-X11.h>

#include "input.h"
#include "shortcuts_handler.h"
#include "windows_handler.h"
#include "khotkeysglobal.h"


// #include <X11/Xutil.h>
#include <QX11Info>

#include <QDebug>
#include <KGlobalAccel>
#include <KLocalizedString>
#include <QKeySequence>

#include <QAction>
#include <QUuid>
#include <kkeyserver.h>

namespace KHotKeys {


ShortcutsHandler::ShortcutsHandler( HandlerType type, QObject *parent )
        : QObject(parent)
         ,_type(type)
         ,_actions(new KActionCollection(this, QStringLiteral("khotkeys")))
    {
    _actions->setComponentDisplayName(i18n("Custom Shortcuts Service"));
    connect(KGlobalAccel::self(), &KGlobalAccel::globalShortcutChanged, this, &ShortcutsHandler::shortcutChanged);
    }


ShortcutsHandler::~ShortcutsHandler()
    {
    _actions->clear();
    delete _actions;
    }


QAction *ShortcutsHandler::addAction(
        const QString &id,
        const QString &text,
        const QKeySequence &shortcut )
    {
#ifdef KHOTKEYS_TRACE
    qDebug() << id << text << shortcut;
#endif
    QString realId(id);
    // HACK: Do this correctly. Remove uuid on importing / exporting
    // On import it can happen that id is already taken. Create it under a
    // different name then.
    if (_actions->action(id))
        {
        qDebug() << id << " already present. Using new id!";
        realId = QUuid::createUuid().toString();
        }

    // Create the action
    QAction *newAction = _actions->addAction(realId);
    if (!newAction)
        {
        return nullptr;
        }
    // If our HandlerType is configuration we have to tell kdedglobalaccel
    // that this action is only for configuration purposes.
    // see KAction::~KAction
    if (_type==Configuration)
        {
        newAction->setProperty("isConfigurationAction", QVariant(true));
        }
    newAction->setText(text);
    KGlobalAccel::self()->setShortcut(newAction, QList<QKeySequence>() << shortcut);
    // Enable global shortcut. If that fails there is no sense in proceeding
    if (!KGlobalAccel::self()->hasShortcut(newAction))
        {
        qWarning() << "Failed to enable global shortcut for '" 
                   << text << "' " << id;
        _actions->removeAction(newAction);
        return nullptr;
        }
    Q_ASSERT(newAction->isEnabled());

    return newAction;
    }


QAction *ShortcutsHandler::getAction( const QString &id )
    {
    return _actions->action(id);
    }


bool ShortcutsHandler::removeAction( const QString &id )
    {
    QAction *action = getAction( id );
    if (!action)
        {
        return false;
        }
    else
        {
        // This will delete the action.
        _actions->removeAction(action);

        return true;
        }
    }


#ifdef HAVE_XTEST

} // namespace KHotKeys
#include <X11/extensions/XTest.h>
namespace KHotKeys
{

static bool xtest_available = false;
static bool xtest_inited = false;
static bool xtest()
    {
    if( xtest_inited )
        return xtest_available;
    xtest_inited = true;
    int dummy1, dummy2, dummy3, dummy4;
    xtest_available =
        ( XTestQueryExtension( QX11Info::display(), &dummy1, &dummy2, &dummy3, &dummy4 ) == True );
    return xtest_available;
    }

static void get_modifier_change(int x_mod_needed, QVector<int> &to_press, QVector<int> &to_release)
{
    // Get state of all keys
    char keymap[32];
    XQueryKeymap(QX11Info::display(), keymap);

    // From KKeyServer's initializeMods()
    XModifierKeymap *xmk = XGetModifierMapping( QX11Info::display() );

    for (int modidx = 0; modidx < 8; ++modidx) {
        bool mod_needed = x_mod_needed & (1 << modidx);
        for (int kcidx = 0; kcidx < xmk->max_keypermod; ++kcidx) {
            int keycode = xmk->modifiermap[modidx * xmk->max_keypermod + kcidx];
            if(!keycode)
                continue;

            bool mod_pressed = keymap[keycode / 8] & (1 << (keycode % 8));
            if(mod_needed) {
                mod_needed = false;
                if(!mod_pressed)
                    to_press.push_back(keycode);
            } else if(mod_pressed)
                to_release.push_back(keycode);
        }
    }

    XFreeModifiermap(xmk);
}

#endif

bool ShortcutsHandler::send_macro_key( const QKeySequence &key, Window window_P )
    {
    if (key.isEmpty())
        return false;

    unsigned int keysym = key[0];
    int x_keycode;
    KKeyServer::keyQtToCodeX(keysym, &x_keycode);
    if( x_keycode == NoSymbol )
        return false;

    unsigned int x_mod;
    KKeyServer::keyQtToModX(keysym, &x_mod );
#ifdef HAVE_XTEST
    if( xtest() && window_P == None )
        {
        QVector<int> keycodes_to_press, keycodes_to_release;
        get_modifier_change(x_mod, keycodes_to_press, keycodes_to_release);

        for(int kc : qAsConst(keycodes_to_release))
            XTestFakeKeyEvent( QX11Info::display(), kc, False, CurrentTime );

        for(int kc : qAsConst(keycodes_to_press))
            XTestFakeKeyEvent( QX11Info::display(), kc, True, CurrentTime );

        bool ret = XTestFakeKeyEvent( QX11Info::display(), x_keycode, True, CurrentTime );
        ret = ret && XTestFakeKeyEvent( QX11Info::display(), x_keycode, False, CurrentTime );

        for(int kc : qAsConst(keycodes_to_press))
            XTestFakeKeyEvent( QX11Info::display(), kc, False, CurrentTime );

        for(int kc : qAsConst(keycodes_to_release))
            XTestFakeKeyEvent( QX11Info::display(), kc, True, CurrentTime );

        return ret;
        }
#endif
    if( window_P == None || window_P == InputFocus )
        window_P = windows_handler->active_window();
    if( window_P == None ) // CHECKME tohle cele je ponekud ...
        window_P = InputFocus;
    XEvent ev;
    ev.type = KeyPress;
    ev.xkey.display = QX11Info::display();
    ev.xkey.window = window_P;
    ev.xkey.root = QX11Info::appRootWindow();   // I don't know whether these have to be set
    ev.xkey.subwindow = None;       // to these values, but it seems to work, hmm
    ev.xkey.time = CurrentTime;
    ev.xkey.x = 0;
    ev.xkey.y = 0;
    ev.xkey.x_root = 0;
    ev.xkey.y_root = 0;
    ev.xkey.keycode = x_keycode;
    ev.xkey.state = x_mod;
    ev.xkey.same_screen = True;
    bool ret = XSendEvent( QX11Info::display(), window_P, True, KeyPressMask, &ev );
#if 1
    ev.type = KeyRelease;  // is this actually really needed ??
    ev.xkey.display = QX11Info::display();
    ev.xkey.window = window_P;
    ev.xkey.root = QX11Info::appRootWindow();
    ev.xkey.subwindow = None;
    ev.xkey.time = CurrentTime;
    ev.xkey.x = 0;
    ev.xkey.y = 0;
    ev.xkey.x_root = 0;
    ev.xkey.y_root = 0;
    ev.xkey.state = x_mod;
    ev.xkey.keycode = x_keycode;
    ev.xkey.same_screen = True;
    ret = ret && XSendEvent( QX11Info::display(), window_P, True, KeyReleaseMask, &ev );
#endif
    // Qt's autorepeat compression is broken and can create "aab" from "aba"
    // XSync() should create delay longer than Qt's max autorepeat interval
    XSync( QX11Info::display(), False );
    return ret;
    }


bool Mouse::send_mouse_button( int button_P, bool release_P )
    {
#ifdef HAVE_XTEST
    if( xtest())
        {
        // CHECKME tohle jeste potrebuje modifikatory
        // a asi i spravnou timestamp misto CurrentTime
        bool ret = XTestFakeButtonEvent( QX11Info::display(), button_P, True, CurrentTime );
        if( release_P )
            ret = ret && XTestFakeButtonEvent( QX11Info::display(), button_P, False, CurrentTime );
        return ret;
        }
#endif
    return false;
    }

} // namespace KHotKeys

#include "moc_shortcuts_handler.cpp"
