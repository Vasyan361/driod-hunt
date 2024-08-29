#pragma once

#include <Arduino.h>
#include "BaseDisplay.h"

class DisplayEn : public BaseDisplay
{
    public:
        void mainScreen(int16_t callInterval, int16_t betWeenCallInterval)  override;
        void droidSettingsScreen(uint8_t serialNumber) override;
        void settingsScreen()  override;
        void setGameTimeScreen(uint16_t time) override;
    private:
        char statusMap[5][STATUS_MAX_LENGTH] = {
            "not defined",
            "not connected",
            "connected",
            "out of range",
            "caught",
        };
};