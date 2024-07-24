#pragma once

#include <Arduino.h>
#include <esp_now.h>
#include "../../Config.h"
#include "StatusContainer.h"
#include "StatusCodes.h"

class Transmitter
{
    public:
        void init(uint8_t droidAddresses[][6]);
        void send();
        void setCode(uint8_t code);
    private:
        esp_now_peer_info_t peerInfo = {};
        u_int32_t timer;
        bool isCall = false;
};