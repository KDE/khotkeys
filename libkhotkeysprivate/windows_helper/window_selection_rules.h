#ifndef WINDOW_SELECTION_RULES_H
#define WINDOW_SELECTION_RULES_H
/* SPDX-FileCopyrightText: 1999-2001 Lubos Lunak <l.lunak@kde.org>
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: GPL-2.0-only
*/

#include "windows_helper/window_selection_interface.h"


namespace KHotKeys {

/**
 * Rules to match a windows.
 */
class Q_DECL_EXPORT Windowdef_simple : public Windowdef
    {

    typedef Windowdef base;

    public:

        /**
         * How to compare.
         */
        enum substr_type_t
            {
            NOT_IMPORTANT,
            CONTAINS,
            IS,
            REGEXP,
            CONTAINS_NOT,
            IS_NOT,
            REGEXP_NOT,
            };

        /**
         * Window Type
         */
        enum window_type_t
            {
            WINDOW_TYPE_NORMAL     = ( 1 << NET::Normal ),
            WINDOW_TYPE_DESKTOP    = ( 1 << NET::Desktop ),
            WINDOW_TYPE_DOCK       = ( 1 << NET::Dock ),
            WINDOW_TYPE_DIALOG     = ( 1 << NET::Dialog ),
            };

        /**
         * Constructor
         */
        Windowdef_simple(
                const QString& comment_P = QString(),
                const QString& title_P = QString(),
                substr_type_t _title_type_P = NOT_IMPORTANT,
                const QString& wclass_P = QString(),
                substr_type_t wclass_type_P = NOT_IMPORTANT,
                const QString& role_P = QString(),
                substr_type_t role_type_P = NOT_IMPORTANT,
                int window_types_P = 0 );

        /**
         * Create from a configuration file.
         */
        Windowdef_simple( KConfigGroup& cfg_P );

        /**
         * Match against window @p window_P
         */
        bool match( const Window_data& window_P ) Q_DECL_OVERRIDE;

        /**
         * Write to configuration file @p cfg_P
         */
        void cfg_write( KConfigGroup& cfg_P ) const Q_DECL_OVERRIDE;

        /**
         * The string to compare with the window title
         */
        const QString& title() const;
        void set_title(const QString &title);

        /**
         * How to match the window title
         */
        substr_type_t title_match_type() const;
        void set_title_match_type(const substr_type_t &type);

        /**
         * The string to compare with the window class
         */
        const QString& wclass() const;
        void set_wclass(const QString &wclass);

        /**
         * How to match the window class
         */
        substr_type_t wclass_match_type() const;
        void set_wclass_match_type(const substr_type_t &);

        /**
         * The string to compare with the window role
         */
        const QString& role() const;
        void set_role(const QString &role);

        /**
         * How to match the window type
         */
        substr_type_t role_match_type() const;
        void set_role_match_type(const substr_type_t &type);

        /**
         * The window types to match
         */
        int window_types() const;
        void set_window_types(const int types);

        /**
         *
         */
        bool type_match( window_type_t type_P ) const;

        /**
         */
        bool type_match( NET::WindowType type_P ) const;

        /**
         * Create a copy
         */
        Windowdef_simple* copy( /*ActionDataBase* data_P*/ ) const Q_DECL_OVERRIDE;

        /**
         * The description of this rule.
         *
         * @todo: Move to base class?
         */
        const QString description() const Q_DECL_OVERRIDE;

    protected:

        /**
         */
        bool is_substr_match(
                const QString& str1_P,
                const QString& str2_P,
                substr_type_t type_P );

    private:

        //! The title string
        QString _title;

        //! How to use the title string
        substr_type_t _title_match_type;

        //! The class string
        QString _wclass;

        //! How to use the class string
        substr_type_t _wclass_match_type;

        //! The role string
        QString _role;

        //! How to use the role string
        substr_type_t _role_match_type;

        //! Which window types to match
        int _window_types;
    };


} // namespace KHotKeys


#endif /* #ifndef WINDOW_SELECTION_RULES_H */
