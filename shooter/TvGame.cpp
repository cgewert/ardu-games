#include "TvGame.h"

TvGame::TvGame() {
    // TODO Not implemented yet
}

void TvGame::begin() {
    randomSeed(analogRead(0));
    TV.begin(NTSC, width, height);
    setFont(font6x8);
    frameCounterTime = millis();
    currentFps = fps;
}

void TvGame::setFps(uint8_t fps) {
    this->fps = fps;
}

bool TvGame::nextFrame() {
    currentMillis = millis();
    diffMillis = currentMillis - lastFrameMillis;

    if (diffMillis >= 1000 / fps) {
        overtime = diffMillis - (1000 / fps);
        lastFrameMillis = currentMillis - overtime;
        frameCount++;

        if (currentMillis - frameCounterTime >= 1000) {
            currentFps = frameCount;
            frameCount = 0;
            frameCounterTime = currentMillis;
        }
        return true;
    }
    return false;
}

void TvGame::clearScreen() {
    TV.clear_screen();
}

void TvGame::delay(unsigned int ms) {
    TV.delay(ms);
}

void TvGame::setFont(const unsigned char* f) {
    fontWidth = (int)f[0];
    fontHeight = (int)f[1];
    TV.select_font(f);
}

void TvGame::drawText(const char str[]) {
    TV.print(str);
}

void TvGame::drawCenteredText(uint8_t y, const char str[]) {
    int x = (width / 2) - ((strlen(str) * (int)fontWidth) / 2);
    TV.set_cursor(x, y);
    TV.print(str);
}

void TvGame::setCursor(uint8_t x, uint8_t y) {
    TV.set_cursor(x, y);
}

void TvGame::fillScreen(uint8_t color) {
    TV.fill(color);
}

void TvGame::shiftScreen(uint8_t distance, uint8_t direction) {
    TV.shift(distance, direction);
}

void TvGame::drawPixel(uint8_t x, uint8_t y, uint8_t color) {
    TV.set_pixel(x, y, color);
}

void TvGame::drawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color = WHITE) {
    TV.draw_rect(x, y, width - 1, height - 1, color);
}

void TvGame::fillRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color = WHITE, uint8_t fillColor = WHITE) {
    TV.draw_rect(x, y, width - 1, height - 1, color, fillColor);
}
