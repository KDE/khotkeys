#ifndef CONDITIONS_LIST_BASE_H
#define CONDITIONS_LIST_BASE_H
/* SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>
   SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>

   SPDX-License-Identifier: LGPL-2.0-only
*/

#include "conditions/condition.h"

#include <QList>

class KConfigGroup;

namespace KHotKeys
{
class ConditionsVisitor;

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class Q_DECL_EXPORT Condition_list_base : public Condition, private QList<Condition *>
{
    typedef Condition base;

public:
    Condition_list_base(Condition_list_base *parent = nullptr);

    Condition_list_base(const QList<Condition *> &children_P, Condition_list_base *parent_P);

    Condition_list_base(KConfigGroup &cfg_P, Condition_list_base *parent_P);

    virtual ~Condition_list_base();

    void cfg_write(KConfigGroup &cfg_P) const Q_DECL_OVERRIDE;
    virtual bool accepts_children() const;

    typedef QList<Condition *>::iterator Iterator;
    typedef QList<Condition *>::const_iterator ConstIterator;

    void append(Condition *);

    Iterator begin();
    ConstIterator begin() const;

    Iterator end();
    ConstIterator end() const;

    Condition *first();
    Condition const *first() const;

    int count() const;

    bool isEmpty() const;

    void clear();

    void visit(ConditionsVisitor *visitor) Q_DECL_OVERRIDE;

protected:
    int removeAll(Condition *const &);

    friend class Condition;
};

} // namespace KHotKeys

#endif /* #ifndef CONDITIONS_LIST_BASE_H */
