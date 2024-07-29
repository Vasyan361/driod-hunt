#include "DisplayMenu.h"

void DisplayMenu::init(Receiver* receiver, Transmitter* transmitter)
{
    DisplayMenu::transmitter = transmitter;
    display.init(receiver);
}

void DisplayMenu::navigate()
{
    display.setPointer(pointer);
    calculateCallTimers();
    switch (mode)
    {
        case MAIN_SCREEN: display.mainScreen(callInterval, betWeenCallInterval); break;
        case DROID_SETTINGS: display.droidSettingsScreen(currentDroid); break;
        case SETTINGS: display.settingsScreen(); break;
        case OK_SCREN: display.okScreen(); mode = MAIN_SCREEN; break;
        case CALL_SCREN: display.callScreen(); mode = MAIN_SCREEN; break;
        default: break;
    }
}

void DisplayMenu::okButtonClick()
{
    mode = nextModeMap[mode][pointer];
    
    if (mode > maxMode) {
        mode = 0;
    }

    modeAction();

    pointer = 0;   
}

void DisplayMenu::upButtonClick()
{
    pointer--;
    if (pointer < 0) {
        pointer = maxPointerByMode[mode];
    }
}

void DisplayMenu::downButtonClick()
{
    pointer++;
    if (pointer > maxPointerByMode[mode]) {
       pointer = 0;
    }
}

void DisplayMenu::backButtonClick()
{
    mode = previousModeMap[mode];

    pointer = 0; 
}

void DisplayMenu::callButtonClick()
{
    if (canCall && !isCall) {
        transmitter->setCode(CONTROL_CODE_CALL);
        canCall = false;
        isCall = true;
        lastCallTime = millis();
    }
}

void DisplayMenu::modeAction()
{
    switch (mode)
    {
        case DROID_SETTINGS: currentDroid = pointer + 1; break;
        default: break;
    }
}

void DisplayMenu::calculateCallTimers()
{
    if (!canCall) {
        uint32_t lastCallIntervall = millis() - lastCallTime;
        if (isCall) {
            callInterval = CALL_TIME - (lastCallIntervall / 1000);
            if (callInterval <= 0) {
                isCall = false;
                transmitter->setCode(CONTROL_CODE_DEFAULT);
            }
        }
        
        betWeenCallInterval = (CALL_TIME + BETWEEN_CALL_TIME) - (lastCallIntervall / 1000);
        if (betWeenCallInterval <= 0) {
            canCall = true;
        }
    }
}