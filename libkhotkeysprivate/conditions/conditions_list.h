#ifndef CONDITIONS_LIST_H
#define CONDITIONS_LIST_H
/* SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>
   SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>

   SPDX-License-Identifier: LGPL-2.0-only
*/

#include "conditions/conditions_list_base.h"

#include <QString>

class KConfigGroup;

namespace KHotKeys
{
class ActionDataBase;

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class Q_DECL_EXPORT Condition_list : public Condition_list_base
{
    typedef Condition_list_base base;

public:
    Condition_list(const QString &comment_P, ActionDataBase *parent = nullptr);
    Condition_list(KConfigGroup &cfg_P, ActionDataBase *data_P);
    void cfg_write(KConfigGroup &cfg_P) const Q_DECL_OVERRIDE;
    Condition_list *copy() const Q_DECL_OVERRIDE;
    bool match() const Q_DECL_OVERRIDE;
    const QString &comment() const;
    void set_data(ActionDataBase *data_P);
    void updated() const Q_DECL_OVERRIDE;
    const QString description() const Q_DECL_OVERRIDE;

    void visit(ConditionsVisitor *visitor) Q_DECL_OVERRIDE;

private:
    QString _comment;
    ActionDataBase *data;
};

} // namespace KHotKeys

#endif /* #ifndef CONDITIONS_LIST_H */
