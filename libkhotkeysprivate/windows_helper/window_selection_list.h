#ifndef WINDOW_SELECTION_LIST_H
#define WINDOW_SELECTION_LIST_H
/* SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: GPL-2.0-only

#include "windows_helper/window_selection_interface.h"

#include <QList>

namespace KHotKeys {


class Q_DECL_EXPORT Windowdef_list : public QList< Windowdef* >
    {
    Q_DISABLE_COPY( Windowdef_list )

    public:
        Windowdef_list( const QString& comment = "" );
        Windowdef_list( KConfigGroup& cfg_P/*, ActionDataBase* data_P*/ );

        ~Windowdef_list();

        void cfg_write( KConfigGroup& cfg_P ) const;
        bool match( const Window_data& window_P ) const;
        Windowdef_list* copy( /*ActionDataBase* data_P*/ ) const;
        // typedef QList< Windowdef* >::iterator Iterator;
        void set_comment(const QString &comment);
        const QString& comment() const;
    private:
        QString _comment;
    };


} // namespace KHotKeys

#endif /* #ifndef WINDOW_SELECTION_LIST_H */
