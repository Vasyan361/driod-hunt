#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "../EspNow/Receiver.h"
#include "../EspNow/Transmitter.h"
#include "../EspNow/ControlCodes.h"
#include "../Ftm/Ftm.h"
#include "../Devices/Sound.h"
#include "../Devices/VibrationMotor.h"
#include "../Devices/Backlight.h"

class DriodLigic
{
    public:
        void init(uint8_t droidAddresses[6], const char * ssid, const char * password);
        void run();
    private:
        void initWiFi();
        Receiver receiver;
        Transmitter transmitter;
        Ftm ftm;
        Sound sound;
        VibrationMotor vibrationMotor;
        Backlight backlight;
        uint8_t peviousCode = 0;
        uint32_t timer = 0;
        void droidActions();
};
