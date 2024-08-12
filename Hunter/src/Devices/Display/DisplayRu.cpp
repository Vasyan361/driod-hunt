#include "DisplayRu.h"

void DisplayRu::init(Receiver* receiver)
{
    DisplayRu::receiver = receiver;

    Wire.setPins(I2C_SDA, I2C_SCL);

    if(!oled.begin(SCREEN_ADDRESS)) {
        return;
    }

    oled.cp437(true);

    startScreen();
}

void DisplayRu::mainScreen(int16_t callInterval, int16_t betWeenCallInterval)
{
    prepareForPrint();

    if (callInterval > 0) {
        oled.printf("      %s %dc\n", utf8rus("Вызов"), callInterval);
    } else if (betWeenCallInterval > 0) {
        oled.printf("      %s %dc\n", utf8rus("Ждите"), betWeenCallInterval);
    } else {
        oled.println(utf8rus("   Готов к вызову"));
    }

    oled.print(F("=====================\n"));

    for (uint8_t i = 0; i < MAX_DROIDS_COUNT; i++)
    {
        if (STATUS_CONNECTED == receiver->getStatus(i))
        {
            oled.printf(" %d %s %d\n", i + 1, utf8rus(statusMap[receiver->getStatus(i)]), receiver->getDistance(i));
        } else {
            oled.printf(" %d %s\n", i + 1, utf8rus(statusMap[receiver->getStatus(i)]));
        }
    }

    oled.println(utf8rus(" Настройки"));
    

    printPointer(2);

    oled.display();
}

void DisplayRu::droidSettingsScreen(uint8_t serialNumber)
{
    prepareForPrint();
    oled.printf("       %s %d\n", utf8rus("Дройд"), serialNumber);
    oled.println( "=====================");
    oled.println(utf8rus( " Пойман"));
    oled.println(utf8rus( " Вернуть в игру"));
    oled.println(utf8rus( " Вызвать отдельно"));

    printPointer(2);

    oled.display();
}

void DisplayRu::settingsScreen()
{
    prepareForPrint();
    oled.println(utf8rus("   Настройки игры"));
    oled.println( "=====================");
    oled.println(utf8rus( " Время игры"));
    oled.println( utf8rus(" Закончить игру"));

    printPointer(2);

    oled.display();  
}

void DisplayRu::setGameTimeScreen(uint16_t time)
{
    prepareForPrint();
    oled.println(utf8rus("      Время игры"));
    oled.println( "=====================");

    oled.setTextSize(5);

    uint16_t minuts = time % 60;
    if (minuts == 0) {
        oled.printf("%d:00", time / 60);
    } else {
        oled.printf("%d:%d", time / 60, minuts);
    }
    
    
    oled.display();
}

String DisplayRu::utf8rus(String source)
{
    int i,k;
    String target;
    unsigned char n;
    char m[2] = { '0', '\0' };

    k = source.length(); i = 0;

    while (i < k) {
        n = source[i]; i++;

        if (n >= 0xC0) {
        switch (n) {
            case 0xD0: {
            n = source[i]; i++;
            if (n == 0x81) { n = 0xA8; break; }
            if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
            break;
            }
            case 0xD1: {
            n = source[i]; i++;
            if (n == 0x91) { n = 0xB8; break; }
            if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
            break;
            }
        }
        }
        m[0] = n; target = target + String(m);
    }
    return target;
}