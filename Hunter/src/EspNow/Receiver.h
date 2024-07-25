#pragma once

#include <Arduino.h>
#include <esp_now.h>
#include "../../Config.h"
#include "StatusCodes.h"

class Receiver
{
    public:
        void init();
        uint32_t getDistance(uint8_t id);
        uint8_t getConnectionStatus(uint8_t id);
    private:
};
