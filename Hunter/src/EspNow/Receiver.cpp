#include "Receiver.h"

typedef struct DroidData {
    uint8_t id = 0;
    uint8_t status = 0;
    uint32_t distance = 0;
} DroidData;

DroidData droidsData[DROIDS_COUNT];

DroidData tempDroidData;

uint32_t lastReciveTimers[MAX_DROIDS_COUNT];

void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
    memcpy(&tempDroidData, incomingData, sizeof(tempDroidData));
    memcpy(&droidsData[tempDroidData.id], incomingData, sizeof(tempDroidData));
    lastReciveTimers[tempDroidData.id] = millis();
}

void Receiver::init()
{
    esp_now_register_recv_cb(OnDataRecv);

    for (uint8_t i = 0; i < MAX_DROIDS_COUNT; i++)
    {
        lastReciveTimers[i] = 0;
    }
}

uint32_t Receiver::getDistance(uint8_t id)
{
    return droidsData[id].distance;
}

uint8_t Receiver::getConnectionStatus(uint8_t id)
{
    return millis() - lastReciveTimers[id] < 200 ? STATUS_CONNECTED : STATUS_NOT_CONNECTED;
}