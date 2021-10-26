#ifndef ACTIVE_WINDOW_CONDITION_H
#define ACTIVE_WINDOW_CONDITION_H
/* SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>
   SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>

   SPDX-License-Identifier: LGPL-2.0-only
*/

#include "conditions/condition.h"

#include <QObject>

#include <QWindowList>

class KConfigGroup;

namespace KHotKeys
{
class Condition_list_base;
class Windowdef_list;

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class Q_DECL_EXPORT Active_window_condition : public QObject, public Condition
{
    Q_OBJECT
    typedef Condition base;

public:
    Active_window_condition(Windowdef_list *window_P, Condition_list_base *parent_P = nullptr);
    Active_window_condition(KConfigGroup &cfg_P, Condition_list_base *parent_P);
    ~Active_window_condition() override;
    bool match() const Q_DECL_OVERRIDE;
    void cfg_write(KConfigGroup &cfg_P) const Q_DECL_OVERRIDE;
    const Windowdef_list *window() const;
    Windowdef_list *window();
    Active_window_condition *copy() const Q_DECL_OVERRIDE;
    const QString description() const Q_DECL_OVERRIDE;
public Q_SLOTS:
    void active_window_changed(WId);

private:
    void init();
    void set_match();
    Windowdef_list *_window;
    bool is_match;
};

} // namespace KHotKeys

#endif /* #ifndef ACTIVE_WINDOW_CONDITION_H */
