/*
    SPDX-License-Identifier: GPL-2.0-only
    SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
 */

#ifndef CONDITIONS_H
#define CONDITIONS_H

#include "conditions/conditions_list_base.h"

#include "action_data/action_data_group.h"
#include "windows_handler.h"

class KConfigGroup;

namespace KHotKeys
{
class Condition;

class Q_DECL_EXPORT Not_condition : public Condition_list_base
{
    typedef Condition_list_base base;

public:
    Not_condition(Condition_list_base *parent = nullptr);
    Not_condition(KConfigGroup &cfg_P, Condition_list_base *parent_P);
    bool match() const Q_DECL_OVERRIDE;
    void cfg_write(KConfigGroup &cfg_P) const Q_DECL_OVERRIDE;
    Not_condition *copy() const Q_DECL_OVERRIDE;
    const QString description() const Q_DECL_OVERRIDE;
    const Condition *condition() const;
    bool accepts_children() const Q_DECL_OVERRIDE;
};

class Q_DECL_EXPORT And_condition : public Condition_list_base
{
    typedef Condition_list_base base;

public:
    And_condition(Condition_list_base *parent = nullptr);
    And_condition(KConfigGroup &cfg_P, Condition_list_base *parent_P);
    bool match() const Q_DECL_OVERRIDE;
    void cfg_write(KConfigGroup &cfg_P) const Q_DECL_OVERRIDE;
    And_condition *copy() const Q_DECL_OVERRIDE;
    const QString description() const Q_DECL_OVERRIDE;
};

class Q_DECL_EXPORT Or_condition : public Condition_list_base
{
    typedef Condition_list_base base;

public:
    Or_condition(Condition_list_base *parent = nullptr);
    Or_condition(KConfigGroup &cfg_P, Condition_list_base *parent_P);
    bool match() const Q_DECL_OVERRIDE;
    void cfg_write(KConfigGroup &cfg_P) const Q_DECL_OVERRIDE;
    Or_condition *copy() const Q_DECL_OVERRIDE;
    const QString description() const Q_DECL_OVERRIDE;
};

} // namespace KHotKeys

#endif // #define CONDITIONS_H
