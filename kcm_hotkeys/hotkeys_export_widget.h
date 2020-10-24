#ifndef HOTKEYS_EXPORT_WIDGET_H
#define HOTKEYS_EXPORT_WIDGET_H
/**
 * SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "ui_hotkeys_export_widget.h"

#include <QDialog>
#include <QUrl>

#include <QWidget>


/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class KHotkeysExportWidget : public QWidget
    {
    Q_OBJECT

public:

    KHotkeysExportWidget(QWidget *parent);
    virtual ~KHotkeysExportWidget();

    // The layout
    Ui::KHotkeysExportWidget ui;

    }; // KHotkeysExportWidget

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class KHotkeysExportDialog : public QDialog
    {
public:
    KHotkeysExportDialog(QWidget*);
    virtual ~KHotkeysExportDialog();

    QString importId() const;

    bool allowMerging() const;
    void setAllowMerging(bool);
    void setImportId(const QString &id);
    int state() const;
    QUrl url() const;

private:

    KHotkeysExportWidget *w;
    }; // KHotkeysExportDialog


#endif /* HOTKEYS_EXPORT_WIDGET_H */
