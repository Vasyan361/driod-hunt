#pragma once

#include <Arduino.h>
#include "WiFi.h"


#define FTM_FRAME_COUNT 16   // Количество запрашиваемых кадров FTM (0 или 16, 24, 32, 64)
#define FTM_BURST_PERIOD 5   // Период между пакетами FTM в 100 миллисекунд (0 или 2-255)

class Ftm
{
    public:
        void init(const char * ssid, const char * password);
        void callFtmReport();
        uint32_t getDistance();
        uint32_t getTime();
    private:
};
