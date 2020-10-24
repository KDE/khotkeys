#ifndef CONDITIONS_VISITOR_H
#define CONDITIONS_VISITOR_H
/* SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>
   SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>

   SPDX-License-Identifier: LGPL-2.0-only
*/

#include <qglobal.h>

namespace KHotKeys {
    class Condition_list_base;
    class Condition_list;
    class Condition;


/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class Q_DECL_EXPORT ConditionsVisitor
    {
public:

    ConditionsVisitor( bool recurse = true );
    virtual ~ ConditionsVisitor();

    virtual void visitCondition( Condition *condition ) = 0;
    virtual void visitConditionsList( Condition_list *list) = 0;
    virtual void visitConditionsListBase( Condition_list_base *list) = 0;

private:

    bool _recurse;

    }; // class ConditionsVisitor


} // namespace KHotKeys


#endif /* #ifndef CONDITIONS_VISITOR_H */
