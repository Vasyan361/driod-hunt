#pragma once

#include <Arduino.h>
#include "BaseDisplay.h"

class DisplayRu : public BaseDisplay
{
    public:
        void init(Receiver* receiver);
        void mainScreen(int16_t callInterval, int16_t betWeenCallInterval)  override;
        void droidSettingsScreen(uint8_t serialNumber) override;
        void settingsScreen()  override;
        void setGameTimeScreen(uint16_t time) override;
    private:
        String utf8rus(String source);
        char statusMap[5][STATUS_MAX_LENGTH] = {
            "не определен",
            "не подключен",
            "подключен",
            "вне диапазона",
            "пойман",
        };
};