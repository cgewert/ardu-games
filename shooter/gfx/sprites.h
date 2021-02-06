#include <avr/pgmspace.h>
#ifndef SPRITES_GFX_H
#define SPRITES_GFX_H

const unsigned char blink1[] PROGMEM = {
    5, 5,
    0x00, // ◻◻◻◻◻
    0x20, // ◻◻◼◻◻
    0x70, // ◻◼◼◼◻
    0x20, // ◻◻◼◻◻
    0x00  // ◻◻◻◻◻
};

const unsigned char blink2[] PROGMEM = {
    7, 7,
    0x00, // ◻◻◻◻◻◻◻
    0x10, // ◻◻◻◼◻◻◻
    0x38, // ◻◻◼◼◼◻◻
    0x7C, // ◻◼◼◼◼◼◻
    0x38, // ◻◻◼◼◼◻◻
    0x10, // ◻◻◻◼◻◻◻
    0x00  // ◻◻◻◻◻◻◻
};

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
    0x3C, // ◻◻◼◼◼◼◻◻
    0x42, // ◻◼◻◻◻◻◼◻
    0x59, // ◻◼◻◼◼◻◻◼
    0x41, // ◻◼◻◻◻◻◻◼
    0x71, // ◻◼◼◼◻◻◻◼
    0x81, // ◼◻◻◻◻◻◻◼
    0xAA, // ◼◻◼◻◼◻◼◻
    0x7C  // ◻◼◼◼◼◼◻◻
};

const unsigned char gfxEnemy01b[] PROGMEM = {
    8, 8,
    0x1C, // ◻◻◻◼◼◼◻◻
    0x22, // ◻◻◼◻◻◻◼◻
    0x59, // ◻◼◻◼◼◻◻◼
    0x41, // ◻◼◻◻◻◻◻◼
    0x3D, // ◻◻◼◼◼◼◻◼
    0x41, // ◻◼◻◻◻◻◻◼
    0xAA, // ◼◻◼◻◼◻◼◻
    0x7C  // ◻◼◼◼◼◼◻◻
};

const unsigned char gfxEnemy02a[] PROGMEM = {
    8, 8,
    0x24, // ◻◻◼◻◻◼◻◻
    0x5A, // ◻◼◻◼◼◻◼◻
    0x81, // ◼◻◻◻◻◻◻◼
    0x99, // ◼◻◻◼◼◻◻◼
    0xE7, // ◼◼◼◻◻◼◼◼
    0x81, // ◼◻◻◻◻◻◻◼
    0x5A, // ◻◼◻◼◼◻◼◻
    0x3C  // ◻◻◼◼◼◼◻◻
};

const unsigned char gfxEnemy02b[] PROGMEM = {
    8, 8,
    0x24, // ◻◻◼◻◻◼◻◻
    0x5A, // ◻◼◻◼◼◻◼◻
    0xA5, // ◼◻◼◻◻◼◻◼
    0x81, // ◼◻◻◻◻◻◻◼
    0x99, // ◼◻◻◼◼◻◻◼
    0xE7, // ◼◼◼◻◻◼◼◼
    0x5A, // ◻◼◻◼◼◻◼◻
    0x3C  // ◻◻◼◼◼◼◻◻
};

const unsigned char gfxEnemy03a[] PROGMEM = {
    8, 8,
    0x54, // ◻◼◻◼◻◼◻◻
    0xAA, // ◼◻◼◻◼◻◼◻
    0x81, // ◼◻◻◻◻◻◻◼
    0xF9, // ◼◼◼◼◼◻◻◼
    0xF9, // ◼◼◼◼◼◻◻◼
    0x81, // ◼◻◻◻◻◻◻◼
    0xAA, // ◼◻◼◻◼◻◼◻
    0x54  // ◻◼◻◼◻◼◻◻
};

const unsigned char gfxEnemy03b[] PROGMEM = {
    8, 8,
    0x2A, // ◻◻◼◻◼◻◼◻
    0xD5, // ◼◼◻◼◻◼◻◼
    0x81, // ◼◻◻◻◻◻◻◼
    0xF9, // ◼◼◼◼◼◻◻◼
    0xF9, // ◼◼◼◼◼◻◻◼
    0x81, // ◼◻◻◻◻◻◻◼
    0xD5, // ◼◼◻◼◻◼◻◼
    0x2A  // ◻◻◼◻◼◻◼◻
};

const unsigned char gfxEnemy04a[] PROGMEM = {
    6, 6,
    0xFC, // ######..
    0xE8, // ###.#...
    0xA8, // #.#.#...
    0x84, // #....#..
    0x20, // ..#.....
    0x10  // ...#....
};


const unsigned char gfxEnemy04b[] PROGMEM = {
    6, 6,
    0xFC, // ######..
    0xBC, // #.####..
    0xA8, // #.#.#...
    0x84, // #....#..
    0x08, // ....#...
    0x10  // ...#....
};

const unsigned char gfxEnemy05a[] PROGMEM = {
    6, 6,
    0x10, // ...#....
    0x08, // ....#...
    0x84, // #....#..
    0xA8, // #.#.#...
    0xBC, // #.####..
    0xFC  // ######..
};

const unsigned char gfxEnemy05b[] PROGMEM = {
    6, 6,
    0x20, // ..#.....
    0x10, // ...#....
    0x84, // #....#..
    0x54, // .#.#.#..
    0x5C, // .#.###..
    0xFC  // ######..
};



#endif
