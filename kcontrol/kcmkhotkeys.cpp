/****************************************************************************

 KHotKeys
 
 Copyright (C) 1999-2001 Lubos Lunak <l.lunak@kde.org>

 Distributed under the terms of the GNU General Public License version 2.
 
****************************************************************************/

#define _KCMKHOTKEYS_CPP_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "kcmkhotkeys.h"

#include <unistd.h>

#include <qlayout.h>
#include <qsplitter.h>

#include <kcmodule.h>
#include <klocale.h>
#include <kapp.h>
#include <kconfig.h>
#include <kapp.h>
#include <dcopclient.h>
#include <kdebug.h>
#include <kmessagebox.h>
#include <kglobal.h>
#include <ksimpleconfig.h>
#include <kfiledialog.h>
#include <dcopref.h>

#include <input.h>
#include <triggers.h>
#include <action_data.h>

#include "tab_widget.h"
#include "actions_listview_widget.h"
#include "main_buttons_widget.h"

extern "C"
{
KCModule* create_khotkeys( QWidget* parent_P, const char* name_P )
    {
//    sleep( 20 ); // CHECKME DEBUG
    KGlobal::locale()->insertCatalogue("khotkeys");
    KHotKeys::Module* ret = new KHotKeys::Module( parent_P, name_P );
    ret->load(); // CHECKME
    return ret;
    }

void init_khotkeys()
    {
    KConfig cfg( "khotkeysrc", true );
    cfg.setGroup( "Main" );
    if( !cfg.readBoolEntry( "Autostart", false ))
        return;
    cfg.setGroup("X11"); // from kdeglobals actually
    // Non-xinerama multhead support in KDE is just a hack
    // involving forking apps per-screen. Don't bother with
    // kded modules in such case.
    if( cfg.readBoolEntry( "enableMultihead" ))
        kapp->kdeinitExec( "khotkeys" );
    else
        {
        DCOPRef ref( "kded", "kded" );
        if( !ref.call( "loadModule", QCString( "khotkeys" )))
            {
            kdWarning( 1217 ) << "Loading of khotkeys module failed." << endl;
            kapp->kdeinitExec( "khotkeys" );
            }
        }
    }
}

