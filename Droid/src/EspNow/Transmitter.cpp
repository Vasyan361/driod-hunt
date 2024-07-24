#include "Transmitter.h"

typedef struct DroidData {
    uint8_t id = DROID_ID;
    uint8_t status = 0;
    uint32_t distance = 0;
} DroidData;

DroidData droidData;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
}

void Transmitter::init(uint8_t hunterAddress[6])
{
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;

    esp_now_register_send_cb(OnDataSent);

    memcpy(peerInfo.peer_addr, hunterAddress, 6);
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        return;
    }
}

void Transmitter::send(uint32_t distance)
{
    droidData.distance = distance;
    esp_now_send(0, (uint8_t *) &droidData, sizeof(droidData));
}