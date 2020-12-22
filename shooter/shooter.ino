#include "TvGame.h"
#include "AnalogStickController.h"
#include "gfx/title.h"
#include "gfx/gameOverGfx.h"
#include "gfx/gameEndGfx.h"
#include "gfx/sprites.h"
#include "levels/levels.h"

#define MAX_SHOTS 5
#define MAX_BULLETS 5
#define MAX_ENEMIES 16
#define MAX_LEVEL 2

#define STATE_INACTIVE 0
#define STATE_ACTIVE 1
#define STATE_PENDING 2

#define TYPE_FRIENDLY 0
#define TYPE_ENEMY 1
#define LEVEL_ENTRY_LENGTH 3

#define GAMESTATE_TITLE 0
#define GAMESTATE_GAME 1
#define GAMESTATE_NEXT_LEVEL 2
#define GAMESTATE_GAMEOVER 3
#define GAMESTATE_END 4

struct Sprite {
    Rect bounds = Rect(0, 0, 1, 1);
    byte state = STATE_INACTIVE;
    byte type = TYPE_ENEMY;
    byte frame = 0;
    byte hitPoints = 1;
    byte ttl = 0;
    byte id = 0;
    const unsigned char* bitmap1;
    const unsigned char* bitmap2;
};

struct Bullet {
    Point position = Point(0, 0);
    Point speed = Point(0, 0);
    uint8_t state = STATE_INACTIVE;
};

byte gamestate = 0;
byte nextGamestate = 0;
TvGame game;
AnalogStickController controller;

Sprite player;
Sprite enemies[MAX_ENEMIES];
Bullet shots[MAX_SHOTS];
Bullet bullets[MAX_BULLETS];

const unsigned int* currentLevel;
unsigned long levelStartTime = 0;
unsigned long timeElapsed = 0;
unsigned long levelMaxTime = 0;

uint8_t levelCount = 0;
uint8_t levelCursor = 0;
uint8_t levelEntries = 0;
uint16_t playerScore = 0;
uint8_t playerLives = 0;

void setup() {
    game = TvGame(128, 64);
    game.begin();
    game.setFps(20);
    game.setFont(font4x6);
    controller = AnalogStickController();
    controller.begin();

    player = Sprite();
    player.type = TYPE_FRIENDLY;
    player.state = STATE_ACTIVE;
    player.bounds.x = 0;
    player.bounds.y = 0;
    player.bounds.width = 8;
    player.bounds.height = 8;
    player.bitmap1 = gfxPlayer;
    player.bitmap2 = gfxPlayerB;

    for (byte i = 0; i < MAX_ENEMIES; i++) {
        enemies[i] = Sprite();
    }
    for (byte i = 0; i < MAX_SHOTS; i++) {
        shots[i] = Bullet();
    }
    for (byte i = 0; i < MAX_BULLETS; i++) {
        bullets[i] = Bullet();
    }
}

void soundCollision() {
    game.tone(200, 100);
}

void soundEnemyShoot() {
    game.tone(50, 25);
}

void soundPlayerShoot() {
    game.tone(1500, 25);
}

void newGame() {
    player.bounds.x = 0;
    player.bounds.y = game.height /2;
    playerScore = 0;
    playerLives = 3;
    levelCount = 0;    
    nextLevel();
}

bool nextLevel() {
    for (byte i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].state = STATE_INACTIVE;
    }
    for (byte i = 0; i < MAX_SHOTS; i++) {
        shots[i].state = STATE_INACTIVE;
    }
    for (byte i = 0; i < MAX_BULLETS; i++) {
        bullets[i].state = STATE_INACTIVE;
    }
    if (levelCount < MAX_LEVEL) {
        levelCount++;
        switch (levelCount) {
            case 1: currentLevel = level1; break;
            case 2: currentLevel = level2; break;
        }
        levelEntries = (uint8_t)pgm_read_byte(currentLevel);
        levelMaxTime = (uint8_t)pgm_read_byte(currentLevel + 1);
        levelStartTime = millis();
        levelCursor = 0;
        return true;
    }
    return false;
}

