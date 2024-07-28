#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "../../Config.h"

class Backlight
{
    public:
        void init();
        void run();
        void stop();
    private:
        Adafruit_NeoPixel pixel = Adafruit_NeoPixel(2, LIGHT_PIN, NEO_GRB + NEO_KHZ800);
        uint32_t timer = 0;
        uint8_t state = 0;
        int red = 0;
        int green = 0;
        int blue = 0;
};
