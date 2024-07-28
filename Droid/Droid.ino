#pragma once

#include <Arduino.h>
#include "Constant.h"
#include "src/Logic/DriodLigic.h"

DriodLigic driodLigic;

void setup() {
    driodLigic.init(hunterAddress, WIFI_FTM_SSID, WIFI_FTM_PASS);
}
void loop() {
    driodLigic.run();
}
