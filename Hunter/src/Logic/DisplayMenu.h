#pragma once

#include <Arduino.h>
#include "../../Config.h"
#include "../Devices/Display.h"
#include "../Devices/Display/BaseDisplay.h"
#include "../EspNow/Receiver.h"
#include "../EspNow/Transmitter.h"
#include "../EspNow/ControlCodes.h"

#ifdef LOCALE_RU
#include "../Devices/Display/DisplayRu.h"
#endif

#ifdef LOCALE_EN
#include "../Devices/Display/DisplayEn.h"
#endif

class DisplayMenu
{
    public:
        void init(Receiver* receiver, Transmitter* transmitter);
        void navigate();
        void okButtonClick();
        void upButtonClick();
        void downButtonClick();
        void backButtonClick();
        void callButtonClick();
    private:
        #ifdef LOCALE_RU
        DisplayRu display = DisplayRu();
        #endif
        #ifdef LOCALE_EN
        DisplayEn display = DisplayEn();
        #endif
        Transmitter* transmitter;
        uint8_t mode = 0;
        uint8_t peviousMode = 0;
        int8_t pointer = 0;
        uint8_t currentDroid = 0;
        uint8_t currentDroidId = 0;
        uint32_t lastCallTime = 0;
        int16_t callInterval = 0;
        int16_t betWeenCallInterval = 0;
        bool isCall = false;
        bool canCall = true;
        int16_t gameTime = MAX_GAME_TIME;
        enum {
            MAIN_SCREEN,
            DROID_SETTINGS,
            SETTINGS,
            SET_GAME_TIME_SCREEN,
            OK_SCREN,
            CALL_SCREN,
        } modes;
        enum {
            DROID_SETTING_CODE_CAUGHT,
            DROID_SETTING_CODE_RETURN_TO_GAME,
            DROID_SETTING_CODE_CALL_SEPARATELY,
        } droidSettingCodes;
        enum {
            SETTING_CODE_SET_GAME_TIME,
            SETTING_CODE_FINISH_THE_GAME,
        } settingCodes;
        int maxMode = 5;
        int maxPointerByMode[6] {
            5, //MAIN_SCREEN
            2, //DROID_SETTINGS
            2, //SETTINGS
            0, //SET_TIME_SCREEN    
            0, //OK_SCREN
            0, //CALL_SCREN
        };
        int nextModeMap[4][6] {
            {
                1, //MAIN_SCREEN => DROID_SETTINGS
                1, //MAIN_SCREEN => DROID_SETTINGS
                1, //MAIN_SCREEN => DROID_SETTINGS
                1, //MAIN_SCREEN => DROID_SETTINGS
                1, //MAIN_SCREEN => DROID_SETTINGS
                2, //MAIN_SCREEN => SETTINGS
            },
            {
                4, //DROID_SETTINGS => OK_SCREN
                4, //DROID_SETTINGS => OK_SCREN
                5, //DROID_SETTINGS => CALL_SCREN
            },
            {
                3, //SETTINGS => SET_GAME_TIME_SCREEN
                4, //SETTINGS => OK_SCREN
            },
            {
                4, //SET_GAME_TIME_SCREEN => OK_SCREN
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
        void droidSettingActions();
        void settingActions();
        void calculateCallTimers();
};
