#include "TvGame.h"

TvGame::TvGame(uint8_t width, uint8_t height) {
    this->width = width;
    this->height = height;
}

TvGame::TvGame() : TvGame(128, 96) {
};

#pragma region Basic control

void TvGame::begin() {
    randomSeed(analogRead(0));
    TV.begin(NTSC, width, height);
    setFont(font6x8);
    frameCounterTime = millis();
    lastFrameMillis = frameCounterTime;
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

bool TvGame::everyXFrames(uint8_t frames) {
    return frameCount % frames == 0;
}

void TvGame::delay(unsigned int ms) {
    TV.delay(ms);
}

#pragma endregion


#pragma region Audio

void TvGame::tone(unsigned int frequency, unsigned long duration_ms) {
    TV.tone(frequency, duration_ms);
}

void TvGame::noTone() {
    TV.noTone();
}

#pragma endregion


#pragma region Graphics

void TvGame::clearScreen() {
    TV.clear_screen();
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

void TvGame::drawPixel(int8_t x, int8_t y, uint8_t color = WHITE) {
    TV.set_pixel(x, y, color);
}

void TvGame::drawRect(int8_t x, int8_t y, uint8_t width, uint8_t height, uint8_t color = WHITE) {
    TV.draw_rect(x, y, width - 1, height - 1, color);
}

void TvGame::fillRect(int8_t x, int8_t y, uint8_t width, uint8_t height, uint8_t color = WHITE, uint8_t fillColor = WHITE) {
    TV.draw_rect(x, y, width - 1, height - 1, color, fillColor);
}

void TvGame::drawCircle(int8_t x0, int8_t y0, uint8_t r, uint8_t color = WHITE) {
    TV.draw_circle(x0, y0, r, color);
}

void TvGame::fillCircle(int8_t x0, int8_t y0, uint8_t r, uint8_t color = WHITE, uint8_t fillColor = WHITE) {
    TV.draw_circle(x0, y0, r, color, fillColor);
}

void TvGame::drawBitmap(int8_t x, int8_t y, const uint8_t* bitmap, uint8_t width = 0, uint8_t height = 0) {
    TV.bitmap(x, y, bitmap, 0, width, height);
}

#pragma endregion


#pragma region Collision detection

bool TvGame::collide(Point point, Rect rect) {
    return ((point.x >= rect.x) && (point.x < rect.x + rect.width) &&
        (point.y >= rect.y) && (point.y < rect.y + rect.height));
}

bool TvGame::collide(Rect rect1, Rect rect2) {
    return !(rect2.x >= rect1.x + rect1.width ||
        rect2.x + rect2.width <= rect1.x ||
        rect2.y >= rect1.y + rect1.height ||
        rect2.y + rect2.height <= rect1.y);
}

#pragma endregion
