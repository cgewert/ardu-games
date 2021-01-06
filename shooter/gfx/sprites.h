#include <avr/pgmspace.h>
#ifndef SPRITES_GFX_H
#define SPRITES_GFX_H

const unsigned char gfxExplosion1[] PROGMEM = {
    8, 8,
    0x00, // ◻◻◻◻◻◻◻◻
    0x04, // ◻◻◻◻◻◼◻◻
    0x2E, // ◻◻◼◻◼◼◼◻
    0x02, // ◻◻◻◻◻◻◼◻
    0x60, // ◻◼◼◻◻◻◻◻
    0x06, // ◻◻◻◻◻◼◼◻
    0x20, // ◻◻◼◻◻◻◻◻
    0x20  // ◻◻◼◻◻◻◻◻
};

const unsigned char gfxExplosion2[] PROGMEM = {
    8, 8,
    0x12, // ◻◻◻◼◻◻◼◻
    0x22, // ◻◻◼◻◻◻◼◻
    0x40, // ◻◼◻◻◻◻◻◻
    0x00, // ◻◻◻◻◻◻◻◻
    0x52, // ◻◼◻◼◻◻◼◻
    0x4C, // ◻◼◻◻◼◼◻◻
    0x98, // ◼◻◻◼◼◻◻◻
    0x00  // ◻◻◻◻◻◻◻◻
};

const unsigned char gfxPlayer[] PROGMEM = {
    8, 8,
    0x00, // ◻◻◻◻◻◻◻◻
    0x78, // ◻◼◼◼◼◻◻◻
    0xE4, // ◼◼◼◻◻◼◻◻
    0x77, // ◻◼◼◼◻◼◼◼
    0xE6, // ◼◼◼◻◻◼◼◻
    0xBC, // ◼◻◼◼◼◼◻◻
    0x70, // ◻◼◼◼◻◻◻◻
    0xC0  // ◼◼◻◻◻◻◻◻
};

const unsigned char gfxPlayerB[] PROGMEM = {
    8, 8,
    0x40, // ◻◼◻◻◻◻◻◻
    0xF8, // ◼◼◼◼◼◻◻◻
    0x64, // ◻◼◼◻◻◼◻◻
    0xF7, // ◼◼◼◼◻◼◼◼
    0xA6, // ◼◻◼◻◻◼◼◻
    0x7C, // ◻◼◼◼◼◼◻◻
    0xF0, // ◼◼◼◼◻◻◻◻
    0x00  // ◻◻◻◻◻◻◻◻
};

const unsigned char gfxPlayerDown[] PROGMEM = {
    8, 8,
    0x00, // ◻◻◻◻◻◻◻◻
    0x38, // ◻◻◼◼◼◻◻◻
    0x78, // ◻◼◼◼◼◻◻◻
    0xF4, // ◼◼◼◼◻◼◻◻
    0x77, // ◻◼◼◼◻◼◼◼
    0xE6, // ◼◼◼◻◻◼◼◻
    0xBC, // ◼◻◼◼◼◼◻◻
    0x70  // ◻◼◼◼◻◻◻◻
};

const unsigned char gfxPlayerUp[] PROGMEM = {
    8, 8,
    0x78, // ◻◼◼◼◼◻◻◻
    0xF4, // ◼◼◼◼◻◼◻◻
    0x77, // ◻◼◼◼◻◼◼◼
    0xE6, // ◼◼◼◻◻◼◼◻
    0xBC, // ◼◻◼◼◼◼◻◻
    0x74, // ◻◼◼◼◻◼◻◻
    0xD0, // ◼◼◻◼◻◻◻◻
    0x40  // ◻◼◻◻◻◻◻◻
};

const unsigned char gfxEnemy01a[] PROGMEM = {
    8, 8,
    B00111100,
    B01000010,
    B01011001,
    B01000001,
    B01110001,
    B10000001,
    B10101010,
    B01111100
};

const unsigned char gfxEnemy01b[] PROGMEM = {
    8, 8,
    B00011100,
    B00100010,
    B01011001,
    B01000001,
    B00111101,
    B01000001,
    B10101010,
    B01111100
};

const unsigned char gfxEnemy02a[] PROGMEM = {
    8, 8,
    B00100100,
    B01011010,
    B10000001,
    B10011001,
    B11100111,
    B10000001,
    B01011010,
    B00111100
};

const unsigned char gfxEnemy02b[] PROGMEM = {
    8, 8,
    B00100100,
    B01011010,
    B10100101,
    B10000001,
    B10011001,
    B11100111,
    B01011010,
    B00111100
};

const unsigned char gfxEnemy03a[] PROGMEM = {
    8, 8,
    B01010100,
    B10101010,
    B10000001,
    B11111001,
    B11111001,
    B10000001,
    B10101010,
    B01010100
};

const unsigned char gfxEnemy03b[] PROGMEM = {
    8, 8,
    B00101010,
    B11010101,
    B10000001,
    B11111001,
    B11111001,
    B10000001,
    B11010101,
    B00101010
};

#endif
