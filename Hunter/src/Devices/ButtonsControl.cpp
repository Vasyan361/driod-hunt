#include "ButtonsControl.h"

void ButtonsControl::init(DisplayMenu* displayMenu, Transmitter* transmitter)

{
    ButtonsControl::displayMenu = displayMenu;
    ButtonsControl::transmitter = transmitter;

    buttons[BACK_BUTTON].attachClick([](void *scope) { ((ButtonsControl *) scope)->backButtonClick();}, this);
    buttons[UP_BUTTON].attachClick([](void *scope) { ((ButtonsControl *) scope)->upButtonClick();}, this);
    buttons[DOWN_BUTTON].attachClick([](void *scope) { ((ButtonsControl *) scope)->downButtonClick();}, this);
    buttons[OK_BUTTON].attachClick([](void *scope) { ((ButtonsControl *) scope)->okButtonClick();}, this);
    buttons[CALL_BUTTON].attachClick([](void *scope) { ((ButtonsControl *) scope)->callButtonClick();}, this);
}

void ButtonsControl::readInput()
{
    for (int i = 0; i < 5; i++) {
        buttons[i].tick();
    }
}

void ButtonsControl::backButtonClick()
{
    displayMenu->backButtonClick();
}

void ButtonsControl::upButtonClick()
{
    displayMenu->upButtonClick();
}

void ButtonsControl::downButtonClick()
{
    displayMenu->downButtonClick();
}

void ButtonsControl::okButtonClick()
{
    displayMenu->okButtonClick();
}

void ButtonsControl::callButtonClick()
{
    transmitter->setCode(1);
}
