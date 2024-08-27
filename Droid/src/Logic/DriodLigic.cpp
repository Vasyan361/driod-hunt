#include "DriodLigic.h"

void DriodLigic::init(uint8_t hunterAddress[6], const char * ssid, const char * password)
{
    callTimeout = CALL_TIME * 1000;
    gameTime = GAME_TIME * 60 * 1000;

    Serial.begin(115200);

    initWiFi();
    
    receiver.init();
    transmitter.init(hunterAddress);
    ftm.init(ssid, password);
    sound.init();
    vibrationMotor.init();
    backlight.init();
}

void DriodLigic::run()
{
    if (millis() - timer >= 20) {
        ftm.callFtmReport();
        transmitter.setDistance(ftm.getDistance());
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
        if (!isCaught) {
            callDroid();
        }

        break;
    case CONTROL_CODE_CAUGHT:
        isCaught = true;
        
        break;
    case CONTROL_CODE_RETURN_TO_GAME:
        isCaught = false;

        break;
    case CONTROL_CODE_CALL_SEPARATALY:
        callDroid();

        break;
    case CONTROL_CODE_SET_GAME_TIME:
        gameTime = receiver.getGameTime() * 60 * 1000;

        break;
    default:
        break;
    }
}

void DriodLigic::callDroid()
{
    if (!isCall) {
        callTimer = millis();
        isCall = true;
    } else if(millis() - callTimer <= callTimeout) {
        sound.play();
        vibrationMotor.run();
        backlight.run();
    } else {
        isCall = false;
        vibrationMotor.stop();
        backlight.stop();
    }
}