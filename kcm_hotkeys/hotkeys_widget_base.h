/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef HOTKEYS_WIDGET_BASE_H
#define HOTKEYS_WIDGET_BASE_H

#include "ui_hotkeys_widget_base.h"

#include "hotkeys_widget_iface.h"
#include "libkhotkeysfwd.h"

class HotkeysWidgetBasePrivate;

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class HotkeysWidgetBase : public HotkeysWidgetIFace
{
    Q_OBJECT

public:
    /**
     * Default constructor
     */
    HotkeysWidgetBase(QWidget *parent = nullptr);

    /**
     * Destructor
     */
    ~HotkeysWidgetBase() override;

    void apply() override;

    /**
     * The associated action.
     */
    KHotKeys::ActionDataBase *data()
    {
        return _data;
    }

    const KHotKeys::ActionDataBase *data() const
    {
        return _data;
    }

    bool isChanged() const override;

    using HotkeysWidgetIFace::changed;

Q_SIGNALS:

    void changed(KHotKeys::ActionDataBase *);

protected:
#if 0
    /**
     * Append the QLayoutItems from QGridLayout \from to QGridLayout \to.
     */
    void mergeLayouts( QGridLayout *to, QGridLayout *from );
#endif

protected:
    void extend(QWidget *, const QString &);

    void doCopyFromObject() override;
    void doCopyToObject() override;

    Ui::HotkeysWidgetBase ui;

    KHotKeys::ActionDataBase *_data;
};

#endif /* #ifndef HOTKEYS_WIDGET_BASE_H */
