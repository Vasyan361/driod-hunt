#pragma once

#include <Arduino.h>
#include <esp_now.h>
#include "../../Config.h"

class Receiver
{
    public:
        void init();
        uint8_t getCode();
        uint16_t getGameTime();
    private:
};
