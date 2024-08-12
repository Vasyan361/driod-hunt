#include "BaseDisplay.h"

void BaseDisplay::init(Receiver* receiver)
{
    BaseDisplay::receiver = receiver;

    Wire.setPins(I2C_SDA, I2C_SCL);

    if(!oled.begin(SCREEN_ADDRESS)) {
        return;
    }

    startScreen();
}

void BaseDisplay::setPointer(uint8_t pointer)
{
    BaseDisplay::pointer = pointer;
}

void BaseDisplay::prepareForPrint()
{
    oled.clearDisplay();
    oled.setCursor(0,0); 

    oled.setTextSize(1);
    oled.setTextColor(SH110X_WHITE);
}

void BaseDisplay::printPointer()
{
    printPointer(0);
}

void BaseDisplay::printPointer(uint8_t alignment)
{
    oled.setCursor(0, 8 * (pointer + alignment));
    oled.print(">");
}

void BaseDisplay::mainScreen(int16_t callInterval, int16_t betWeenCallInterval)
{
}

void BaseDisplay::droidSettingsScreen(uint8_t serialNumber)
{
}

void BaseDisplay::settingsScreen()
{
}

void BaseDisplay::okScreen()
{
    for (uint8_t i = 0; i < 27; i++)
    {
        oled.clearDisplay();
        oled.drawBitmap(32, 0, okFrames[i], 64, 64, 1);
        oled.display();
    }
}


void BaseDisplay::callScreen()
{
    for (uint8_t i = 0; i < 27; i++)
    {
        oled.clearDisplay();
        oled.drawBitmap(32, 0, callFrames[i], 64, 64, 1);
        oled.display();
    }
}

void BaseDisplay::setGameTimeScreen(uint16_t time)
{
}

void BaseDisplay::startScreen()
{
    prepareForPrint();

    oled.println(F("====================="));
    oled.println(F("     Droid Hunt"));
    oled.println(F("====================="));

    oled.display();

    delay(1000);
}