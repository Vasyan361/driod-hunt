#pragma once

#include <Arduino.h>
#include <esp_now.h>
#include "../../Config.h"

class Transmitter
{
    public:
        void init(uint8_t hunterAddress[6]);
        void setDistance(uint32_t distance);
        void setStatus(uint8_t status);
        void send();
    private:
        esp_now_peer_info_t peerInfo = {};
};