#ifndef WINDOW_SELECTION_INTERFACE_H
#define WINDOW_SELECTION_INTERFACE_H
/* SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: GPL-2.0-only
*/

#include <QString>

#include "KConfigGroup"

#include <QWindowList>

#include <netwm_def.h>

namespace KHotKeys
{
struct Q_DECL_EXPORT Window_data {
    Window_data(WId id_P);
    QString title; // _NET_WM_NAME or WM_NAME
    QString role; // WM_WINDOW_ROLE
    QString wclass; // WM_CLASS
    NET::WindowType type;
};

class Q_DECL_EXPORT Windowdef
{
    Q_DISABLE_COPY(Windowdef)

public:
    Windowdef(const QString &comment_P);
    Windowdef(KConfigGroup &cfg_P);
    virtual ~Windowdef();
    const QString &comment() const;
    void set_comment(const QString &comment);
    virtual bool match(const Window_data &window_P) = 0;
    static Windowdef *create_cfg_read(KConfigGroup &cfg_P /*, ActionDataBase* data_P*/);
    virtual void cfg_write(KConfigGroup &cfg_P) const = 0;
    virtual Windowdef *copy(/*ActionDataBase* data_P*/) const = 0;
    virtual const QString description() const = 0;

private:
    QString _comment;
};

} // namespace KHotKeys

#endif /* #ifndef WINDOW_SELECTION_INTERFACE_H */
