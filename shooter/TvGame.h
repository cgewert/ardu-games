#include <Arduino.h>
#include <TVout.h>
#include <fontALL.h>
#include <SPI.h>

#ifndef _TVGAME_H
#define _TVGAME_H

//#define TVGAME_PIN_INPUT A7

#define BUTTON_NONE;

//=============================================
//========== Rect (rectangle) object ==========
//=============================================

/** 
 * @brief A rectangle object for collision functions.
 * 
 * The X and Y coordinates specify the top left corner of a rectangle with the
 * given width and height.
 */
struct Rect {
    float x;      /**< The X coordinate of the top left corner */
    float y;      /**< The Y coordinate of the top left corner */
    uint8_t width;  /**< The width of the rectangle */
    uint8_t height; /**< The height of the rectangle */

    /**
     * @brief The default constructor
     */
    Rect() = default;

    /**
     * @brief The fully initializing constructor

     * @param x The X coordinate of the top left corner. Copied to variable `x`.
     * @param y The Y coordinate of the top left corner. Copied to variable `y`.
     * @param width The width of the rectangle. Copied to variable `width`.
     * @param height The height of the rectangle. Copied to variable `height`.
     */
    constexpr Rect(float x, float y, uint8_t width, uint8_t height)
        : x(x), y(y), width(width), height(height)   {  }
};

/**
 * @brief An object to define a single point for collision functions.
 * 
 * The location of the point is given by X and Y coordinates.
 */
struct Point {
    float x; /**< The X coordinate of the point */
    float y; /**< The Y coordinate of the point */

    /**
     * @brief The default constructor
     */
    Point() = default;

    /**
     * @brief The fully initializing constructor
     * 
     * @param x The X coordinate of the point. Copied to variable `x`.
     * @param y The Y coordinate of the point. Copied to variable `y`.
     */
    constexpr Point(float x, float y)
        : x(x), y(y)   {  }
};

class TvGame {
public:
    TvGame();
    TvGame(uint8_t width, uint8_t height);

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

    /**
     * @brief Returns true every x frames
     * 
     * @param frames The desired number of elapsed frames
     * @return true if the specified number of frames has elapsed
     * @return false if the specified number of frames has not elapsed
     */
    bool everyXFrames(uint8_t frames);

    /**
     * @brief Delays the execution of the game for the specified number of milli seconds
     * 
     * @param ms Time to delay
     */
    void delay(unsigned int ms);

    // Audio

    /**
     * @brief Plays a tone
     * 
     * @param frequency Frequency
     * @param duration_ms Length of the tone output
     */
    void tone(unsigned int frequency, unsigned long duration_ms);

    /**
     * @brief Stops the playback of audio, if any
     */
    void noTone();

    // Graphics
    void clearScreen();
    void setFont(const unsigned char* f);
    void drawText(const char str[]);
    void drawCenteredText(uint8_t y, const char str[]);
    void setCursor(uint8_t x, uint8_t y);
    void fillScreen(uint8_t color);
    void shiftScreen(uint8_t distance, uint8_t direction);
    void drawPixel(int8_t x, int8_t y, uint8_t color = WHITE);
    void drawRect(int8_t x, int8_t y, uint8_t width, uint8_t height, uint8_t color = WHITE);
    void fillRect(int8_t x, int8_t y, uint8_t width, uint8_t height, uint8_t color = WHITE, uint8_t fillColor = WHITE);
    void drawBitmap(int8_t x, int8_t y, const uint8_t* bitmap, uint8_t with = 0, uint8_t height = 0);
    void drawCircle(int8_t x0, int8_t y0, uint8_t r, uint8_t color = WHITE);
    void fillCircle(int8_t x0, int8_t y0, uint8_t r, uint8_t color = WHITE, uint8_t fillColor = WHITE);

    // Collision detection
    static bool collide(Point point, Rect rect);
    static bool collide(Rect rect1, Rect rect2);
    
public:
    TVout TV;
    uint8_t width = 128;
    uint8_t height = 96;
    uint8_t frameCount;
    float currentFps;

private:
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
