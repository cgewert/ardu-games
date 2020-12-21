#include "AnalogButtonsController.h"

AnalogButtonsController::AnalogButtonsController() {
    // ...
}

void AnalogButtonsController::begin() {
    pinMode(PIN_CONTROLLER_INPUT, INPUT);
}

word AnalogButtonsController::readControllerState() {
    word state = BUTTON_NONE;
    int input = analogRead(PIN_CONTROLLER_INPUT);

    state |= (input < 16)? BUTTON_LEFT : 0;
    state |= (input >= 16 && input < 48)? BUTTON_UP : 0;
    state |= (input >= 80 && input < 112)? BUTTON_DOWN : 0;
    state |= (input >= 144 && input < 176)? BUTTON_RIGHT : 0;
    state |= (input >= 336 && input < 368)? BUTTON_A : 0;

    return state;
}