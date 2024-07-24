#line 1 "/home/vasya/arduino/droid-hunt/Hunter/src/EspNow/Transmitter.cpp"
#include "Transmitter.h"

String macStrings[DROIDS_COUNT];
uint8_t statusCodes[DROIDS_COUNT];

typedef struct HunterData {
    uint8_t code = 0;
} HunterData;

HunterData hunterData;

char* convertMacToStrng(uint8_t macAddress[6])
{
    char macString[18];

    snprintf(
        macString,
        sizeof(macString),
        "%02x:%02x:%02x:%02x:%02x:%02x",
        macAddress[0],
        macAddress[1],
        macAddress[2],
        macAddress[3],
        macAddress[4],
        macAddress[5]
    );

    return macString;
}

void setStatusByMac(uint8_t macAddres[6], uint8_t statusCode)
{
    String macString = convertMacToStrng(macAddres);

    for (uint8_t i = 0; i < DROIDS_COUNT; i++) {
        if (macStrings[i] == macString) {
            statusCodes[i] = statusCode;
            return;
        }
    }
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    uint8_t macAddres[6];
    memcpy(&mac_addr, macAddres, sizeof(mac_addr));

    // statusCodes[0] =  status == ESP_NOW_SEND_SUCCESS ? STATUS_CONNECTED : STATUS_NOT_CONNECTED; 

    setStatusByMac(macAddres, status == ESP_NOW_SEND_SUCCESS ? STATUS_CONNECTED : STATUS_NOT_CONNECTED);
}


void Transmitter::init(uint8_t droidAddresses[][6], StatusContainer* statusContainer)
{
    Transmitter::statusContainer = statusContainer;

    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    esp_now_register_send_cb(OnDataSent);

    for (uint8_t i = 0; i < DROIDS_COUNT; i++) {
        macStrings[i] = convertMacToStrng(droidAddresses[i]);
        statusCodes[i] = STATUS_NOT_CONNECTED;
        memcpy(peerInfo.peer_addr, droidAddresses[i], 6);
        if (esp_now_add_peer(&peerInfo) != ESP_OK){
            return;
        }
    }
}

void Transmitter::pushStatusToContainer()
{
    for (uint8_t i = 0; i < DROIDS_COUNT; i++) {
        statusContainer->setStatus(i, statusCodes[i]);
    }
}

void Transmitter::send()
{
    if (isCall && millis() - timer >= 3000)
    {
        hunterData.code = 0;
        isCall = false;
    }
    
    esp_now_send(0, (uint8_t *) &hunterData, sizeof(hunterData));
}

void Transmitter::setCode(uint8_t code)
{
    if (hunterData.code != code)
    {
        hunterData.code = code;
        timer = millis();
        isCall = true;
    }
    
}