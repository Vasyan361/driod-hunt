#include "Receiver.h"

typedef struct HunterData {
    uint8_t code = 0;
    uint16_t gameTime = GAME_TIME;
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

uint16_t Receiver::getGameTime()
{
    return hunterData.gameTime;
}