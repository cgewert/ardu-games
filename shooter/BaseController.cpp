#include "BaseController.h"

BaseController::BaseController() {
}

void BaseController::begin() {
}

void BaseController::updateControllerState() {
    lastState = currentState;
    currentState = readControllerState();
}

bool BaseController::pressed(word buttons) {
    return (currentState & buttons) == buttons;
}

bool BaseController::notPressed(word buttons) {
    return (currentState & buttons) == 0;
}

bool BaseController::anyPressed(word buttons = 0) {
    return (currentState & buttons) != 0;
}

bool BaseController::justPressed(word button) {
    return (!(lastState & button) && (currentState & button));
}

bool BaseController::justReleased(word button) {
    return ((lastState & button) && !(currentState & button));
}

float BaseController::getRelativeX() {
    if (currentState & BUTTON_LEFT) return -1;
    if (currentState & BUTTON_RIGHT) return 1;
    return 0;
}

float BaseController::getRelativeY() {
    if (currentState & BUTTON_DOWN) return 1;
    if (currentState & BUTTON_UP) return -1;
    return 0;
}
