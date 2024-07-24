#pragma once

#include <Arduino.h>
#include <esp_now.h>
#include "../../Config.h"

class Transmitter
{
    public:
        void init(uint8_t hunterAddress[6]);
        void send(uint32_t distance);
    private:
        esp_now_peer_info_t peerInfo = {};
};