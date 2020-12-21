#ifndef TVGAME_ANALOG_STICK_CONTROLLER
#define TVGAME_ANALOG_STICK_CONTROLLER

#include "BaseController.h"

#define PIN_STICK_SWITCH A0
#define PIN_STICK_X A1
#define PIN_STICK_Y A2

/**
 * @brief Implements an interface for analog controller sticks (PS2)
 * 
 */
class AnalogStickController : public BaseController {

// Public methods
public:
    AnalogStickController();
    void begin() override;
    word readControllerState() override;
    float getRelativeX() override;
    float getRelativeY() override;

// Private methods
private:
    int getPositionX();
    int getPositionY();

// Private properties
private:
    int currentX = 0;
    int currentY = 0;
    bool currentSwitch = false;
};

#endif
