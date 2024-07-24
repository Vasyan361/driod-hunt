#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "Constant.h"
#include "Signal.h"
#include "src/EspNow/Receiver.h"
#include "src/EspNow/Transmitter.h"
#include "src/Ftm/Ftm.h"
#include "src/Devices/Sound.h"
// #include <Adafruit_NeoPixel.h>

Receiver receiver;
Transmitter transmitter;
Ftm ftm;
Sound sound;

// Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, 3, NEO_GRB + NEO_KHZ800);

uint32_t timer = 0;

uint8_t peviousCode = 0;

bool state = false;
uint32_t stateTimer = 0;


void setup() {
    // Serial.begin(115200);
    
    // initWiFi();
    
    // receiver.init();
    // transmitter.init(hunterAddress);
    // // ftm.init(WIFI_FTM_SSID, WIFI_FTM_PASS);
    // sound.init();
    // // pixel.begin();
    pinMode(1, OUTPUT);
}
void loop() {
    digitalWrite(1, HIGH);
    delay(1000);
    digitalWrite(1, LOW);
    delay(1000);
    // if (millis() - timer >= 20) {
    //     timer = millis();

    //     // ftm.callFtmReport();
    //     // transmitter.send(ftm.getDistance());
    //     transmitter.send(0);

    //     Serial.println(peviousCode);

    //     if (receiver.getCode() != peviousCode)
    //     {
    //         if (receiver.getCode() == 1)
    //         {
    //             state = true;
    //             stateTimer = millis();
    //         }
            
    //         peviousCode = receiver.getCode();
    //     }

    //     if (state)
    //     {
    //         digitalWrite(1, HIGH);
    //         // pixel.clear();
    //         // pixel.setPixelColor(0, pixel.Color(0, 255, 0));
    //         // pixel.show();
    //         sound.play();
    //     } else {
    //         digitalWrite(1, LOW);
    //         // pixel.clear();
    //         // pixel.setPixelColor(0, pixel.Color(0, 0, 0));
    //         // pixel.show();
    //     }
        
    //     if (millis() - stateTimer >= 2000) {
    //         state = false;
    //     }
        
    // }
}

void initWiFi()
{
    WiFi.mode(WIFI_STA);
 
    if (esp_now_init() != ESP_OK) {
        return;
    }
}