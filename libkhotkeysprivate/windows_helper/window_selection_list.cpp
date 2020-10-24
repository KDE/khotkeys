/* SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: GPL-2.0-only


#include "windows_helper/window_selection_list.h"

#include <KConfig>
#include <QDebug>


namespace KHotKeys {


Windowdef_list::Windowdef_list( const QString& comment_P )
    : QList< Windowdef* >(), _comment( comment_P )
    {
    }


Windowdef_list::Windowdef_list( KConfigGroup& cfg_P )
    : QList< Windowdef* >()
    {
    _comment = cfg_P.readEntry( "Comment" );
    int cnt = cfg_P.readEntry( "WindowsCount", 0 );
    for( int i = 0;
         i < cnt;
         ++i )
        {
        KConfigGroup windowGroup( cfg_P.config(), cfg_P.name() + QString::number( i ));
        Windowdef* window = Windowdef::create_cfg_read( windowGroup );
        if( window )
            append( window );
        }
    }


Windowdef_list::~Windowdef_list()
    {
    qDeleteAll(*this);
    }


const QString& Windowdef_list::comment() const
    {
    return _comment;
    }


void Windowdef_list::cfg_write( KConfigGroup& cfg_P ) const
    {
    int i = 0;
    for( ConstIterator it(begin());
         it!= end();
         ++it, ++i )
        {
        KConfigGroup itGroup( cfg_P.config(), cfg_P.name() + QString::number( i ) );
        (*it)->cfg_write( itGroup );
        }
    cfg_P.writeEntry( "WindowsCount", i );
    cfg_P.writeEntry( "Comment", comment());
    }


Windowdef_list* Windowdef_list::copy() const
    {
    Windowdef_list* ret = new Windowdef_list(comment());
    for( ConstIterator it(constBegin());
         it!= constEnd();
         ++it)
        {
        qDebug() << "Duplicating " << (*it)->comment();
        ret->append( (*it)->copy());
        }
    return ret;
    }


bool Windowdef_list::match( const Window_data& window_P ) const
    {
    if( count() == 0 ) // CHECKME no windows to match => ok
        return true;
    for( ConstIterator it(begin());
         it != end();
         ++it )
        if( (*it)->match( window_P ))
            return true;
    return false;
    }


void Windowdef_list::set_comment(const QString &comment)
    {
    _comment = comment;
    }


} // namespace KHotKeys
