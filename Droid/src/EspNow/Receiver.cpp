#include "Receiver.h"
#include "../../Config.h"

typedef struct HunterData {
    uint8_t code = 0;
} HunterData;

HunterData hunterData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    memcpy(&hunterData, incomingData, sizeof(hunterData));
}

void Receiver::init()
{
    esp_now_register_recv_cb(OnDataRecv);
}

uint8_t Receiver::getCode()
{
    return hunterData.code;
}