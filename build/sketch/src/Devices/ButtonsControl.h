#line 1 "/home/vasya/arduino/droid-hunt/Hunter/src/Devices/ButtonsControl.h"
#pragma once

#include <Arduino.h>
#include <OneButton.h>
#include "../../Config.h"
#include "../Logic/DisplayMenu.h"
#include "../EspNow/Transmitter.h"

class ButtonsControl
{
    public:
        void init(DisplayMenu* displayMenu, Transmitter* transmitter);
        void readInput();
        void backButtonClick();
        void upButtonClick();
        void downButtonClick();
        void okButtonClick();
        void callButtonClick();
    private:
        OneButton buttons[5] {
            OneButton(BACK_BUTTON_PIN, true, true),
            OneButton(UP_BUTTON_PIN, true, true),
            OneButton(DOWN_BUTTON_PIN, true, true),
            OneButton(OK_BUTTON_PIN, true, true),
            OneButton(CALL_BUTTON_PIN, true, true),
        };
        enum {
            BACK_BUTTON,
            UP_BUTTON,
            DOWN_BUTTON,
            OK_BUTTON,
            CALL_BUTTON,
        } buttonNames;
        DisplayMenu* displayMenu;
        Transmitter* transmitter;
};

