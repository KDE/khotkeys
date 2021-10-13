/*
   SPDX-FileCopyrightText: 2008 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kcm_hotkeys.h"
#include "hotkeys_context_menu.h"
#include "ui_kcm_hotkeys.h"

#include <typeinfo>

// ACTION_DATAS
#include "action_data/action_data_group.h"
// OUR ACTION WIDGETS
#include "action_group_widget.h"
#include "global_settings_widget.h"
#include "simple_action_data_widget.h"
// REST
#include "daemon/daemon.h"
#include "hotkeys_model.h"
#include "hotkeys_proxy_model.h"
#include "hotkeys_tree_view.h"
#include "khotkeys_interface.h"
#include "khotkeysglobal.h"

#include <QDBusConnection>
#include <QDBusError>

#include <KAboutData>
#include <KMessageBox>
#include <QDebug>

K_PLUGIN_FACTORY(KCMHotkeysFactory, registerPlugin<KCMHotkeys>();)

class KCMHotkeysPrivate : public Ui::KCMHotkeysWidget
{
public:
    KCMHotkeysPrivate(KCMHotkeys *host);

    /** The model holding the shortcut settings. Beware! There is a proxy
     * model between us and that model */
    KHotkeysModel *model;

    //! Our host
    KCMHotkeys *q;

    //! The currently shown dialog
    HotkeysWidgetIFace *current;

    //! The currently shown item
    QModelIndex currentIndex;

    /**
     * Show the widget. If the current widget has changes allow
     * cancelation ! of this action
     */
    bool maybeShowWidget(const QModelIndex &next);

    /**
     * Applies the changes from the current item
     */
    void applyCurrentItem();

    void load();
    void save();
};

KCMHotkeys::KCMHotkeys(QWidget *parent, const QVariantList & /* args */)
    : KCModule(parent)
    , d(new KCMHotkeysPrivate(this))
{
    // Inform KCModule of the buttons we support
    KCModule::setButtons(KCModule::Buttons(KCModule::Default | KCModule::Apply | KCModule::Help));

    // Add the about data
    KAboutData *about = new KAboutData("khotkeys",
                                       i18n("KDE Hotkeys Configuration Module"),
                                       PROJECT_VERSION,
                                       QString(),
                                       KAboutLicense::GPL,
                                       i18n("Copyright 2008 (c) Michael Jansen"));
    about->addAuthor(i18n("Michael Jansen"), i18n("Maintainer"), "kde@michael-jansen.biz");
    setAboutData(about);

    // Tell KCModule we were changed.
    connect(d->action_group, SIGNAL(changed(bool)), this, SIGNAL(changed(bool)));
    connect(d->simple_action, SIGNAL(changed(bool)), this, SIGNAL(changed(bool)));
    connect(d->global_settings, SIGNAL(changed(bool)), this, SIGNAL(changed(bool)));
    // Update TreeView if hotkeys was changed
    auto emitModelChange = [this](KHotKeys::ActionDataBase *hotkey) {
        d->model->emitChanged(hotkey);
    };
    connect(d->simple_action, static_cast<void (HotkeysWidgetBase::*)(KHotKeys::ActionDataBase *)>(&HotkeysWidgetBase::changed), emitModelChange);
    connect(d->action_group, static_cast<void (HotkeysWidgetBase::*)(KHotKeys::ActionDataBase *)>(&HotkeysWidgetBase::changed), emitModelChange);

    // Show the context menu
    d->menu_button->setMenu(new HotkeysTreeViewContextMenu(d->tree_view));

    // Switch to the global settings dialog
    connect(d->settings_button, SIGNAL(clicked(bool)), SLOT(showGlobalSettings()));
}

void KCMHotkeys::currentChanged(const QModelIndex &pCurrent, const QModelIndex &pPrevious)
{
    // We're not interested in changes of columns. Just compare the rows
    QModelIndex current = pCurrent.isValid() ? pCurrent.sibling(pCurrent.row(), 0) : QModelIndex();
    QModelIndex previous = pPrevious.isValid() ? pPrevious.sibling(pPrevious.row(), 0) : QModelIndex();

    // Now it's possible for previous and current to be the same
    if (current == previous || current == d->currentIndex) {
        return;
    }

    // Current and previous differ. Ask user if there are unsaved changes
    if (!d->maybeShowWidget(current)) {
        // Bring focus back to the current item
        d->tree_view->selectionModel()->setCurrentIndex(d->currentIndex, QItemSelectionModel::SelectCurrent);
        return;
    }

    if (!current.isValid()) {
        if (previous.isValid()) { // throw away old widget and stuff lest we have dangling pointers https://bugs.kde.org/show_bug.cgi?id=443656
            d->simple_action->unsetActionData();
        }
        return showGlobalSettings();
    }

    // Now go on and activate the new item;
    KHotKeys::ActionDataBase *item = d->model->indexToActionDataBase(current);
    QModelIndex typeOfIndex = d->model->index(current.row(), KHotkeysModel::TypeColumn, current.parent());

    switch (d->model->data(typeOfIndex).toInt()) {
    case KHotkeysModel::SimpleActionData: {
        KHotKeys::SimpleActionData *data = dynamic_cast<KHotKeys::SimpleActionData *>(item);
        if (data) {
            d->simple_action->setActionData(data);
            d->current = d->simple_action;
        }
    } break;

    case KHotkeysModel::ActionDataGroup: {
        KHotKeys::ActionDataGroup *group = dynamic_cast<KHotKeys::ActionDataGroup *>(item);
        if (group) {
            d->action_group->setActionData(group);
            d->current = d->action_group;
        }
    } break;

    default: {
        const std::type_info &ti = typeid(*item);
        qDebug() << "##### Unknown ActionDataType " << ti.name();
    }

    } // switch

    d->currentIndex = current;
    d->stack->setCurrentWidget(d->current);
}

