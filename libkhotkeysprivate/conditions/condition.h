#ifndef CONDITION_H
#define CONDITION_H
/* SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>
   SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>

   SPDX-License-Identifier: LGPL-2.0-only
*/

#include <QObject>
#include <QString>

class KConfigGroup;


namespace KHotKeys {

class ConditionsVisitor;
class Condition_list_base;

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class Q_DECL_EXPORT Condition
    {
    Q_DISABLE_COPY( Condition )

    public:
        Condition( Condition_list_base* parent_P = nullptr );
        Condition( KConfigGroup& cfg_P, Condition_list_base* parent_P );
        virtual ~Condition();
        virtual bool match() const = 0;
        virtual void updated() const; // called when the condition changes
        virtual void cfg_write( KConfigGroup& cfg_P ) const = 0;
        virtual const QString description() const = 0;
        virtual Condition* copy() const = 0;
        const Condition_list_base* parent() const;
        Condition_list_base* parent();
        static Condition* create_cfg_read( KConfigGroup& cfg_P, Condition_list_base* parent_P );

        // Reparent the condition to another list.
        void reparent(Condition_list_base *parent);

        virtual void visit( ConditionsVisitor *visitor );

    protected:

        Condition_list_base* _parent;
    };


} // namespace KHotKeys

#endif /* #ifndef CONDITION_H */
