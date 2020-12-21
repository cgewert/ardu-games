#ifndef TVGAME_ANALOG_BUTTONS_CONTROLLER
#define TVGAME_ANALOG_BUTTONS_CONTROLLER

#include "BaseController.h"

#define PIN_CONTROLLER_INPUT A5

class AnalogButtonsController : public BaseController {
public:
    AnalogButtonsController();
    void begin() override;
    word readControllerState() override;
};

#endif
