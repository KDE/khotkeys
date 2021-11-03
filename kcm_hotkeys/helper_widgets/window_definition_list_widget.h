#ifndef WINDOW_DEFINITION_LIST_WIDGET_H
#define WINDOW_DEFINITION_LIST_WIDGET_H
/* SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "hotkeys_widget_iface.h"

#include "ui_window_definition_list_widget.h"
#include "windows_helper/window_selection_list.h"
#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class WindowDefinitionListWidget : public HotkeysWidgetIFace
{
    Q_OBJECT

public:
    /**
     * Default constructor
     */
    WindowDefinitionListWidget(KHotKeys::Windowdef_list *windowdef_list, QWidget *parent = nullptr);

    WindowDefinitionListWidget(QWidget *parent);

    /**
     * Destructor
     */
    ~WindowDefinitionListWidget() override;

    void setWindowDefinitions(KHotKeys::Windowdef_list *windowdef_list);

    bool isChanged() const override;

private:
    void emitChanged(bool);

private Q_SLOTS:

    void slotDelete(bool);
    void slotDuplicate(bool);
    void slotEdit(bool);
    void slotNew(bool);

protected:
    void doCopyFromObject() override;
    void doCopyToObject() override;

private:
    // The Windowdefinition list
    KHotKeys::Windowdef_list *_windowdefs;
    KHotKeys::Windowdef_list *_working;

    // The User Interface
    Ui::WindowDefinitionListWidget ui;

    // Unsaved changes?
    bool _changed;
};

class WindowDefinitionListDialog : public QDialog
{
    Q_OBJECT

public:
    WindowDefinitionListDialog(KHotKeys::Windowdef_list *list, QWidget *parent = nullptr)
        : QDialog(parent)
        , def(nullptr)
    {
        setLayout(new QVBoxLayout);

        def = new WindowDefinitionListWidget(list, this);
        def->copyFromObject();

        layout()->addWidget(def);

        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

        layout()->addWidget(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    }

    ~WindowDefinitionListDialog() override
    {
        def = nullptr;
    }

    void accept() override
    {
        def->copyToObject();
        QDialog::accept();
    }

private:
    WindowDefinitionListWidget *def;
};

#endif /* #ifndef WINDOW_DEFINITION_LIST_WIDGET_H */
