#pragma once

#include <Arduino.h>
#include "Constants.h"
#include "src/Logic/HunterLogic.h"

HunterLogic hunterLogic;

void setup() {
    hunterLogic.init(droidAddresses, WIFI_FTM_SSID, WIFI_FTM_PASS);
}

void loop() {
    hunterLogic.run();
}