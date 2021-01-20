/* SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>

   SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef WINDOWS_HANDLER_H
#define WINDOWS_HANDLER_H

#include <QObject>
#include <QWindowList>

#include <netwm.h>

namespace KHotKeys
{

const NET::WindowTypes SUPPORTED_WINDOW_TYPES_MASK = NET::NormalMask | NET::DesktopMask | NET::DockMask
    | NET::ToolbarMask | NET::MenuMask | NET::DialogMask | NET::OverrideMask | NET::TopMenuMask
    | NET::UtilityMask | NET::SplashMask;


class Windowdef_list;

class Q_DECL_EXPORT WindowsHandler : public QObject
    {
    Q_OBJECT
    public:
        WindowsHandler( bool enable_signals_P, QObject* parent_P );
        virtual ~WindowsHandler();
        QString get_window_class( WId id_P );
        QString get_window_role( WId id_P );
        WId active_window();
        void set_action_window( WId window );
        WId action_window();
        WId find_window( const Windowdef_list* window_P );
        static WId window_at_position( int x, int y );
        static void activate_window( WId id_P );
    Q_SIGNALS:
        void window_added( WId window_P );
        void window_removed( WId window_P );
        void active_window_changed( WId window_P );
        void window_changed( WId window_P );
        void window_changed( WId window_P, unsigned int flags_P );
    protected Q_SLOTS:
        void window_added_slot( WId window_P );
        void window_removed_slot( WId window_P );
        void active_window_changed_slot( WId window_P );
        void window_changed_slot( WId window_P );
        void window_changed_slot( WId window_P, unsigned int flags_P );
    private:
        bool signals_enabled;
        WId _action_window;
        bool m_isX11;
    };


} // namespace KHotKeys

#endif
