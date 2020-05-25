#ifndef WINDOW_DEFINITION_H
#define WINDOW_DEFINITION_H
/* Copyright (C) 2008 Michael Jansen <kde@michael-jansen.biz>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "hotkeys_widget_iface.h"

#include "qwindowdefs.h"
#include <QWidget>
#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>


namespace Ui {
    class WindowDefinitionWidget;
}

namespace KHotKeys {
    class Windowdef_simple;
}


/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class WindowDefinitionWidget : public HotkeysWidgetIFace
    {
    Q_OBJECT

public:

    /**
     * Default constructor
     */
    WindowDefinitionWidget(KHotKeys::Windowdef_simple *windowdef, QWidget *parent = nullptr);

    /**
     * Destructor
     */
    virtual ~WindowDefinitionWidget();

    bool isChanged() const Q_DECL_OVERRIDE;

protected:

    void doCopyFromObject() Q_DECL_OVERRIDE;
    void doCopyToObject() Q_DECL_OVERRIDE;

private Q_SLOTS:

    void slotWindowClassChanged(int);
    void slotWindowRoleChanged(int);
    void slotWindowTitleChanged(int);

    void slotAutoDetect();
    void slotWindowSelected(WId);

private:

    Ui::WindowDefinitionWidget *ui;

    KHotKeys::Windowdef_simple *_windowdef;
};


class WindowDefinitionDialog : public QDialog
    {
    Q_OBJECT

public:

    WindowDefinitionDialog( KHotKeys::Windowdef_simple *windowdef, QWidget *parent=nullptr)
        :   QDialog(parent)
            ,def(nullptr)
        {
        setLayout(new QVBoxLayout);

        def = new WindowDefinitionWidget(windowdef, this);
        def->copyFromObject();

        layout()->addWidget(def);

        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                | QDialogButtonBox::Cancel);

        layout()->addWidget(buttonBox);


        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
        }


    ~WindowDefinitionDialog()
        {
        def = nullptr;
        }


    void accept() Q_DECL_OVERRIDE
        {
        def->copyToObject();
        QDialog::accept();
        }

private:

    WindowDefinitionWidget *def;
    };


#endif /* #ifndef WINDOW_DEFINITION_H */
