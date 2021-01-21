/*
   SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-only
*/

#include "action_data.h"
#include "triggers.h"
#include "voices.h"
#include "windows.h"

#include <KConfigGroup>
#include <QDebug>

namespace KHotKeys
{
Voice_trigger::Voice_trigger(ActionData *data_P, const QString &Voicecode_P, const VoiceSignature &signature1_P, const VoiceSignature &signature2_P)
    : Trigger(data_P)
    , _voicecode(Voicecode_P)
{
    _voicesignature[0] = signature1_P;
    _voicesignature[1] = signature2_P;
}

Voice_trigger::Voice_trigger(KConfigGroup &cfg_P, ActionData *data_P)
    : Trigger(cfg_P, data_P)
{
    _voicecode = cfg_P.readEntry("Name");
    _voicesignature[0].read(cfg_P, "Signature1");
    _voicesignature[1].read(cfg_P, "Signature2");
}

Voice_trigger::~Voice_trigger()
{
    voice_handler->unregister_handler(this);
}

void Voice_trigger::cfg_write(KConfigGroup &cfg_P) const
{
    base::cfg_write(cfg_P);
    cfg_P.writeEntry("Name", voicecode());
    cfg_P.writeEntry("Type", "VOICE"); // overwrites value set in base::cfg_write()
    _voicesignature[0].write(cfg_P, "Signature1");
    _voicesignature[1].write(cfg_P, "Signature2");
}

Trigger *Voice_trigger::copy(ActionData *data_P) const
{
    qDebug() << "Voice_trigger::copy()";
    return new Voice_trigger(data_P ? data_P : data, voicecode(), voicesignature(1), voicesignature(2));
}

const QString Voice_trigger::description() const
{
    return i18n("Voice trigger: ") + voicecode();
}

void Voice_trigger::handle_Voice()
{
    windows_handler->set_action_window(0); // use active window
    data->execute();
}

void Voice_trigger::activate(bool activate_P)
{
    if (activate_P && khotkeys_active())
        voice_handler->register_handler(this);
    else
        voice_handler->unregister_handler(this);
}

} // namespace KHotKeys
