#pragma once

#include <Arduino.h>
#include "../../Config.h"
#include "StatusCodes.h"

class StatusContainer
{
    public:
        void init();
        void setStatus(uint8_t id, uint8_t statusCode);
        uint8_t getStatus(uint8_t id);
    private:
        uint8_t statusCodes[MAX_DROIDS_COUNT];
};
