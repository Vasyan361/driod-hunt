#include "Transmitter.h"

String macStrings[DROIDS_COUNT];

typedef struct HunterData {
    uint8_t code = 0;
} HunterData;

HunterData hunterData[DROIDS_COUNT];
    
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
}

void Transmitter::init(uint8_t droidAddresses[][6])
{
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    esp_now_register_send_cb(OnDataSent);

    for (uint8_t i = 0; i < DROIDS_COUNT; i++) {
        memcpy(peerInfo.peer_addr, droidAddresses[i], 6);
        memcpy(Transmitter::droidAddresses[i], droidAddresses[i], 6);
        if (esp_now_add_peer(&peerInfo) != ESP_OK){
            return;
        }
    }
}

void Transmitter::send()
{
    for (uint8_t i = 0; i < DROIDS_COUNT; i++) {
        esp_now_send(droidAddresses[i], (uint8_t *) &hunterData[i], sizeof(hunterData[i]));
    }
}

void Transmitter::setCode(uint8_t code)
{
    for (uint8_t i = 0; i < DROIDS_COUNT; i++) {
        if (hunterData[i].code != code) {
            hunterData[i].code = code;
        }
    }
}

void Transmitter::setCode(uint8_t code, uint8_t id)
{
    if (hunterData[id].code != code) {
        hunterData[id].code = code;
    }
}