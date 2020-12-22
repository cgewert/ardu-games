#include "AnalogStickController.h"

AnalogStickController::AnalogStickController() {
    // ...
}

void AnalogStickController::begin() {
    pinMode(PIN_STICK_SWITCH, INPUT_PULLUP);
}

word AnalogStickController::readControllerState() {
    currentX = analogRead(PIN_STICK_X);
    currentY = analogRead(PIN_STICK_Y);
    currentSwitch = digitalRead(PIN_STICK_SWITCH);

    word state = BUTTON_NONE;
    state |= (currentSwitch == LOW)? BUTTON_A : 0;
    state |= (getRelativeX() >= 0.2)? BUTTON_RIGHT : 0;
    state |= (getRelativeX() <= -0.2)? BUTTON_LEFT : 0;
    state |= (getRelativeY() >= 0.2)? BUTTON_DOWN : 0;
    state |= (getRelativeY() <= -0.2)? BUTTON_UP : 0;

    return state;
}

int AnalogStickController::getPositionX() {
    return currentX;
}

int AnalogStickController::getPositionY() {
    return currentY;
}

float AnalogStickController::getRelativeX() {
    return (512 - currentX) /512.0;
}

float AnalogStickController::getRelativeY() {
    return -(512 - currentY) /512.0;
}