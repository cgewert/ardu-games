#ifndef TVGAME_BASE_CONTROLLER
#define TVGAME_BASE_CONTROLLER

#include <Arduino.h>

class BaseController {
public:
    BaseController();
    void updateControllerState();
    bool pressed(word button);

    // Virtual methods which must be implemented by concrete classes
    virtual void begin();
    virtual word readControllerState();

public:
    word lastState = 0;
    word currentState = 0;
};

#endif
