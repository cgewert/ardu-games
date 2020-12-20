#ifndef TVGAME_SEGA_CONTROLLER
#define TVGAME_SEGA_CONTROLLER

#include <Arduino.h>
#include <SegaController.h>
#include "BaseController.h"

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

#define PIN_DB9_1 12
#define PIN_DB9_2 10
#define PIN_DB9_3 8
#define PIN_DB9_4 6
// DB9-PIN 5 is power 5V
#define PIN_DB9_6 5
#define PIN_DB9_7 4
// DB9-PIN 8 is ground
#define PIN_DB9_9 3

class SegaDbus9 : public BaseController {
public:
    SegaDbus9();
    void begin() override;
    word readControllerState() override;

private:
    //SegaController segaController = SegaController(4, 12, 10, 8, 6, 5, 3);
    SegaController segaController = SegaController(PIN_DB9_7, PIN_DB9_1, PIN_DB9_2, PIN_DB9_3, PIN_DB9_4, PIN_DB9_6, PIN_DB9_9);
};

#endif
