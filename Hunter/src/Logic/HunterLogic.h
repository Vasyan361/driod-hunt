#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "../EspNow/StatusContainer.h"
#include "DisplayMenu.h"
#include "../Devices/ButtonsControl.h"
#include "../EspNow/Transmitter.h"
#include "../EspNow/Receiver.h"


class HunterLogic
{
    public:
        void init(uint8_t droidAddresses[][6], const char * WIFI_FTM_SSID, const char * WIFI_FTM_PASS);
        void run();
    private:
        StatusContainer statusContainer;
        DisplayMenu displayMenu;
        ButtonsControl buttonsControl;
        Transmitter transmitter;
        Receiver receiver;
        uint32_t timer = 0;
        void initWiFi(const char * WIFI_FTM_SSID, const char * WIFI_FTM_PASS);
};
