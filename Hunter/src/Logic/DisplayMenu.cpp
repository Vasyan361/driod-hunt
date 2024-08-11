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
        case SET_GAME_TIME_SCREEN: display.setGameTimeScreen(gameTime); break;
        case OK_SCREN: display.okScreen(); mode = MAIN_SCREEN; break;
        case CALL_SCREN: display.callScreen(); mode = MAIN_SCREEN; break;
        default: break;
    }
}

void DisplayMenu::okButtonClick()
{
    peviousMode = mode;
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

    if (mode == SET_GAME_TIME_SCREEN) {
        gameTime+=SET_GAME_TIME_STEP;

        if (gameTime > MAX_GAME_TIME) {
            gameTime = SET_GAME_TIME_STEP;
        }
    }
    
}

void DisplayMenu::downButtonClick()
{
    pointer++;
    if (pointer > maxPointerByMode[mode]) {
       pointer = 0;
    }

    if (mode == SET_GAME_TIME_SCREEN) {
        gameTime-=SET_GAME_TIME_STEP;

        if (gameTime < 30) {
            gameTime = 240;
        }
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
        case DROID_SETTINGS: 
            currentDroid = pointer + 1;
            currentDroidId = pointer;
            
            break;
        default: break;
    }

    switch (peviousMode)
    {
        case DROID_SETTINGS: 
            droidSettingActions();
            
            break;
        case SETTINGS: 
            settingActions();
        case SET_GAME_TIME_SCREEN: 
            transmitter->setCode(CONTROL_CODE_SET_GAME_TIME);
            transmitter->setGameTime(gameTime);
            
            break;
        default: break;
    }
}

void DisplayMenu::droidSettingActions()
{
    switch (pointer)
    {
        case DROID_SETTING_CODE_CAUGHT: 
            transmitter->setCode(CONTROL_CODE_CAUGHT, currentDroidId);
            
            break;
        case DROID_SETTING_CODE_RETURN_TO_GAME: 
            transmitter->setCode(CONTROL_CODE_RETURN_TO_GAME, currentDroidId);
            
            break;
        case DROID_SETTING_CODE_CALL_SEPARATELY: 
            transmitter->setCode(CONTROL_CODE_CALL_SEPARATALY, currentDroidId);
            
            break;
        default: break;
    }
}

void DisplayMenu::settingActions()
{
    switch (pointer)
    {
        case SETTING_CODE_FINISH_THE_GAME: 
            transmitter->setCode(CONTROL_CODE_FINISH_THE_GAME);
            
            break;
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