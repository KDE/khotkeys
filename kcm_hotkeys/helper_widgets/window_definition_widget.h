#ifndef WINDOW_DEFINITION_H
#define WINDOW_DEFINITION_H
/* SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
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
