/**
 * SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "hotkeys_export_widget.h"

#include <QDialogButtonBox>

KHotkeysExportWidget::KHotkeysExportWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

KHotkeysExportWidget::~KHotkeysExportWidget()
{
}

KHotkeysExportDialog::KHotkeysExportDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18n("Export Group"));
    setLayout(new QVBoxLayout);

    w = new KHotkeysExportWidget(this);
    layout()->addWidget(w);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    layout()->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

KHotkeysExportDialog::~KHotkeysExportDialog()
{
}

bool KHotkeysExportDialog::allowMerging() const
{
    return w->ui.allowMerging->isChecked();
}

QString KHotkeysExportDialog::importId() const
{
    return w->ui.id->text();
}

void KHotkeysExportDialog::setAllowMerging(bool allow)
{
    w->ui.allowMerging->setChecked(allow);
}

void KHotkeysExportDialog::setImportId(const QString &id)
{
    w->ui.id->setText(id);
}

int KHotkeysExportDialog::state() const
{
    return w->ui.state->currentIndex();
}

QUrl KHotkeysExportDialog::url() const
{
    return w->ui.filename->url();
}

#include "moc_hotkeys_export_widget.cpp"
