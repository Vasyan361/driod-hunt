#include <WiFi.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("ESP Board MAC Address: ");
  Serial.println(WiFi.macAddress());
  delay(1000);
}