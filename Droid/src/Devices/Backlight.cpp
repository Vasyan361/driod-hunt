#include "Backlight.h"

void Backlight::init()
{
    pixel.begin();
}

void Backlight::run()
{
    if (millis() - timer > 300) {
        timer = millis();

        state++;
        if (state >= 3) {
            state = 0;
        }
    }

    switch (state)
    {
    case 0:
        red = 255;
        green = 0;
        blue = 0;

        break;
    case 1:
        red = 0;
        green = 255;
        blue = 0;

        break;
    case 2:
        red = 0;
        green = 0;
        blue = 255;

        break;
    default:
        break;
    }

    for (int i = 0; i < 2; i++) {
        pixel.setPixelColor(i, pixel.Color(red, green, blue));
    }

    pixel.show();
}

void Backlight::stop()
{
    for (int i = 0; i < 2; i++) {
        pixel.setPixelColor(i, pixel.Color(0, 0, 0));
    }

    pixel.show();
}