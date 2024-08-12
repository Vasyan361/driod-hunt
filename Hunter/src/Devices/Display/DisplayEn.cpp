#include "DisplayEn.h"

void DisplayEn::mainScreen(int16_t callInterval, int16_t betWeenCallInterval)
{
    prepareForPrint();

    if (callInterval > 0) {
        oled.printf("     Calling %ds\n", callInterval);
    } else if (betWeenCallInterval > 0) {
        oled.printf("      Wait %ds\n", betWeenCallInterval);
    } else {
        oled.print(F("    Ready to call\n"));
    }

    oled.print(F("=====================\n"));

    for (uint8_t i = 0; i < MAX_DROIDS_COUNT; i++)
    {
        if (STATUS_CONNECTED == receiver->getStatus(i))
        {
            oled.printf(" %d %s %d\n", i + 1, statusMap[receiver->getStatus(i)], receiver->getDistance(i));
        } else {
            oled.printf(" %d %s\n", i + 1, statusMap[receiver->getStatus(i)]);
        }
    }

    oled.println(F(" Settings"));
    

    printPointer(2);

    oled.display();
}

void DisplayEn::droidSettingsScreen(uint8_t serialNumber)
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

void DisplayEn::settingsScreen()
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

void DisplayEn::setGameTimeScreen(uint16_t time)
{
    prepareForPrint();
    oled.print(F(
        "    Set game time\n"
        "=====================\n\n"
    ));

    oled.setTextSize(5);

    uint16_t minuts = time % 60;
    if (minuts == 0) {
        oled.printf("%d:00", time / 60);
    } else {
        oled.printf("%d:%d", time / 60, minuts);
    }
    
    
    oled.display();
}