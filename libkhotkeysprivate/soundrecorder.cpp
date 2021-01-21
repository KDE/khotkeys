/*
 *   SPDX-FileCopyrightText: 2005 Olivier Goffart <ogoffart@kde.org>
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "soundrecorder.h"

#include <QDebug>
#include <QTimer>
#include <klibrary.h>
#include <klocale.h>

#include "khotkeysglobal.h"

namespace KHotKeys
{
SoundRecorder::create_ptr SoundRecorder::create_fun = NULL;

bool SoundRecorder::init(KLibrary *lib)
{
#ifdef HAVE_ARTS
    if (create_fun == NULL && lib != NULL)
        create_fun = (create_ptr)lib->symbol("khotkeys_soundrecorder_create");
#endif
    //    qDebug() << "soundrecorder:" << create_fun << ":" << lib;
    return create_fun != NULL;
}

SoundRecorder *SoundRecorder::create(QObject *parent)
{
#ifdef HAVE_ARTS
    if (create_fun != NULL)
        return create_fun(parent, name);
#endif
    return new SoundRecorder(parent);
}

SoundRecorder::SoundRecorder(QObject *parent)
    : QObject(parent)
{
}

SoundRecorder::~SoundRecorder()
{
}

void SoundRecorder::start()
{
}

void SoundRecorder::stop()
{
}

void SoundRecorder::abort()
{
}

Sound SoundRecorder::sound()
{
    Sound s;
    return s;
}

}

#include "soundrecorder.moc"