namespace KHotKeys
{

Module::Module( QWidget* parent_P, const char* )
    : KCModule( parent_P, "khotkeys" ), _actions_root( NULL ), _current_action_data( NULL ),
        listview_is_changed( false ), deleting_action( false )
    {
    setButtons( Help | Cancel | Apply | Ok );
    module = this;
    init_global_data( false, this ); // don't grab keys
    QVBoxLayout* vbox = new QVBoxLayout( this ); 
    vbox->setSpacing( 6 );
    vbox->setMargin( 11 );
    QSplitter* splt = new QSplitter( this );
    actions_listview_widget = new Actions_listview_widget( splt );
    tab_widget = new Tab_widget( splt );
    vbox->addWidget( splt );
    buttons_widget = new Main_buttons_widget( this );
    vbox->addWidget( buttons_widget );
    connect( actions_listview_widget, SIGNAL( current_action_changed()),
        SLOT( listview_current_action_changed()));
    connect( buttons_widget, SIGNAL( new_action_pressed()),  SLOT( new_action()));
    connect( buttons_widget, SIGNAL( new_action_group_pressed()),  SLOT( new_action_group()));
    connect( buttons_widget, SIGNAL( delete_action_pressed()),  SLOT( delete_action()));
    connect( buttons_widget, SIGNAL( global_settings_pressed()), SLOT( global_settings()));
//    listview_current_action_changed(); // init
    }
    
Module::~Module()
    {
    _current_action_data = NULL;
    tab_widget->load_current_action(); // clear tab_widget
    delete _actions_root;
    module = NULL;
    }
    
void Module::load()
    {
    actions_listview_widget->clear();
    delete _actions_root;
    settings.actions = NULL;
    _current_action_data = NULL;
    settings.read_settings( true );
    _actions_root = settings.actions;
    kdDebug( 1217 ) << "actions_root:" << _actions_root << endl;
    actions_listview_widget->build_up();
    tab_widget->load_current_action();
    emit KCModule::changed( false ); // HACK otherwise the module would be changed from the very beginning
    }

void Module::save()
    {
    tab_widget->save_current_action_changes();
    settings.actions = _actions_root;
    settings.write_settings();
    if( daemon_disabled())
        {
        QByteArray data;
        kapp->dcopClient()->send( "khotkeys*", "khotkeys", "quit()", data );
        kdDebug( 1217 ) << "disabling khotkeys daemon" << endl;
        }
    else
        {
        if( !kapp->dcopClient()->isApplicationRegistered( "khotkeys" ))
            {
            kdDebug( 1217 ) << "launching new khotkeys daemon" << endl;
            KApplication::kdeinitExec( "khotkeys" );
            }
        else
            {
            QByteArray data;
            kapp->dcopClient()->send( "khotkeys*", "khotkeys", "reread_configuration()", data );
            kdDebug( 1217 ) << "telling khotkeys daemon to reread configuration" << endl;
            }
        }
    emit KCModule::changed( false );
    }


QString Module::quickHelp() const
    {
    return i18n( "" ); // TODO CHECKME
    }

void Module::action_name_changed( const QString& name_P )
    {
    current_action_data()->set_name( name_P );
    actions_listview_widget->action_name_changed( name_P );
    }
    
void Module::listview_current_action_changed()
    {
    // CHECKME tohle je trosku hack, aby se pri save zmenenych hodnot ve stare vybrane polozce
    // zmenila data v te stare polozce a ne nove aktivni
    listview_is_changed = true;
    set_new_current_action( !deleting_action );
    listview_is_changed = false;
    }

void Module::set_new_current_action( bool save_old_P )
    {
    if( save_old_P )
        tab_widget->save_current_action_changes();
    _current_action_data = actions_listview_widget->current_action_data();
    kdDebug( 1217 ) << "set_new_current_action : " << _current_action_data << endl;
    tab_widget->load_current_action();
    buttons_widget->enable_delete( current_action_data() != NULL );
    }

// CHECKME volano jen z Tab_widget pro nastaveni zmenenych dat ( novy Action_data_base )
void Module::set_current_action_data( Action_data_base* data_P )
    {
    delete _current_action_data;
    _current_action_data = data_P;
    actions_listview_widget->set_action_data( data_P, listview_is_changed );
//    tab_widget->load_current_action(); CHECKME asi neni treba
    }
    
#if 0

}
#include <iostream>
#include <iomanip>
namespace KHotKeys {

void check_tree( Action_data_group* b, int lev_P = 0 )
    {
    using namespace std;
    cerr << setw( lev_P ) << "" << b << ":Group:" << b->name().latin1() << ":" << b->parent() << endl;
    for( Action_data_group::Iterator it = b->first_child();
         it;
         ++it )
        if( Action_data_group* g = dynamic_cast< Action_data_group* >( *it ))
            check_tree( g, lev_P + 1 );
        else
            cerr << setw( lev_P + 1 ) << "" << (*it) << ":Action:" << (*it)->name().latin1() << ":" << (*it)->parent() << endl;
    }

#endif
    
void Module::new_action()
    {
    tab_widget->save_current_action_changes();
//    check_tree( actions_root());
    Action_data_group* parent = current_action_data() != NULL
        ? dynamic_cast< Action_data_group* >( current_action_data()) : NULL;
    if( parent == NULL )
        {
        if( current_action_data() != NULL )
            parent = current_action_data()->parent();
        else
            parent = module->actions_root();
        }
    Action_data_base* item = new Generic_action_data( parent, i18n( "New Action" ), "",
        new Trigger_list( "" ), new Condition_list( "", NULL ), new Action_list( "" ), true );
    actions_listview_widget->new_action( item );
//    check_tree( actions_root());
    set_new_current_action( false );
    }

// CHECKME spojit tyhle dve do jedne    
void Module::new_action_group()
    {
    tab_widget->save_current_action_changes();
//    check_tree( actions_root());
    Action_data_group* parent = current_action_data() != NULL
        ? dynamic_cast< Action_data_group* >( current_action_data()) : NULL;
    if( parent == NULL )
        {
        if( current_action_data() != NULL )
            parent = current_action_data()->parent();
        else
            parent = module->actions_root();
        }
    Action_data_base* item = new Action_data_group( parent, i18n( "New Action Group" ), "",
        new Condition_list( "", NULL ), Action_data_group::SYSTEM_NONE, true );
    actions_listview_widget->new_action( item );
//    check_tree( actions_root());
    set_new_current_action( false );
    }

void Module::delete_action()
    {
    delete _current_action_data;
    _current_action_data = NULL;
    deleting_action = true; // CHECKME zase tak trosku hack, jinak by se snazilo provest save
    actions_listview_widget->delete_action(); // prave mazane polozky
    deleting_action = false;
    set_new_current_action( false );
    }

void Module::global_settings()
    {
    actions_listview_widget->set_current_action( NULL );
    set_new_current_action( true );
    }

void Module::set_gestures_exclude( Windowdef_list* windows )
    {
    delete settings.gestures_exclude;
    settings.gestures_exclude = windows;
    }

void Module::import()
    {
    QString file = KFileDialog::getOpenFileName( QString::null, "*.khotkeys", topLevelWidget(),
        i18n( "Select File with Actions to Be Imported" ));
    if( file.isEmpty())
        return;
    KSimpleConfig cfg( file, true );
    if( !settings.import( cfg, true ))
        {
        KMessageBox::error( topLevelWidget(),
            i18n( "Import of the specified file failed. Most probably the file is not a valid "
                "file with actions." ));
        return;
        }
    actions_listview_widget->clear();
    actions_listview_widget->build_up();
    tab_widget->load_current_action();
    emit KCModule::changed( true );
    }
    
void Module::changed()
    {
    emit KCModule::changed( true );
    }

Module* module; // CHECKME

} // namespace KHotKeys

#include "kcmkhotkeys.moc"
