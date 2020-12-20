#include <Arduino.h>
#include <TVout.h>
#include <fontALL.h>
#include <SPI.h>
#include <NintendoExtensionCtrl.h>

#ifndef _TVGAME_H
#define _TVGAME_H

//#define TVGAME_PIN_INPUT A7

#define BUTTON_NONE;

class TvGame {
public:
    TvGame();
    void begin();

    /**
     * @brief Sets the refresh rate in frames per second
     *
     * @param fps New (preferred) number of frames per second
     */
    void setFps(uint8_t fps);

    /**
     * @brief Checks if the next frame should be calculated and drawn
     *
     * @return true If the next frame should be rendered
     * @return false If the game loop should wait for the next frame
     */
    bool nextFrame();

    // Wrapper for tvout library
    void clearScreen();
    void delay(unsigned int ms);
    void setFont(const unsigned char* f);
    void tone(unsigned int frequency, unsigned long duration_ms);
    void noTone();
    void drawText(const char str[]);
    void drawCenteredText(uint8_t y, const char str[]);
    void setCursor(uint8_t x, uint8_t y);

    void fillScreen(uint8_t color);
    void shiftScreen(uint8_t distance, uint8_t direction);
    void drawPixel(uint8_t x, uint8_t y, uint8_t color = WHITE);
    void drawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color = WHITE);
    void fillRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color = WHITE, uint8_t fillColor = WHITE);

public:
    uint8_t width = 128;
    uint8_t height = 96;
    uint8_t frameCount;
    float currentFps;

private:
    TVout TV;    
    uint8_t fontWidth = 6;
    uint8_t fontHeight = 8;
    uint8_t fps = 20;

    unsigned long lastFrameMillis = 0;
    unsigned long currentMillis = 0;
    unsigned long diffMillis = 0;
    unsigned long overtime = 0;
    unsigned long frameCounterTime = 0;
};

#endif
