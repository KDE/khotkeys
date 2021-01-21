/*
   SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-only
*/

#include "triggers.h"

#include <KConfigGroup>
#include <QDebug>

namespace KHotKeys
{
TriggerVisitor::~TriggerVisitor()
{
}

Trigger::Trigger(ActionData *data_P)
    : data(data_P)
{
}

Trigger::~Trigger()
{
}

void Trigger::aboutToBeErased()
{
}

void Trigger::cfg_write(KConfigGroup &cfg_P) const
{
    cfg_P.writeEntry("Type", "ERROR");
}

void Trigger::enable()
{
}

void Trigger::disable()
{
}

} // namespace KHotKeys
