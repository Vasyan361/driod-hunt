#include "Transmitter.h"

String macStrings[DROIDS_COUNT];

typedef struct HunterData {
    uint8_t code = 0;
} HunterData;

HunterData hunterData;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    uint8_t macAddres[6];
    memcpy(&mac_addr, macAddres, sizeof(mac_addr));
}

void Transmitter::init(uint8_t droidAddresses[][6])
{
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    esp_now_register_send_cb(OnDataSent);

    for (uint8_t i = 0; i < DROIDS_COUNT; i++) {
        memcpy(peerInfo.peer_addr, droidAddresses[i], 6);
        if (esp_now_add_peer(&peerInfo) != ESP_OK){
            return;
        }
    }
}

void Transmitter::send()
{
    esp_now_send(0, (uint8_t *) &hunterData, sizeof(hunterData));
}

void Transmitter::setCode(uint8_t code)
{
    if (hunterData.code != code)
    {
        hunterData.code = code;
    }
}