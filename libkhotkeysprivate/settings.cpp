/****************************************************************************

 KHotKeys

 Copyright (C) 1999-2001 Lubos Lunak <l.lunak@kde.org>

 Distributed under the terms of the GNU General Public License version 2.

****************************************************************************/

#define _SETTINGS_CPP_

#include "settings.h"

#include "action_data/action_data.h"
#include "action_data/menuentry_shortcut_action_data.h"
#include "action_data/command_url_shortcut_action_data.h"

#include <kconfig.h>
#include <kconfiggroup.h>
#include <kdebug.h>
#include <khotkeysglobal.h>
#include <klocale.h>
#include <kglobal.h>
#include <kmessagebox.h>

#include "triggers/triggers.h"
#include "conditions/conditions.h"

namespace KHotKeys
{

// Settings

Settings::Settings()
    : m_actions( NULL ), gestures_exclude( NULL )
    {
    }


Settings::~Settings()
    {
    delete m_actions; m_actions = 0;
    }


ActionDataGroup *Settings::actions()
    {
    return m_actions;
    }


bool Settings::areGesturesDisabled() const
    {
    return gestures_disabled;
    }


void Settings::disableDaemon()
    {
    daemon_disabled = true;
    }


void Settings::disableGestures()
    {
    gestures_disabled = true;
    }


void Settings::enableDaemon()
    {
    daemon_disabled = false;
    }


void Settings::enableGestures()
    {
    gestures_disabled = false;
    }


int Settings::gestureMouseButton() const
    {
    return gesture_mouse_button;
    }


Windowdef_list *Settings::gesturesExclude()
    {
    return gestures_exclude;
    }


const Windowdef_list *Settings::gesturesExclude() const
    {
    return gestures_exclude;
    }


int Settings::gestureTimeOut() const
    {
    return gesture_timeout;
    }


bool Settings::isDaemonDisabled() const
    {
    return daemon_disabled;
    }


void Settings::setActions( ActionDataGroup *actions )
    {
    delete m_actions;
    m_actions = actions;
    }


void Settings::setGesturesExclude( Windowdef_list *gestures )
    {
    delete gestures_exclude;
    gestures_exclude = gestures;
    }


void Settings::setGestureMouseButton( int mouse_button )
    {
    gesture_mouse_button = mouse_button;
    }


void Settings::setGestureTimeOut(int timeout)
    {
    gesture_timeout = timeout;
    }


void Settings::setVoiceShortcut( const KShortcut &shortcut )
    {
    voice_shortcut = shortcut;
    }


ActionDataGroup *Settings::takeActions()
    {
    ActionDataGroup *res = m_actions;
    m_actions = 0;
    return res;
    }


KShortcut Settings::voiceShortcut() const
    {
    return voice_shortcut;
    }


bool Settings::read_settings( bool include_disabled_P )
    {
    KConfig cfg( KHOTKEYS_CONFIG_FILE );
    return read_settings( cfg, include_disabled_P, ImportNone );
    }

bool Settings::import( KConfig& cfg_P, bool ask_P )
    {
    return read_settings( cfg_P, true, ask_P ? ImportAsk : ImportSilent );
    }


void Settings::initialize()
    {
    // Create the KMenuEdit group
    get_system_group(ActionDataGroup::SYSTEM_MENUENTRIES);
    }


ActionDataGroup *Settings::get_system_group(ActionDataGroup::system_group_t group_id)
    {
    Q_ASSERT(m_actions);

    // Search for the menuentries system group.
    ActionDataGroup *system_group = NULL;

    Q_FOREACH(KHotKeys::ActionDataBase* element, m_actions->children())
        {
        ActionDataGroup *group = dynamic_cast<ActionDataGroup*>(element);

        if (group && (group->system_group() == group_id))
            {
            system_group = group;
            break;
            }
        }

    // Check if we found the group
    if (system_group==NULL)
        {
        switch (group_id)
            {
            case ActionDataGroup::SYSTEM_MENUENTRIES:
                system_group = new ActionDataGroup(
                        m_actions,
                        "KMenuEdit",
                        "KMenuEdit Global Shortcuts",
                        NULL,
                        ActionDataGroup::SYSTEM_MENUENTRIES,
                        true);
                break;

            default:
                Q_ASSERT(false);
                return NULL;
            }
        }

    Q_ASSERT(system_group);
    return system_group;
    }


bool Settings::read_settings( KConfig& cfg_P, bool include_disabled_P, ImportType import_P )
    {
    // Reread settings. First delete what we have
    setActions(NULL);

    // Initialize m_actions
    m_actions = new ActionDataGroup(
            NULL,
            "should never see",
            "should never see",
            NULL,
            ActionDataGroup::SYSTEM_ROOT,
            true );

    // If the config group we should read from is empty, return.
    if( cfg_P.groupList().count() == 0 ) {
        return false;
    }

    // If we read the main settings and there is no main. Initialize the file
    // and return
    KConfigGroup mainGroup( &cfg_P, "Main" ); // main group
    if (import_P == ImportNone)
        {
        if (!cfg_P.groupList().contains("Main"))
            {
            initialize();
            return false;
            }

        // List of already imported configuration files
        already_imported = mainGroup.readEntry( "AlreadyImported",QStringList() );
        }
    else
        {
        QString import_id = mainGroup.readEntry( "ImportId" );
        if( !import_id.isEmpty())
            {
            if( already_imported.contains( import_id ))
                {
                if( import_P == ImportSilent
                    || KMessageBox::warningContinueCancel( NULL,
                        i18n( "This \"actions\" file has already been imported before. "
                              "Are you sure you want to import it again?" )) != KMessageBox::Continue )
                    return true; // import "successful"
                }
            else
                already_imported.append( import_id );
            }
        else
            {
            if( import_P != ImportSilent
                && KMessageBox::warningContinueCancel( NULL,
                    i18n( "This \"actions\" file has no ImportId field and therefore it cannot be determined "
                          "whether or not it has been imported already. Are you sure you want to import it?" ))
                    == KMessageBox::Cancel )
                return true;
            }
        }
    int version = mainGroup.readEntry( "Version", -1234576 );
    switch( version )
        {
        case 1:
            read_settings_v1( cfg_P );
          break;
        case 2:
            read_settings_v2( cfg_P, include_disabled_P );
          break;
        default:
            kWarning() << "Unknown cfg. file version\n";
          return false;
        case -1234576: // no config file
            if( import_P ) // if importing, this is an error
                return false;
          break;
        }
    if( import_P != ImportNone )
        return true; // don't read global settings
    daemon_disabled = mainGroup.readEntry( "Disabled", false);
    KConfigGroup gesturesConfig( &cfg_P, "Gestures" );
    gestures_disabled = gesturesConfig.readEntry( "Disabled", true);
    gesture_mouse_button = gesturesConfig.readEntry( "MouseButton", 2 );
    gesture_mouse_button = qBound( 2, gesture_mouse_button, 9 );
    gesture_timeout = gesturesConfig.readEntry( "Timeout", 300 );
    KConfigGroup gesturesExcludeConfig( &cfg_P, "GesturesExclude" );
    delete gestures_exclude;
    gestures_exclude = new Windowdef_list( gesturesExcludeConfig );
    KConfigGroup voiceConfig( &cfg_P, "Voice" );
    voice_shortcut=KShortcut( voiceConfig.readEntry("Shortcut" , "")  );

    // Ensure the system groups exist
    initialize();
    return true;
    }

void Settings::write_settings()
    {
    KConfig cfg( KHOTKEYS_CONFIG_FILE );

// CHECKME    smazat stare sekce ?
    QStringList groups = cfg.groupList();
    for( QStringList::ConstIterator it = groups.begin();
         it != groups.end();
         ++it )
        cfg.deleteGroup( *it );
    KConfigGroup mainGroup( &cfg, "Main" ); // main group
    mainGroup.writeEntry( "Version", 2 ); // now it's version 2 cfg. file
    mainGroup.writeEntry( "AlreadyImported", already_imported );
    KConfigGroup dataGroup( &cfg,  "Data" );
    int cnt = write_actions_recursively_v2( dataGroup, m_actions, true );
    mainGroup.writeEntry( "Autostart", cnt != 0 && !daemon_disabled );
    mainGroup.writeEntry( "Disabled", daemon_disabled );
    KConfigGroup gesturesConfig( &cfg, "Gestures" );
    gesturesConfig.writeEntry( "Disabled", gestures_disabled );
    gesturesConfig.writeEntry( "MouseButton", gesture_mouse_button );
    gesturesConfig.writeEntry( "Timeout", gesture_timeout );
    if( gestures_exclude != NULL )
        {
        KConfigGroup gesturesExcludeConfig( &cfg, "GesturesExclude" );
        gestures_exclude->cfg_write( gesturesExcludeConfig );
        }
    else
        cfg.deleteGroup( "GesturesExclude" );
    KConfigGroup voiceConfig( &cfg, "Voice" );
    voiceConfig.writeEntry("Shortcut" , voice_shortcut.toString() );

    }


// return value means the number of enabled actions written in the cfg file
// i.e. 'Autostart' for value > 0 should be on
int Settings::write_actions_recursively_v2( KConfigGroup& cfg_P, ActionDataGroup* parent_P, bool enabled_P )
    {
    int enabled_cnt = 0;
    QString save_cfg_group = cfg_P.name();
    int cnt = 0;
    if( parent_P )
        {
        Q_FOREACH(ActionDataBase *child,parent_P->children())
            {
            ++cnt;
            if( enabled_P && child->enabled( true ))
                ++enabled_cnt;
            KConfigGroup itConfig( cfg_P.config(), save_cfg_group + '_' + QString::number( cnt ));
            child->cfg_write( itConfig );
            ActionDataGroup* grp = dynamic_cast< ActionDataGroup* >(child);
            if( grp != NULL )
                enabled_cnt += write_actions_recursively_v2( itConfig, grp, enabled_P && child->enabled( true ));
            }
        }
    cfg_P.writeEntry( "DataCount", cnt );
    return enabled_cnt;
    }

void Settings::read_settings_v2( KConfig& cfg_P, bool include_disabled_P  )
    {
    KConfigGroup dataGroup( &cfg_P, "Data" );
    read_actions_recursively_v2( dataGroup, m_actions, include_disabled_P );
    }

void Settings::read_actions_recursively_v2( KConfigGroup& cfg_P, ActionDataGroup* parent_P,
    bool include_disabled_P )
    {
    QString save_cfg_group = cfg_P.name();
    int cnt = cfg_P.readEntry( "DataCount",0 );
    for( int i = 1;
         i <= cnt;
         ++i )
        {
        KConfigGroup itConfig( cfg_P.config(), save_cfg_group + '_' + QString::number( i ));
        if( include_disabled_P || ActionDataBase::cfg_is_enabled( itConfig ))
            {
            ActionDataBase* new_action = ActionDataBase::create_cfg_read( itConfig, parent_P );
            ActionDataGroup* grp = dynamic_cast< ActionDataGroup* >( new_action );
            if( grp != NULL )
                read_actions_recursively_v2( itConfig, grp, include_disabled_P );
            }
        }
    }

// backward compatibility
void Settings::read_settings_v1( KConfig& cfg_P )
    {
    KConfigGroup mainGroup( &cfg_P, "Main" );
    int sections = mainGroup.readEntry( "Num_Sections", 0 );
    ActionDataGroup* menuentries = NULL;
    Q_FOREACH(ActionDataBase *child, m_actions->children())
        {
        ActionDataGroup* tmp = dynamic_cast< ActionDataGroup* >(child);
        if( tmp == NULL )
            continue;
        if( tmp->system_group() == ActionDataGroup::SYSTEM_MENUENTRIES )
            {
            menuentries = tmp;
            break;
            }
        }
    for( int sect = 1;
         sect <= sections;
         ++sect )
        {
        QString group = QString( "Section%1" ).arg( sect );
        if( !cfg_P.hasGroup( group ))
            continue;
        KConfigGroup sectionConfig( &cfg_P, group );
        QString name = sectionConfig.readEntry( "Name" );
        if( name.isNull() )
            continue;
        QString shortcut = sectionConfig.readEntry( "Shortcut" );
        if( shortcut.isNull() )
            continue;
        QString run = sectionConfig.readEntry( "Run" );
        if( run.isNull() )
            continue;
        bool menuentry = sectionConfig.readEntry( "MenuEntry", false);
        // CHECKME tohle pridavani az pak je trosku HACK
        if( menuentry )
            {
            if( menuentries == NULL )
                {
                menuentries = new ActionDataGroup( m_actions,
                    i18n( MENU_EDITOR_ENTRIES_GROUP_NAME ),
                    i18n( "These entries were created using Menu Editor." ), NULL,
                    ActionDataGroup::SYSTEM_MENUENTRIES, true );
                menuentries->set_conditions( new Condition_list( "", menuentries ));
                }
            ( void ) new MenuEntryShortcutActionData( menuentries, name, "",
                KShortcut( shortcut ), run );
            }
        else
            {
            ( void ) new CommandUrlShortcutActionData( m_actions, name, "",
                KShortcut( shortcut ), run );
            }
        }
    }

} // namespace KHotKeys
