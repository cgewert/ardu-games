#include "SegaDbus9Controller.h"

SegaDbus9::SegaDbus9() {
    // ...
}

void SegaDbus9::begin() {
    // TODO implementieren
}

word SegaDbus9::readControllerState() {
    return segaController.getState();
}
