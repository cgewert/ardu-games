#ifndef TVGAME_BASE_CONTROLLER
#define TVGAME_BASE_CONTROLLER

#include <Arduino.h>

#define BUTTON_NONE 0;
#define BUTTON_UP 2
#define BUTTON_DOWN 4
#define BUTTON_LEFT 8
#define BUTTON_RIGHT 16
#define BUTTON_START 32
#define BUTTON_A 64
#define BUTTON_B 128
#define BUTTON_C 256
#define BUTTON_X 512
#define BUTTON_Y 1024
#define BUTTON_Z 2048
#define BUTTON_HOME 4096

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
