#include "DigitialButtonsController.h"

DigitalButtonController::DigitalButtonController() {
    // ...
}

void DigitalButtonController::begin() {
    pinMode(PIN_CONTROLLER_UP, INPUT_PULLUP);
    pinMode(PIN_CONTROLLER_DOWN, INPUT_PULLUP);
    pinMode(PIN_CONTROLLER_LEFT, INPUT_PULLUP);
    pinMode(PIN_CONTROLLER_RIGHT, INPUT_PULLUP);
    pinMode(PIN_CONTROLLER_MIDDLE, INPUT_PULLUP);
    pinMode(PIN_CONTROLLER_SET, INPUT_PULLUP);
    pinMode(PIN_CONTROLLER_RESET, INPUT_PULLUP);
}

word DigitalButtonController::readControllerState() {
    word state = 0;
    state |= (digitalRead(PIN_CONTROLLER_UP) == LOW)? BUTTON_UP : 0;
    state |= (digitalRead(PIN_CONTROLLER_DOWN) == LOW) ? BUTTON_DOWN : 0;
    state |= (digitalRead(PIN_CONTROLLER_LEFT) == LOW) ? BUTTON_LEFT : 0;
    state |= (digitalRead(PIN_CONTROLLER_RIGHT) == LOW) ? BUTTON_RIGHT : 0;
    state |= (digitalRead(PIN_CONTROLLER_MIDDLE) == LOW) ? BUTTON_A : 0;
    state |= (digitalRead(PIN_CONTROLLER_SET) == LOW) ? BUTTON_START : 0;
    state |= (digitalRead(PIN_CONTROLLER_RESET) == LOW) ? BUTTON_HOME : 0;
    return state;
}
