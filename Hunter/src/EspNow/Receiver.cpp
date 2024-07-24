#include "Receiver.h"
#include "../../Config.h"

typedef struct DroidData {
    uint8_t id = 0;
    uint8_t status = 0;
    uint32_t distance = 0;
} DroidData;

DroidData droidsData[DROIDS_COUNT];

DroidData tempDroidData;

void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
    memcpy(&tempDroidData, incomingData, sizeof(tempDroidData));
    memcpy(&droidsData[tempDroidData.id], incomingData, sizeof(tempDroidData));
}

void Receiver::init()
{
    esp_now_register_recv_cb(OnDataRecv);
}

uint32_t Receiver::getDistance(uint8_t id)
{
    return droidsData[id].distance;
}