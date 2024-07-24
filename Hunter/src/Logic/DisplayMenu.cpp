#include "DisplayMenu.h"

void DisplayMenu::init(StatusContainer* statusContainer, Receiver* receiver)
{
    display.init(statusContainer, receiver);
}

void DisplayMenu::navigate()
{
    display.setPointer(pointer);
    switch (mode)
    {
        case MAIN_SCREEN: display.mainScreen(); break;
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

void DisplayMenu::modeAction()
{
    switch (mode)
    {
        case DROID_SETTINGS: currentDroid = pointer + 1; break;
        default: break;
    }
}