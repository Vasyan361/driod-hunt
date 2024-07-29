#include "DriodLigic.h"

void DriodLigic::init(uint8_t hunterAddress[6], const char * ssid, const char * password)
{
    Serial.begin(115200);

    initWiFi();
    
    receiver.init();
    transmitter.init(hunterAddress);
    // ftm.init(ssid, password);
    sound.init();
    vibrationMotor.init();
    backlight.init();
}

void DriodLigic::run()
{
    if (millis() - timer >= 20) {
        // ftm.callFtmReport();
        // transmitter.send(ftm.getDistance());
        transmitter.setDistance(0);
        transmitter.setStatus(STATUS_CONNECTED);
        transmitter.send();
    }

    if (receiver.getCode() != peviousCode)
    {
        peviousCode = receiver.getCode();
    }

    droidActions();
}

void DriodLigic::initWiFi()
{
    WiFi.mode(WIFI_STA);
 
    if (esp_now_init() != ESP_OK) {
        return;
    }
}

void DriodLigic::droidActions()
{
    switch (peviousCode)
    {
    case CONTROL_CODE_DEFAULT:
        vibrationMotor.stop();
        backlight.stop();
        break;
    case CONTROL_CODE_CALL:
        sound.play();
        vibrationMotor.run();
        backlight.run();
        break;
    default:
        break;
    }
}