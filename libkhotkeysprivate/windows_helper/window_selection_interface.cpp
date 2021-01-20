/* SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: GPL-2.0-only
*/

#include "window_selection_rules.h"

#include <QDebug>


namespace KHotKeys {

Windowdef::Windowdef( const QString& comment_P )
    : _comment( comment_P )
    {
    }


Windowdef::Windowdef( KConfigGroup& cfg_P )
    {
    _comment = cfg_P.readEntry( "Comment" );
    }


Windowdef::~Windowdef()
    {
    }


void Windowdef::cfg_write( KConfigGroup& cfg_P ) const
    {
    cfg_P.writeEntry( "Type", "ERROR" );
    cfg_P.writeEntry( "Comment", comment());
    }


const QString& Windowdef::comment() const
    {
    return _comment;
    }


Windowdef* Windowdef::create_cfg_read( KConfigGroup& cfg_P )
    {
    QString type = cfg_P.readEntry( "Type" );
    if( type == "SIMPLE" )
        return new Windowdef_simple( cfg_P );
    qWarning() << "Unknown Windowdef type read from cfg file\n";
    return nullptr;
    }


void Windowdef::set_comment(const QString &comment)
    {
    _comment = comment;
    }



} // namespace KHotKeys
