/*
 *   SPDX-FileCopyrightText: 2005 Olivier Goffart <ogoffart@kde.org>
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */
#ifndef RECORDER_H
#define RECORDER_H

#include "sound.h"
#include <QObject>

class KLibrary;

namespace KHotKeys
{
/**
@author Olivier Goffart
*/
class Q_DECL_EXPORT SoundRecorder : public QObject
{
    Q_OBJECT
public:
    static SoundRecorder *create(QObject *parent = 0);
    virtual ~SoundRecorder();

    virtual void start();
    virtual void stop();
    virtual void abort();
    virtual Sound sound();

    static bool init(KLibrary *);
signals:
    void recorded(const Sound &);

protected:
    SoundRecorder(QObject *parent = 0);
    typedef SoundRecorder *(*create_ptr)(QObject *, const char *);

private:
    static create_ptr create_fun;
};

}

#endif
