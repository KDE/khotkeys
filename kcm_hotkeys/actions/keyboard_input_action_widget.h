#ifndef KEYBOARD_INPUT_ACTION_WIDGET_H
#define KEYBOARD_INPUT_ACTION_WIDGET_H
/* SPDX-FileCopyrightText: 2009 Michael Jansen <kde@michael-jansen.biz>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "action_widget_base.h"
#include "ui_keyboard_input_action_widget.h"

/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class KeyboardInputActionWidget : public ActionWidgetBase
{
    Q_OBJECT

    typedef ActionWidgetBase Base;

public:
    /**
     * Default constructor
     */
    KeyboardInputActionWidget(KHotKeys::KeyboardInputAction *action, QWidget *parent = nullptr);

    /**
     * Destructor
     */
    ~KeyboardInputActionWidget() override;

    KHotKeys::KeyboardInputAction *action() override;
    const KHotKeys::KeyboardInputAction *action() const override;

    bool isChanged() const override;

protected:
    void doCopyFromObject() override;
    void doCopyToObject() override;

    Ui::KeyboardInputActionWidget ui;
};

#endif /* #ifndef KEYBOARD_INPUT_ACTION_WIDGET_H */