byte nextFreeEnemyIndex() {
    for (byte i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].state == STATE_INACTIVE) return i;
    }
    return MAX_ENEMIES;
}

byte nextFreeShotIndex() {
    for (byte i = 0; i < MAX_SHOTS; i++) {
        if (shots[i].state == STATE_INACTIVE) return i;
    }
    return MAX_SHOTS;
}

byte nextFreeBulletIndex() {
    for (byte i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].state == STATE_INACTIVE) return i;
    }
    return MAX_BULLETS;
}

void newBullet(float startX, float startY, float speedX = -2, float speedY = 0) {
    byte idx = nextFreeBulletIndex();
    if (idx < MAX_BULLETS) {
        bullets[idx] = Bullet();
        bullets[idx].state = STATE_ACTIVE;
        bullets[idx].position.x = startX;
        bullets[idx].position.y = startY;
        bullets[idx].speed.x = speedX;
        bullets[idx].speed.y = speedY;
        soundEnemyShoot();
    }
}

void newShot() {
    byte idx = nextFreeShotIndex();
    if (idx < MAX_SHOTS) {
        shots[idx] = Bullet();
        shots[idx].state = STATE_ACTIVE;
        shots[idx].position.x = player.bounds.x +player.bounds.width;
        shots[idx].position.y = player.bounds.y +player.bounds.height /2;
        shots[idx].speed = Point(2, 0);
        soundPlayerShoot();
    }
}

void newEnemy(uint8_t enemyType = 0, float y = 0) {
    int idx = nextFreeEnemyIndex();
    if (idx < MAX_ENEMIES) {
        enemies[idx] = Sprite();
        enemies[idx].bounds = Rect(
            game.width - 9,
            y,
            8, 8
        );
        enemies[idx].frame = game.frameCount;
        enemies[idx].state = 1;
        enemies[idx].type = TYPE_ENEMY;
        enemies[idx].id = enemyType;

        switch (enemyType) {
            case 3:
                enemies[idx].hitPoints = 4;
                enemies[idx].bitmap1 = gfxEnemy03a;
                enemies[idx].bitmap2 = gfxEnemy03b;
                break;

            case 2:
                enemies[idx].hitPoints = 2;
                enemies[idx].bitmap1 = gfxEnemy02a;
                enemies[idx].bitmap2 = gfxEnemy02b;
                break;

            default:
                enemies[idx].hitPoints = 2;
                enemies[idx].bitmap1 = gfxEnemy01a;
                enemies[idx].bitmap2 = gfxEnemy01b;
                break;
        }
    }
}

void playerHit() {
    if (playerLives > 0) {
        playerLives--;
        soundCollision();
    } else {
        nextGamestate = GAMESTATE_GAMEOVER;
    }
}

void drawStatusText() {
    game.setFont(font4x6);
    game.setCursor(0, 0);
    game.TV.print("Level ");
    game.TV.print((int)levelCount);

    game.setCursor(45, 0);
    game.TV.print("Lives ");
    game.TV.print((int)playerLives);

    game.setCursor(90, 0);
    game.TV.print("Score ");
    game.TV.print(playerScore);
}

