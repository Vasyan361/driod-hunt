#line 1 "/home/vasya/arduino/droid-hunt/Hunter/Hunter.ino"
#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "Constant.h"
#include "src/EspNow/StatusContainer.h"
#include "src/Logic/DisplayMenu.h"
#include "src/Devices/ButtonsControl.h"
#include "src/EspNow/Transmitter.h"
#include "src/EspNow/Receiver.h"

StatusContainer statusContainer;
DisplayMenu displayMenu;
ButtonsControl buttonsControl;
Transmitter transmitter;
Receiver receiver;

uint32_t timer = 0;

#line 21 "/home/vasya/arduino/droid-hunt/Hunter/Hunter.ino"
void setup();
#line 33 "/home/vasya/arduino/droid-hunt/Hunter/Hunter.ino"
void loop();
#line 44 "/home/vasya/arduino/droid-hunt/Hunter/Hunter.ino"
void initWiFi();
#line 21 "/home/vasya/arduino/droid-hunt/Hunter/Hunter.ino"
void setup() {
    Serial.begin(115200);

    initWiFi();

    statusContainer.init();
    transmitter.init(droidAddresses, &statusContainer);
    receiver.init();
    displayMenu.init(&statusContainer, &receiver);
    buttonsControl.init(&displayMenu, &transmitter);
}

void loop() {
    if (millis() - timer >= 20) {
        timer = millis();

        buttonsControl.readInput();
        displayMenu.navigate();
        transmitter.pushStatusToContainer();
        transmitter.send();
    }
}

void initWiFi()
{
    WiFi.mode(WIFI_STA);
 
    if (esp_now_init() != ESP_OK) {
        return;
    }

    WiFi.softAP(WIFI_FTM_SSID, WIFI_FTM_PASS, 1, 0, 4, true);
}
