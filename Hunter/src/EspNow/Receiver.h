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
