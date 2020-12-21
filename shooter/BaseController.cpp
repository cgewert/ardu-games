#include "BaseController.h"

BaseController::BaseController() {
}

void BaseController::begin() {
}

void BaseController::updateControllerState() {
    lastState = currentState;
    currentState = readControllerState();
}

bool BaseController::pressed(word button) {
    return (currentState & button) == button; 
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
