/****************************************************************************

 KHotKeys
 
 Copyright (C) 1999-2001 Lubos Lunak <l.lunak@kde.org>

 Distributed under the terms of the GNU General Public License version 2.
 
****************************************************************************/

#ifndef _CONDITIONS_LIST_WIDGET_H_
#define _CONDITIONS_LIST_WIDGET_H_

#include <qlistview.h>
#include <qptrlist.h>

#include <kdialogbase.h>

#include <conditions.h>
#include <condition_list_widget_ui.h>

namespace KHotKeys
{

class Action_data;
class Windowdef_list_widget;

class Condition_list_item;

class Condition_list_widget
    : public Condition_list_widget_ui
    {
    Q_OBJECT
    public:
        Condition_list_widget( QWidget* parent_P = NULL, const char* name_P = NULL );
        virtual ~Condition_list_widget();
        void set_data( const Condition_list* data_P );
        Condition_list* get_data( Action_data_base* data_P ) const;
    public slots:
        void clear_data();
    protected:
        Condition_list_item* create_listview_item( Condition* condition_P, QListView* parent1_P,
            Condition_list_item* parent2_P, QListViewItem* after_P, bool copy_P );
        void edit_listview_item( Condition_list_item* item_P );
        enum type_t { TYPE_ACTIVE_WINDOW, TYPE_EXISTING_WINDOW, TYPE_NOT, TYPE_AND, TYPE_OR };
    protected slots:
        void new_selected( int type_P );
        virtual void copy_pressed();
        virtual void delete_pressed();
        virtual void modify_pressed();
        virtual void current_changed( QListViewItem* item_P );
    private:
        void insert_listview_items( const Condition_list_base* parent_P,
            QListView* parent1_P, Condition_list_item* parent2_P );
        void get_listview_items( Condition_list_base* list_P, QListViewItem* first_item_P ) const;
        Condition_list_item* selected_item;
        QPtrList< Condition > conditions;
    };

typedef Condition_list_widget Condition_list_tab;

class Condition_list_item
    : public QListViewItem
    {
    public:
        Condition_list_item( QListView* parent_P, Condition* condition_P );
        Condition_list_item( QListViewItem* parent_P, Condition* condition_P );
        Condition_list_item( QListView* parent_P, QListViewItem* after_P, Condition* condition_P );
        Condition_list_item( QListViewItem* parent_P, QListViewItem* after_P,
            Condition* condition_P );
        virtual QString text( int column_P ) const;
        Condition* condition() const;
        void set_condition( Condition* condition_P );
    protected:
        Condition* _condition; // owns it
    };
        
class Condition_dialog
    {
    public:
        virtual Condition* edit_condition() = 0;
        virtual ~Condition_dialog();
    };
    
class Active_window_condition_dialog
    : public KDialogBase, public Condition_dialog
    {
    Q_OBJECT
    public:
        Active_window_condition_dialog( Active_window_condition* condition_P );
        virtual Condition* edit_condition();
    protected:
        virtual void accept();
        Windowdef_list_widget* widget;
        Active_window_condition* condition;
    };
        
class Existing_window_condition_dialog
    : public KDialogBase, public Condition_dialog
    {
    Q_OBJECT
    public:
        Existing_window_condition_dialog( Existing_window_condition* condition_P );
        virtual Condition* edit_condition();
    protected:
        virtual void accept();
        Windowdef_list_widget* widget;
        Existing_window_condition* condition;
    };
        

//***************************************************************************
// Inline
//***************************************************************************

// Condition_list_item

inline
Condition_list_item::Condition_list_item( QListView* parent_P, Condition* condition_P )
    : QListViewItem( parent_P ), _condition( condition_P )
    {
    }
    
inline
Condition_list_item::Condition_list_item( QListViewItem* parent_P, Condition* condition_P )
    : QListViewItem( parent_P ), _condition( condition_P )
    {
    }

inline
Condition_list_item::Condition_list_item( QListView* parent_P, QListViewItem* after_P,
    Condition* condition_P )
    : QListViewItem( parent_P, after_P ), _condition( condition_P )
    {
    }

inline
Condition_list_item::Condition_list_item( QListViewItem* parent_P, QListViewItem* after_P,
    Condition* condition_P )
    : QListViewItem( parent_P, after_P ), _condition( condition_P )
    {
    }

inline
Condition* Condition_list_item::condition() const
    {
    return _condition;
    }
    
inline
void Condition_list_item::set_condition( Condition* condition_P )
    {
    _condition = condition_P;
    }

// Condition_dialog

inline
Condition_dialog::~Condition_dialog()
    {
    }

} // namespace KHotKeys

#endif
