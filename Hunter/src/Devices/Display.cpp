#include "Display.h"

void Display::init(StatusContainer* statusContainer, Receiver* receiver)
{
    Display::statusContainer = statusContainer;
    Display::receiver = receiver;

    Wire.setPins(I2C_SDA, I2C_SCL);

    if(!oled.begin(SCREEN_ADDRESS)) {
        return;
    }

    prepareForPrint();

    oled.println(F("====================="));
    oled.println(F("     Droid Hunt"));
    oled.println(F("====================="));

    oled.display();

    delay(1000);
}

void Display::setPointer(int pointer)
{
    Display::pointer = pointer;
}

void Display::prepareForPrint()
{
    oled.clearDisplay();
    oled.setCursor(0,0); 

    oled.setTextSize(1);
    oled.setTextColor(SH110X_WHITE);
}

void Display::printPointer()
{
    printPointer(0);
}

void Display::printPointer(int alignment)
{
    oled.setCursor(0, 8 * (pointer + alignment));
    oled.print(">");
}

void Display::mainScreen()
{
    prepareForPrint();

    oled.print(F(
        "     Droid Hunt\n"
        "=====================\n"
    ));

    for (uint8_t i = 0; i < MAX_DROIDS_COUNT; i++)
    {
        if (STATUS_CONNECTED == receiver->getConnectionStatus(i))
        {
            oled.printf(" %d %s %d\n", i + 1, statusMap[statusContainer->getStatus(i)], receiver->getDistance(i));
        } else {
            oled.printf(" %d %s\n", i + 1, statusMap[statusContainer->getStatus(i)]);
        }
    }

    oled.println(F(" Settings"));
    

    printPointer(2);

    oled.display();
}

void Display::droidSettingsScreen(uint8_t serialNumber)
{
    prepareForPrint();
    oled.printf("       Droid %d\n", serialNumber);

    oled.print(F(
        "=====================\n"
        " Caught\n"
        " Return to game\n"
        " Call separately\n"
    ));


    printPointer(2);

    oled.display();
}

void Display::settingsScreen()
{
    prepareForPrint();

    oled.print(F(
        "    Game settings\n"
        "=====================\n"
        " Set game time\n"
        " Finish the game\n"
    ));

    printPointer(2);

    oled.display();  
}

void Display::okScreen()
{
    for (uint8_t i = 0; i < 27; i++)
    {
        oled.clearDisplay();
        oled.drawBitmap(32, 0, okFrames[i], 64, 64, 1);
        oled.display();
    }
}


void Display::callScreen()
{
    for (uint8_t i = 0; i < 27; i++)
    {
        oled.clearDisplay();
        oled.drawBitmap(32, 0, callFrames[i], 64, 64, 1);
        oled.display();
    }
}