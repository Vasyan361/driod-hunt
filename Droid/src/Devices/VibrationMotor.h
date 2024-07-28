#pragma once

#include <Arduino.h>
#include "../../Config.h"

class VibrationMotor
{
    public:
        void init();
        void run();
        void stop();
    private:
        uint32_t timer = 0;
        bool state;
};