void loop() {
    if (!game.nextFrame()) return;
    controller.updateControllerState();
    byte i = 0;
    byte k = 0;
    byte idx;
    byte playerDirection = 0;

    switch (gamestate) {

        // Title screen
        case GAMESTATE_TITLE:
            game.drawBitmap(0, 0, titleGfx);
            if (controller.justPressed(BUTTON_A)) {
                newGame();
                nextGamestate = GAMESTATE_GAME;
            }
            break;

        // Main game
        case GAMESTATE_GAME:
            timeElapsed = (millis() -levelStartTime) /1000;

            // Level end is depending on time elapsed
            if (timeElapsed == levelMaxTime) {
                nextGamestate = GAMESTATE_NEXT_LEVEL;
                break;
            }

            // Player control
            if (abs(controller.getRelativeX()) > 0.05) {
                player.bounds.x += controller.getRelativeX() *2;
                if (player.bounds.x + player.bounds.width > game.width) player.bounds.x = game.width - player.bounds.width;
                if (player.bounds.x < 0) player.bounds.x = 0;
            }
            if (abs(controller.getRelativeY()) > 0.05) {
                player.bounds.y += controller.getRelativeY() * 2;
                if (player.bounds.y + player.bounds.height > game.height) player.bounds.y = game.height - player.bounds.height;
                if (player.bounds.y < 0) player.bounds.y = 0;
                if (controller.getRelativeY() > 0.05) {
                    playerDirection = 1;
                } else {
                    playerDirection = -1;
                }
            } else {
                playerDirection = 0;
            }

            // Player bullets
            for (i = 0; i < MAX_SHOTS; i++) {
                if (shots[i].state != STATE_INACTIVE) {
                    if (shots[i].position.x +1 < game.width) {
                        shots[i].position.x += shots[i].speed.x;
                        shots[i].position.y += shots[i].speed.y;
                    } else {
                        shots[i].state = STATE_INACTIVE;
                    }
                }
            }

            // Enemy bullets
            for (i = 0; i < MAX_BULLETS; i++) {
                if (bullets[i].state != STATE_INACTIVE) {
                    if (bullets[i].position.x + 1 < game.width
                        && bullets[i].position.y + 1 < game.height
                        && bullets[i].position.x > 0
                        && bullets[i].position.y > 0) {
                        bullets[i].position.x += bullets[i].speed.x;
                        bullets[i].position.y += bullets[i].speed.y;
                    } else {
                        bullets[i].state = STATE_INACTIVE;
                    }
                }
            }

            // Move enemies
            for (i = 0; i < MAX_ENEMIES; i++) {
                if (enemies[i].state != STATE_INACTIVE) {

                    // If enemy is out of screen bounds, inactivate it
                    if (enemies[i].bounds.x > 0) {
                        enemies[i].bounds.x--;
                    } else {
                        enemies[i].state = STATE_INACTIVE;
                    }

                    // Check if enemy is exploding and should be removed
                    if (enemies[i].ttl > 0 && game.frameCount == 0) {
                        enemies[i].ttl--;
                        if (enemies[i].ttl == 0) {
                            enemies[i].state = STATE_INACTIVE;
                        }
                    }
                }

                // Let some enemies shoot bullets
                if (game.frameCount == 0 && enemies[i].state != STATE_INACTIVE && enemies[i].ttl == 0) {
                    if (enemies[i].id == 3) {
                        if (random(10) == 0) {
                            float lX = (enemies[i].bounds.x -enemies[i].bounds.width /2) - (player.bounds.x -player.bounds.width /2);
                            float lY = (enemies[i].bounds.y -enemies[i].bounds.height /2) - (player.bounds.y -player.bounds.height /2);
                            float v = sqrt(lX * lX + lY * lY);

                            if (v > 1) {
                                lX = lX /v *-2;
                                lY = lY /v *-2;
                                newBullet(
                                    enemies[i].bounds.x + enemies[i].bounds.width /2,
                                    enemies[i].bounds.y + enemies[i].bounds.height /2,
                                    lX,
                                    lY
                                );
                            }
                        }
                    } else if (enemies[i].id == 2) {
                        if (random(7) == 0) {
                            newBullet(
                                enemies[i].bounds.x + enemies[i].bounds.width / 2,
                                enemies[i].bounds.y + enemies[i].bounds.height / 2
                            );
                        }
                    }
                }
            }

            // Add enemies according to level map
            if (game.frameCount == 0) {
                while (levelCursor < levelEntries && (int)pgm_read_byte_near(currentLevel + 2 + (levelCursor * LEVEL_ENTRY_LENGTH)) == timeElapsed) {
                    newEnemy(
                        (int)pgm_read_byte_near(currentLevel + 3 + (levelCursor * LEVEL_ENTRY_LENGTH)),
                        (int)pgm_read_byte_near(currentLevel + 4 + (levelCursor * LEVEL_ENTRY_LENGTH))
                    );
                    levelCursor++;
                }
            }

            // Fire button
            if (controller.justPressed(BUTTON_A)) {
                newShot();
            }

            // Collision detection
            for (i = 0; i < MAX_ENEMIES; i++) {
                // Check if enemy is shot by player
                if (enemies[i].state != STATE_INACTIVE && enemies[i].type != TYPE_FRIENDLY) {
                    for (k = 0; k < MAX_SHOTS; k++) {
                        if (shots[k].state != STATE_INACTIVE) {
                            if (game.collide(shots[k].position, enemies[i].bounds)) {
                                
                                shots[k].state = STATE_INACTIVE;
                                enemies[i].hitPoints--;

                                if (enemies[i].hitPoints == 0) {
                                    enemies[i].type = TYPE_FRIENDLY;
                                    enemies[i].ttl = 2;
                                    enemies[i].frame = game.frameCount;
                                    enemies[i].bitmap1 = gfxExplosion1;
                                    enemies[i].bitmap2 = gfxExplosion2;
                                    
                                    switch (enemies[i].id) {
                                        case 1: playerScore += 10; break;
                                        case 2: playerScore += 30; break;
                                        case 3: playerScore += 50; break;
                                    }
                                    
                                } else {
                                    soundCollision();
                                }
                            }
                        }
                    }
                }

                // Check if enemy collides with player
                if (enemies[i].state != STATE_INACTIVE && enemies[i].type != TYPE_FRIENDLY) {
                    if (game.collide(enemies[i].bounds, player.bounds)) {
                        enemies[i].state = STATE_INACTIVE;
                        playerHit();
                    }
                }
            }

            // Check if player is hit by enemy bullets
            for (i = 0; i < MAX_BULLETS; i++) {
                if (bullets[i].state != STATE_INACTIVE) {
                    if (game.collide(bullets[i].position, player.bounds)) {
                        bullets[i].state = STATE_INACTIVE;
                        playerHit();
                    }
                }
            }

            // Draw the game state
            game.clearScreen();

            // Player shots
            for (i = 0; i < MAX_SHOTS; i++) {
                if (shots[i].state != STATE_INACTIVE) {
                    game.drawPixel(shots[i].position.x, shots[i].position.y);
                }
            }

            // Enemies
            for (i = 0; i < MAX_ENEMIES; i++) {
                if (enemies[i].state != STATE_INACTIVE) {
                    game.drawBitmap(
                        enemies[i].bounds.x,
                        enemies[i].bounds.y,
                        ((enemies[i].frame + game.frameCount) % 20 < 10)? enemies[i].bitmap1 : enemies[i].bitmap2
                    );
                }
            }

            // Enemy bullets
            for (i = 0; i < MAX_BULLETS; i++) {
                if (bullets[i].state != STATE_INACTIVE) {
                    game.drawPixel(bullets[i].position.x, bullets[i].position.y);
                }
            }

            if (playerDirection == -1) {
                game.drawBitmap(
                    player.bounds.x,
                    player.bounds.y,
                    gfxPlayerUp
                );
            } else if (playerDirection == 1) {
                game.drawBitmap(
                    player.bounds.x,
                    player.bounds.y,
                    gfxPlayerDown
                );
            } else {
                game.drawBitmap(
                    player.bounds.x,
                    player.bounds.y,
                    (game.frameCount % 20 < 10) ? player.bitmap1 : player.bitmap2
                );
            }
            drawStatusText();
            break;

        // Begin next level
        case GAMESTATE_NEXT_LEVEL:
            game.clearScreen();
            if (levelCount < MAX_LEVEL) {
                game.drawCenteredText(28, "Level cleared!");
                if (game.frameCount %20 < 10) {
                    game.drawCenteredText(35, "- Press button -");
                }
                if (controller.justPressed(BUTTON_A)) {
                    nextLevel();
                    nextGamestate = GAMESTATE_GAME;
                }
            } else {
                nextGamestate = GAMESTATE_END;
            }
            break;

        // Game over screen
        case GAMESTATE_GAMEOVER:
            game.drawBitmap(0, 0, gameOverGfx);
            if (controller.justPressed(BUTTON_A)) {
                nextGamestate = GAMESTATE_TITLE;
            }
            break;

        // Game ending
        case GAMESTATE_END:
            game.drawBitmap(0, 0, gameEndGfx);
            // TODO play a sweet melody endlessly
            break;
    }

    gamestate = nextGamestate;
}

