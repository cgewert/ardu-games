#ifndef TVGAME_DIGITAL_BUTTONS_CONTROLLER
#define TVGAME_DIGITAL_BUTTONS_CONTROLLER

#include "BaseController.h"

// Geht nicht: A7, A6, D13
// Geht: A5, A4, A3, A2, A1, A0, D2
#define PIN_CONTROLLER_UP A5
#define PIN_CONTROLLER_DOWN A4
#define PIN_CONTROLLER_LEFT A3
#define PIN_CONTROLLER_RIGHT A2
#define PIN_CONTROLLER_MIDDLE A1
#define PIN_CONTROLLER_SET A0
#define PIN_CONTROLLER_RESET 2

/**
 * @brief A simple interface for a controller consisting of a set of digital switches / buttons
 * 
 */
class DigitalButtonsController : public BaseController {
public:
    DigitalButtonsController();
    void begin() override;
    word readControllerState() override;
};

#endif
