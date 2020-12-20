//#include "SegaDbus9.h"
#include "TvGame.h"
#include "DigitialButtonsController.h"

byte gamestate = 0;
TvGame game;
//SegaDbus9 controller;
DigitalButtonController controller;
int8_t posX = 0;
int8_t posY = 0;
int8_t sizeX = 4;
int8_t sizeY = 4;
bool success = false;

void setup() {
    game = TvGame();
    game.begin();
    //controller = SegaDbus9();
    controller = DigitalButtonController();
    controller.begin();
    posX = game.width /2;
    posY = game.height /2;
}

void loop() {
    if (!game.nextFrame()) return;
    controller.updateControllerState();
    game.clearScreen();

    if (controller.pressed(BUTTON_UP)) {
        if (posY > 0) posY--;
    } else if (controller.pressed(BUTTON_DOWN)) {
        if (posY +sizeY < game.height) posY++;
    }
    if (controller.pressed(BUTTON_LEFT)) {
        if (posX > 0) posX--;
    } else if (controller.pressed(BUTTON_RIGHT)) {
        if (posX + sizeX < game.width) posX++;
    }

    game.fillRect(posX, posY, sizeX, sizeY, WHITE);
    game.drawCenteredText(0, String(game.currentFps).c_str());
    game.drawCenteredText(10, String(controller.currentState).c_str());
}

