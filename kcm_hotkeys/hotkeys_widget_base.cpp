/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "hotkeys_widget_base.h"

#include "action_data/action_data_group.h"

#include <QDebug>

HotkeysWidgetBase::HotkeysWidgetBase(QWidget *parent)
    : HotkeysWidgetIFace(parent)
{
    ui.setupUi(this);

    connect(ui.comment, SIGNAL(textChanged()), _changedSignals, SLOT(map()));
    _changedSignals->setMapping(ui.comment, "comment");
}

HotkeysWidgetBase::~HotkeysWidgetBase()
{
}

void HotkeysWidgetBase::apply()
{
    HotkeysWidgetIFace::apply();
    emit changed(_data);
}

void HotkeysWidgetBase::extend(QWidget *w, const QString &label)
{
    ui.tabs->addTab(w, label);
}

bool HotkeysWidgetBase::isChanged() const
{
    return _data->comment() != ui.comment->toPlainText();
}

void HotkeysWidgetBase::doCopyFromObject()
{
    ui.comment->setText(_data->comment());
}

void HotkeysWidgetBase::doCopyToObject()
{
    _data->set_comment(ui.comment->toPlainText());
}

#include "moc_hotkeys_widget_base.cpp"
