#line 1 "/home/vasya/arduino/droid-hunt/Hunter/src/EspNow/Receiver.h"
#pragma once

#include <Arduino.h>
#include <esp_now.h>

class Receiver
{
    public:
        void init();
        uint32_t getDistance(uint8_t id);
    private:
};
