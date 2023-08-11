#include <stdlib.h>
#include <stdio.h>
#include "gba.h"
#include "flowers.h"
#include "sound.h"
#include "print.h"
#include "game.h"

// function prototypes

void initialize();
void goToStart();
void start();
void goToGame();
void game();
void goToPause();
void pause();
void goToWin();
void win();
void goToLose();
void lose();
void strrev();
void swap();

// buffer for score count
char buffer[41];

char testStr[] = "Alexander";

unsigned short oldButtons;
unsigned short buttons;

// state enums
enum
{
    START,
    GAME,
    PAUSE,
    WIN,
    LOSE
};
int state;

// test for exam corrections

int main()
{

    initialize();
    while (1)
    {
        oldButtons = buttons;
        buttons = REG_BUTTONS;

        // state machine
        switch (state)
        {
        case START:
            start();
            break;
        case GAME:
            game();
            break;
        case PAUSE:
            pause();
            break;
        case WIN:
            win();
            break;
        case LOSE:
            lose();
            break;
        }
    }
}

// Initializes registers
void initialize()
{

    mgba_open();
    REG_DISPCTL = MODE(3) | BG_ENABLE(2);

    buttons = REG_BUTTONS;
    oldButtons = 0;

    REG_SOUNDCNT_X = SND_ENABLED;

    REG_SOUNDCNT_L = DMG_VOL_LEFT(5) |
                     DMG_VOL_RIGHT(5) |
                     DMG_SND1_LEFT |
                     DMG_SND1_RIGHT |
                     DMG_SND2_LEFT |
                     DMG_SND2_RIGHT |
                     DMG_SND3_LEFT |
                     DMG_SND3_RIGHT |
                     DMG_SND4_LEFT |
                     DMG_SND4_RIGHT;
    REG_SOUNDCNT_H = DMG_MASTER_VOL(2);

    goToStart();
}

// sets state to start and initializes start screen
void goToStart()
{
    fillScreen(TEAL);

    // strrev(testStr);
    // drawString(20, 20, testStr, WHITE);
    char grandmasChars[8] = {'G', 'R', 'A', 'N', 'D', 'M', 'A', 'S'};
    char flowersChars[7] = {'F', 'L', 'O', 'W', 'E', 'R', 'S'};
    unsigned short colors[8] = {FLOWER_DARK_ORANGE, FLOWER_LIGHT_PURPLE, APPLE_LIGHT_GREEN, FLOWER_MIDDLE, APPLE_LIGHT_BROWN, TURQUOISE, FLOWER_LIGHT_ORANGE, FLOWER_DARK_ORANGE};
    int col = 72;
    int spacing = 12;
    for (int i = 0; i < 8; i++)
    {
        drawChar(col + (i * spacing), 60, grandmasChars[i], colors[i]);
    }
    for (int i = 0; i < 7; i++)
    {
        drawChar(78 + (i * spacing), 74, flowersChars[i], colors[i]);
    }

    drawString(92, 96, "Alex Lee", OFFWHITE);

    state = START;
}

// waits for user to start game
void start()
{
    waitForVBlank();
    if (BUTTON_PRESSED(BUTTON_START))
    {
        goToGame();
        initGame();
    }
}

// sets state to game and initializes game screen
void goToGame()
{
    fillScreen(GRASS);
    drawRect(0, 0, SCREENWIDTH, 25, GRASS);
    drawString(173, 1, "flowers", OFFWHITE);

    state = GAME;
}

// game state
// handles win/loss conditions and allows the player to pause
void game()
{
    updateGame();

    sprintf(buffer, "%i", score);

    waitForVBlank();
    drawString(173, 1, "flowers", OFFWHITE);
    drawRect(220, 1, 20, 8, GRASS);
    drawString(220, 1, buffer, OFFWHITE);

    drawGame();

    if (BUTTON_PRESSED(BUTTON_START))
    {
        goToPause();
    }
    if (lives <= 0)
    {
        goToLose();
    }
    if (score >= 20)
    {
        goToWin();
    }
}

// sets state to pause
void goToPause()
{
    fillScreen(OFFWHITE);
    drawString(63, 73, "GRANDMA'S WAITING!", GRASS);
    state = PAUSE;
}

// allows user to press start to un-pause or select to start over
void pause()
{
    waitForVBlank();
    if (BUTTON_PRESSED(BUTTON_START))
        goToGame();
    else if (BUTTON_PRESSED(BUTTON_SELECT))
        goToStart();
}

// initializes win screen and sets state to win
void goToWin()
{
    fillScreen(OFFWHITE);
    drawString(95, 60, "You Won!", GRASS);
    drawString(29, 85, "Grandma will love the flowers!", GRASS);
    waitForVBlank();
    state = WIN;
}

// allows user to press start to play again
void win()
{
    waitForVBlank();
    if (BUTTON_PRESSED(BUTTON_START))
    {
        goToStart();
    }
}

// initializes loose screen and sets state to lose
void goToLose()
{
    fillScreen(OFFWHITE);
    drawString(85, 60, "You Lost...", GRASS);
    drawString(50, 85, "Grandma is Flowerless!", GRASS);
    state = LOSE;
}

// waits for user to press start to play again
void lose()
{
    waitForVBlank();
    if (BUTTON_PRESSED(BUTTON_START))
    {
        goToStart();
    }
}

// void strrev(char str[])
// {
//     int len = 0;
//     char *endPtr = str;
//     while (*endPtr)
//     {
//         endPtr++;
//         len++;
//     }
//     len--;
//     for (int i = 0; i < len / 2; i++)
//     {
//         swap(&str[i], &str[len - i]);
//     }
// }

// void swap(char *one, char *two)
// {
//     char temp = *one;
//     *one = *two;
//     *two = temp;
// }