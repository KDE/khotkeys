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
    bool match() const override;
    void cfg_write(KConfigGroup &cfg_P) const override;
    Not_condition *copy() const override;
    const QString description() const override;
    const Condition *condition() const;
    bool accepts_children() const override;
};

class Q_DECL_EXPORT And_condition : public Condition_list_base
{
    typedef Condition_list_base base;

public:
    And_condition(Condition_list_base *parent = nullptr);
    And_condition(KConfigGroup &cfg_P, Condition_list_base *parent_P);
    bool match() const override;
    void cfg_write(KConfigGroup &cfg_P) const override;
    And_condition *copy() const override;
    const QString description() const override;
};

class Q_DECL_EXPORT Or_condition : public Condition_list_base
{
    typedef Condition_list_base base;

public:
    Or_condition(Condition_list_base *parent = nullptr);
    Or_condition(KConfigGroup &cfg_P, Condition_list_base *parent_P);
    bool match() const override;
    void cfg_write(KConfigGroup &cfg_P) const override;
    Or_condition *copy() const override;
    const QString description() const override;
};

} // namespace KHotKeys

#endif // #define CONDITIONS_H
