#include <avr/pgmspace.h>
#ifndef SPRITES_GFX_H
#define SPRITES_GFX_H

const unsigned char gfxExplosion1[] PROGMEM = {
    8,8,
    B00000000,
    B00000100,
    B00101110,
    B00000010,
    B01100000,
    B00000110,
    B00100000,
    B00100000
};

const unsigned char gfxExplosion2[] PROGMEM = {
    8, 8,
    B00010010,
    B00100010,
    B01000000,
    B00000000,
    B01010010,
    B01001100,
    B10011000,
    B00000000
};

const unsigned char gfxPlayer[] PROGMEM = {
    8, 8,
    B00000000,
    B01111000,
    B11100100,
    B01110111,
    B11100110,
    B10111100,
    B01110000,
    B11000000
};

const unsigned char gfxPlayerB[] PROGMEM = {
    8, 8,
    B01000000,
    B11111000,
    B01100100,
    B11110111,
    B10100110,
    B01111100,
    B11110000,
    B00000000
};

const unsigned char gfxPlayerDown[] PROGMEM = {
    8, 8,
    B00000000,
    B00111000,
    B01111000,
    B11110100,
    B01110111,
    B11100110,
    B10111100,
    B01110000
};

const unsigned char gfxPlayerUp[] PROGMEM = {
    8, 8,
    B01111000,
    B11110100,
    B01110111,
    B11100110,
    B10111100,
    B01110100,
    B11010000,
    B01000000
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
