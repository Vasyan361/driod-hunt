#pragma once

#include <Arduino.h>
#include "../../Config.h"
#include "../Devices/Display.h"
#include "../EspNow/StatusContainer.h"
#include "../EspNow/Receiver.h"
#include "../EspNow/Transmitter.h"
#include "../EspNow/ControlCodes.h"

class DisplayMenu
{
    public:
        void init(StatusContainer* statusContainer, Receiver* receiver, Transmitter* transmitter);
        void navigate();
        void okButtonClick();
        void upButtonClick();
        void downButtonClick();
        void backButtonClick();
        void callButtonClick();
    private:
        Display display = Display();
        Transmitter* transmitter;
        uint8_t mode = 0;
        int8_t pointer = 0;
        uint8_t currentDroid = 0;
        uint32_t lastCallTime = 0;
        int16_t callInterval = 0;
        int16_t betWeenCallInterval = 0;
        bool isCall = false;
        bool canCall = true;
        enum {
            MAIN_SCREEN,
            DROID_SETTINGS,
            SETTINGS,
            OK_SCREN,
            CALL_SCREN,
        } modes;
        int maxMode = 4;
        int maxPointerByMode[5] {
            5, //MAIN_SCREEN
            2, //DROID_SETTINGS
            2, //SETTINGS
            0, //OK_SCREN
            0, //CALL_SCREN
        };
        int nextModeMap[3][6] {
            {
                1, //MAIN_SCREEN => DROID_SETTINGS
                1, //MAIN_SCREEN => DROID_SETTINGS
                1, //MAIN_SCREEN => DROID_SETTINGS
                1, //MAIN_SCREEN => DROID_SETTINGS
                1, //MAIN_SCREEN => DROID_SETTINGS
                2, //MAIN_SCREEN => SETTINGS
            },
            {
                3, //DROID_SETTINGS => OK_SCREN
                3, //DROID_SETTINGS => OK_SCREN
                4, //DROID_SETTINGS => CALL_SCREN
            },
            {
                3, //SETTINGS => SETTINGS
                3, //SETTINGS => SETTINGS
                3, //SETTINGS => SETTINGS
            },
        };
        int previousModeMap[5] {
            0, //MAIN_SCREEN => MAIN_SCREEN
            0, //DROID_SETTINGS => MAIN_SCREEN
            0, //SETTINGS => MAIN_SCREEN
            0, //CALL_SCREN => MAIN_SCREEN
            0, //CALL_SCREN => MAIN_SCREEN
        };
        void modeAction();
        void calculateCallTimers();
};
