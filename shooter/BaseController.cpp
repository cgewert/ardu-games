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
