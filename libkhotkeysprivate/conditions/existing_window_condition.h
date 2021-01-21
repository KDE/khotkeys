#ifndef EXISTING_WINDOW_CONDITION_H
#define EXISTING_WINDOW_CONDITION_H
/* SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>
   SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>

   SPDX-License-Identifier: LGPL-2.0-only
*/

#include "conditions/condition.h"

#include <QObject>
#include <QString>
#include <QWindowList>

#include <KConfig> // Needed because of some Qt Status redefinitions
#include <KConfigGroup> // Needed because of some Qt Status redefinitions
#include <config-X11.h>

#if HAVE_X11
#include <X11/Xlib.h>
#include <fixx11h.h>
#else
#define None 0
#endif

namespace KHotKeys
{
class Condition_list_base;
class Windowdef_list;

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class Q_DECL_EXPORT Existing_window_condition : public QObject, public Condition
{
    Q_OBJECT
    typedef Condition base;

public:
    Existing_window_condition(Windowdef_list *window_P, Condition_list_base *parent = nullptr);
    Existing_window_condition(KConfigGroup &cfg_P, Condition_list_base *parent_P);
    virtual ~Existing_window_condition();
    bool match() const Q_DECL_OVERRIDE;
    void cfg_write(KConfigGroup &cfg_P) const Q_DECL_OVERRIDE;
    const Windowdef_list *window() const;
    Windowdef_list *window();
    Existing_window_condition *copy() const Q_DECL_OVERRIDE;
    const QString description() const Q_DECL_OVERRIDE;
public Q_SLOTS:
    void window_added(WId w_P);
    void window_removed(WId w_P);

private:
    void init();
    void set_match(WId w_P = None);
    Windowdef_list *_window;
    bool is_match;
};

} // namespace KHotKeys

#endif /* #ifndef EXISTING_WINDOW_CONDITION_H */
