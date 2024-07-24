#include "HunterLogic.h"

void HunterLogic::init(uint8_t droidAddresses[][6], const char * WIFI_FTM_SSID, const char * WIFI_FTM_PASS)
{
    Serial.begin(115200);

    initWiFi(WIFI_FTM_SSID, WIFI_FTM_PASS);

    statusContainer.init();
    transmitter.init(droidAddresses);
    receiver.init();
    displayMenu.init(&statusContainer, &receiver);
    buttonsControl.init(&displayMenu, &transmitter);
}

void HunterLogic::run()
{
    if (millis() - timer >= 20) {
        timer = millis();

        buttonsControl.readInput();
        displayMenu.navigate();
        transmitter.send();
    }
}

void HunterLogic::initWiFi(const char * WIFI_FTM_SSID, const char * WIFI_FTM_PASS)
{
    WiFi.mode(WIFI_STA);
 
    if (esp_now_init() != ESP_OK) {
        return;
    }

    WiFi.softAP(WIFI_FTM_SSID, WIFI_FTM_PASS, 1, 0, 4, true);
}