KCMHotkeys::~KCMHotkeys()
{
    delete d;
    d = nullptr;
}

void KCMHotkeys::defaults()
{
    qWarning() << "not yet implemented!";
}

void KCMHotkeys::load()
{
    showGlobalSettings();
    d->load();
}

void KCMHotkeys::showGlobalSettings()
{
    d->current = d->global_settings;
    d->currentIndex = QModelIndex();

    d->tree_view->setCurrentIndex(d->currentIndex);
    d->global_settings->copyFromObject();
    d->stack->setCurrentWidget(d->global_settings);
}

void KCMHotkeys::slotChanged()
{
    emit changed(true);
}

void KCMHotkeys::slotReset()
{
    showGlobalSettings();
}

void KCMHotkeys::save()
{
    d->save();
    emit changed(false);
}

// ==========================================================================
// KCMHotkeysPrivate

KCMHotkeysPrivate::KCMHotkeysPrivate(KCMHotkeys *host)
    : Ui::KCMHotkeysWidget()
    , model(nullptr)
    , q(host)
    , current(nullptr)
{
    setupUi(q);

    // Initialize the global part of the khotkeys lib ( handler ... )
    KHotKeys::init_global_data(false, q);
}

void KCMHotkeysPrivate::load()
{
    // Start khotkeys
    KHotKeys::Daemon::start();

    // disconnect the signals
    if (tree_view->selectionModel()) {
        // clang-format off
        QObject::disconnect(tree_view->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), q, SLOT(currentChanged(QModelIndex,QModelIndex)));
        // clang-format on
    }

    // Create a new model;
    tree_view->setModel(new KHotkeysModel);
    // Delete the old
    delete model;
    // Now use the old
    model = tree_view->model();

    model->load();
    global_settings->setModel(model);

    // clang-format off
    QObject::connect(model, SIGNAL(rowsRemoved(QModelIndex,int,int)), q, SLOT(slotChanged()));
    QObject::connect(model, SIGNAL(rowsInserted(QModelIndex,int,int)), q, SLOT(slotChanged()));
    QObject::connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), q, SLOT(slotChanged()));
    QObject::connect(model, SIGNAL(modelAboutToBeReset()), q, SLOT(slotReset()));

    // reconnect the signals
    QObject::connect(tree_view->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), q, SLOT(currentChanged(QModelIndex,QModelIndex)));
    // clang-format on
}

bool KCMHotkeysPrivate::maybeShowWidget(const QModelIndex &nextIndex)
{
    qDebug();

    // If the current widget is changed, ask user if switch is ok
    if (current && (currentIndex != nextIndex) && current->isChanged()) {
        const int choice = KMessageBox::warningYesNoCancel(q,
                                                           i18n("The current action has unsaved changes.\n"
                                                                "Do you want to apply the changes or discard them?"),
                                                           i18n("Save changes"),
                                                           KStandardGuiItem::apply(),
                                                           KStandardGuiItem::discard(),
                                                           KStandardGuiItem::cancel());

        switch (choice) {
        case KMessageBox::Yes:
            applyCurrentItem();
            save();
            return true;
        case KMessageBox::No:
            return true;
        case KMessageBox::Cancel:
            return false;
        default:
            Q_UNREACHABLE();
            return false;
        }
    }
    return true;
}

void KCMHotkeysPrivate::save()
{
    if (!KHotKeys::Daemon::isRunning()) {
        // the daemon is not running (yet), we can just write the config and
        // try to start it
        if (current)
            applyCurrentItem();
        // Write the settings
        model->save();

        if (KHotKeys::Daemon::start()) {
            // On startup the demon does the updating stuff, therefore reload
            // the actions.
            model->load();
        } else {
            KMessageBox::error(q, "<qt>" + i18n("Unable to contact khotkeys. Your changes are saved, but they could not be activated.") + "</qt>");
        }
        return;
    }

    bool daemonFailed = false;
    QDBusConnection bus = QDBusConnection::sessionBus();
    QPointer<OrgKdeKhotkeysInterface> iface = new OrgKdeKhotkeysInterface("org.kde.kded5", "/modules/khotkeys", bus, q);

    QDBusError err;
    if (!iface->isValid()) {
        err = iface->lastError();
        if (err.isValid()) {
            qCritical() << err.name() << ":" << err.message();
        }
        daemonFailed = true;
    }

    // prevent the daemon from writing dated information
    if (!daemonFailed)
        iface->declareConfigOutdated(); // mutex on

    if (current)
        applyCurrentItem();

    // Write the settings
    model->save();

    if (!iface->isValid()) {
        err = iface->lastError();
        if (err.isValid()) {
            qCritical() << err.name() << ":" << err.message();
        }
        daemonFailed = true;
    }

    // Reread the configuration. We have no possibility to check if it worked.
    if (daemonFailed)
        KMessageBox::error(q, "<qt>" + i18n("Unable to contact khotkeys. Your changes are saved, but they could not be activated.") + "</qt>");
    else
        iface->reread_configuration(); // mutex off
}

void KCMHotkeysPrivate::applyCurrentItem()
{
    Q_ASSERT(current);
    // Only save when really changed
    if (current->isChanged()) {
        current->apply();
    }
}

#include "kcm_hotkeys.moc"
