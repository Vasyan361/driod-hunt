#line 1 "/home/vasya/arduino/droid-hunt/Hunter/Config.h"
#define DROIDS_COUNT 1
#define MAX_DROIDS_COUNT 5

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define I2C_SDA 2
#define I2C_SCL 4

#define BACK_BUTTON_PIN 16
#define UP_BUTTON_PIN 17
#define DOWN_BUTTON_PIN 10
#define OK_BUTTON_PIN 11
#define CALL_BUTTON_PIN 3