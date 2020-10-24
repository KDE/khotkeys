/*
    SPDX-License-Identifier: GPL-2.0-only
    SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
 */

#ifndef KHOTKEYS_INPUT_H
#define KHOTKEYS_INPUT_H

namespace KHotKeys
{

class Mouse
    {
    public:
        static bool send_mouse_button( int button_P, bool release_P );
    };

} // namespace KHotKeys

#endif
