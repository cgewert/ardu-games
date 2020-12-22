#ifndef TVGAME_SEGA_CONTROLLER
#define TVGAME_SEGA_CONTROLLER

#include <Arduino.h>
#include <SegaController.h>
#include "BaseController.h"

//#define PIN_DB9_1 12
//#define PIN_DB9_2 10
//#define PIN_DB9_3 8
//#define PIN_DB9_4 6
// DB9-PIN 5 is power 5V
//#define PIN_DB9_6 5
//#define PIN_DB9_7 4
// DB9-PIN 8 is ground
//#define PIN_DB9_9 3

#define PIN_DB9_1 A5
#define PIN_DB9_2 A4
#define PIN_DB9_3 A3
#define PIN_DB9_4 A2
// DB9-PIN 5 is power 5V
#define PIN_DB9_6 A1
#define PIN_DB9_7 3
// DB9-PIN 8 is ground
#define PIN_DB9_9 2

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
