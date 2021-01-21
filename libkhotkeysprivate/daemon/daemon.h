#ifndef DAEMON_H
#define DAEMON_H
/* SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include <qglobal.h>

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
namespace KHotKeys
{
namespace Daemon
{
Q_DECL_EXPORT bool isRunning();
Q_DECL_EXPORT bool reload();
Q_DECL_EXPORT bool start();
Q_DECL_EXPORT bool stop();

/**
 * Is the daemon enabled by the user?
 */
Q_DECL_EXPORT bool isEnabled();
}

} // namespace KHotKeys::Daemon

#endif /* #ifndef DAEMON_H */
