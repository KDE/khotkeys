/****************************************************************************

 KHotKeys
 
 Copyright (C) 2003 Lubos Lunak <l.lunak@kde.org>

 Distributed under the terms of the GNU General Public License version 2.
 
****************************************************************************/

#define _GENERAL_SETTINGS_TAB_CPP_



#include "general_settings_tab.h"

#include <QCheckBox>

#include "kcmkhotkeys.h"

namespace KHotKeys
{

General_settings_tab::General_settings_tab( QWidget* parent_P, const char* name_P )
    : General_settings_tab_ui( parent_P )
    {
    setObjectName(name_P);
    // KHotKeys::Module::changed()
    connect( disable_daemon_checkbox, SIGNAL( clicked()),
        module, SLOT( changed()));
    connect( import_button,SIGNAL(clicked()),this,SLOT(import_clicked()));

    }

void General_settings_tab::import_clicked()
    {
    module->import();
    }

void General_settings_tab::write_data() const
    {
    module->set_daemon_disabled( disable_daemon_checkbox->isChecked());
    }

void General_settings_tab::read_data()
    {
    disable_daemon_checkbox->setChecked( module->daemon_disabled());
    }

void General_settings_tab::clear_data()
    {
    // "global" tab, not action specific, do nothing
    }

} // namespace KHotKeys

#include "general_settings_tab.moc"
