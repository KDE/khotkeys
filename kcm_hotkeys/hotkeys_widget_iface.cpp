/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "hotkeys_widget_iface.h"


HotkeysWidgetIFace::HotkeysWidgetIFace( QWidget *parent )
        : QWidget(parent)
         ,_changedSignals(new QSignalMapper(this))
    {
    // Listen to the signal mapper, but not yet
    connect(
        _changedSignals, SIGNAL(mapped(QString)),
        this, SLOT(slotChanged(QString)) );
    _changedSignals->blockSignals(true);
    }


HotkeysWidgetIFace::~HotkeysWidgetIFace()
    {}


void HotkeysWidgetIFace::apply()
    {
    copyToObject();
    }


void HotkeysWidgetIFace::copyFromObject()
    {
    _changedSignals->blockSignals(true);
    doCopyFromObject();
    _changedSignals->blockSignals(false);
    }

void HotkeysWidgetIFace::copyToObject()
    {
    doCopyToObject();
    }


void HotkeysWidgetIFace::slotChanged( const QString & /* what */ )
    {
    emit changed(isChanged());
    }




#include "moc_hotkeys_widget_iface.cpp"
