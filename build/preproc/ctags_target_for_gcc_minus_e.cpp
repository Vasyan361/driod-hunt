# 1 "/home/vasya/arduino/droid-hunt/Hunter/Hunter.ino"
       

# 4 "/home/vasya/arduino/droid-hunt/Hunter/Hunter.ino" 2
# 5 "/home/vasya/arduino/droid-hunt/Hunter/Hunter.ino" 2
# 6 "/home/vasya/arduino/droid-hunt/Hunter/Hunter.ino" 2
# 7 "/home/vasya/arduino/droid-hunt/Hunter/Hunter.ino" 2
# 8 "/home/vasya/arduino/droid-hunt/Hunter/Hunter.ino" 2
# 9 "/home/vasya/arduino/droid-hunt/Hunter/Hunter.ino" 2
# 10 "/home/vasya/arduino/droid-hunt/Hunter/Hunter.ino" 2



StatusContainer statusContainer;
DisplayMenu displayMenu;
ButtonsControl buttonsControl;
Transmitter transmitter;
Receiver receiver;

uint32_t timer = 0;

void setup() {
    Serial.begin(115200);

    initWiFi();

    statusContainer.init();
    transmitter.init(droidAddresses, &statusContainer);
    receiver.init();
    displayMenu.init(&statusContainer, &receiver);
    buttonsControl.init(&displayMenu, &transmitter);
}

void loop() {
    if (millis() - timer >= 20) {
        timer = millis();

        buttonsControl.readInput();
        displayMenu.navigate();
        transmitter.pushStatusToContainer();
        transmitter.send();
    }
}

void initWiFi()
{
    WiFi.mode(WIFI_MODE_STA);

    if (esp_now_init() != 0 /*!< esp_err_t value indicating success (no error) */) {
        return;
    }

    WiFi.softAP(WIFI_FTM_SSID, WIFI_FTM_PASS, 1, 0, 4, true);
}
