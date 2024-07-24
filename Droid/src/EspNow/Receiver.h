#pragma once

#include <Arduino.h>
#include <esp_now.h>

class Receiver
{
    public:
        void init();
        uint8_t getCode();
    private:
};
