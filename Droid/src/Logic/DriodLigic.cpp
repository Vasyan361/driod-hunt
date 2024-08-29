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
        timer = millis();
        ftm.callFtmReport();
        transmitter.setDistance(ftm.getDistance());
        transmitter.setStatus(currentStatus);
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
        stopDroid();

        break;
    case CONTROL_CODE_CALL:
        if (!isCaught) {
            if (isInRange()) {
                currentStatus = STATUS_CONNECTED;
                callByTimer();
            }else {
                currentStatus = STATUS_OUT_OF_RANGE;
            }
        }

        break;
    case CONTROL_CODE_CAUGHT:
        isCaught = true;
        currentStatus = STATUS_CAUGHT;
        
        break;
    case CONTROL_CODE_RETURN_TO_GAME:
        isCaught = false;
        currentStatus = STATUS_CONNECTED;

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

    if (isCall) {
        callByTimer();
    }
}

void DriodLigic::callDroid()
{
    // sound.play();
    vibrationMotor.run();
    backlight.run();
}

void DriodLigic::stopDroid()
{
    vibrationMotor.stop();
    backlight.stop();
}

void DriodLigic::callByTimer()
{
    if (!isCall) {
        callTimer = millis();
        isCall = true;
    } else if(millis() - callTimer <= callTimeout) {
        callDroid();
    } else {
        isCall = false;
        stopDroid();
    }
}

bool DriodLigic::isInRange()
{
    return ftm.getDistance() <= MIN_DISTANCE || ftm.getDistance() >= MAX_DISTANCE;
}