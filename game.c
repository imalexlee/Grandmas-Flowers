#include "gba.h"
#include "game.h"
#include "sound.h"
#include "player.h"
#include "flowers.h"
#include "hearts.h"
#include "apple.h"
#include "bees.h"
#include <stdio.h>
#include <stdlib.h>

int score;
int rSeed;
int lives;
int timer;
int playerSpeed;

// initialize the game state
void initGame()
{
    score = 0;
    rSeed = 0;
    lives = 3;
    timer = 0;
    playerSpeed = 1;

    initializePlayer();
    initializeFlowers();
    initializeBees();
    initializeHearts();
    initializeApple();
    REG_SND2CNT = DMG_ENV_VOL(5) | DMG_STEP_TIME(7);
}

// wrapper for all updates
void updateGame()
{
    rSeed++;
    timer++;
    updateBees();
    updatePlayer();
    updateFlowers();
    updateApple();
}

// update the player position
void updatePlayer()
{
    if (BUTTON_HELD(BUTTON_LEFT) && (player.x - 1 > 0))
    {
        player.xVelocity = -playerSpeed;
    }
    else if (BUTTON_HELD(BUTTON_RIGHT) && (player.x + player.width < SCREENWIDTH - 1))
    {
        player.xVelocity = playerSpeed;
    }
    else
    {
        player.xVelocity = 0;
    }
    if (BUTTON_HELD(BUTTON_UP) && (player.y - 1 > 0))
    {
        player.yVelocity = -playerSpeed;
    }
    else if (BUTTON_HELD(BUTTON_DOWN) && (player.y + player.height + 1 < SCREENHEIGHT))
    {
        player.yVelocity = playerSpeed;
    }
    else
    {
        player.yVelocity = 0;
    }

    player.oldx = player.x;
    player.oldy = player.y;

    // reduces speed if player is in special zone
    // zone switches from top left to entire top when score >= 10
    if (score >= 10)
    {
        if (collision(player.x, player.y, PLAYERWIDTH, PLAYERHEIGHT, 0, 0, SCREENWIDTH, 25))
        {
            if (timer % 2)
            {
                player.x += player.xVelocity;
                player.y += player.yVelocity;
            }
        }
        else
        {
            player.x += player.xVelocity;
            player.y += player.yVelocity;
        }
    }
    else
    {
        if (collision(player.x, player.y, PLAYERWIDTH, PLAYERHEIGHT, 0, 0, SCREENWIDTH / 2, 25))
        {
            if (timer % 2)
            {
                player.x += player.xVelocity;
                player.y += player.yVelocity;
            }
        }
        else
        {
            player.x += player.xVelocity;
            player.y += player.yVelocity;
        }
    }
}

// update the flower positions based on collisions
void updateFlowers()
{
    // check for collision of any flower and the player
    for (int i = 0; i < FLOWERCOUNT; i++)
    {
        if (collision(player.x, player.y, PLAYERWIDTH, PLAYERHEIGHT, flowers[i].x, flowers[i].y, FLOWERWIDTH, FLOWERHEIGHT) && flowers[i].active)
        {
            srand(rSeed);
            flowers[i].oldx = flowers[i].x;
            flowers[i].oldy = flowers[i].y;
            flowers[i].x = rand() % 233;
            flowers[i].y = 20 + (rand() % 126);
            flowers[i].active = 0;
            score++;
            REG_SND2FREQ = NOTE_C6 | SND_RESET;
            // flower pool only displays 3 flowers out of 5 at a time
            // sets the next inactive flower to active
            for (int j = i + 1; j < FLOWERCOUNT + i + 1; j++)
            {
                if (!flowers[j % FLOWERCOUNT].active)
                {
                    flowers[j % FLOWERCOUNT].active = 1;
                    break;
                }
            }
        }
    }
}

// updates bee position to track player
void updateBees()
{
    for (int i = 0; i < BEECOUNT; i++)
    {
        // reduces lives when player hits a bee
        if (collision(player.x, player.y, PLAYERWIDTH, PLAYERHEIGHT, bees[i].x, bees[i].y, BEEWIDTH, BEEHEIGHT))
        {
            lives--;
            bees[i].oldx = bees[i].x;
            bees[i].oldy = bees[i].y;
            bees[i].x = (bees[i].x + 70) % 230;
            bees[i].y = (bees[i].y + 70) % 159;
            REG_SND2FREQ = NOTE_G2 | SND_RESET;
        }
    }
    if (timer % 2)
    {

        for (int i = 0; i < BEECOUNT; i++)
        {
            bees[i].oldx = bees[i].x;
            bees[i].oldy = bees[i].y;
            if (player.x > bees[i].x)
            {
                bees[i].x += 1;
            }
            else
            {
                bees[i].x -= 1;
            }

            if (player.y > bees[i].y)
            {
                bees[i].y += 1;
            }
            else
            {
                bees[i].y -= 1;
            }
        }
    }
}

// sets the apples state to inactive if it is eaten
// increases the players overall speed
void updateApple()
{
    if (collision(player.x, player.y, PLAYERWIDTH, PLAYERHEIGHT, apple.x, apple.y, APPLEWIDTH, APPLEHEIGHT) && apple.active)
    {
        apple.active = 0;
        playerSpeed = 2;
        REG_SND2FREQ = NOTE_G5 | SND_RESET;
    }
}

// wrapper to draw all game elements after update
void drawGame()
{
    // draw apple
    if (apple.active)
    {
        drawApple(200, 100, &apple);
    }
    else
    {
        drawRect(200, 100, 12, 13, GRASS);
    }
    // draw hearts
    drawRect(5, 5, 45, 11, GRASS);
    for (int i = 0; i < lives; i++)
    {
        drawHeart(hearts[i].x, hearts[i].y, &hearts[i]);
    }
    // draw flowers
    for (int i = 0; i < FLOWERCOUNT; i++)
    {
        drawRect(flowers[i].oldx, flowers[i].oldy, FLOWERWIDTH, FLOWERHEIGHT, GRASS);
        if (flowers[i].active)
        {
            drawFlower(flowers[i].x, flowers[i].y, &flowers[i]);
        }
    }
    // draw bee
    for (int i = 0; i < BEECOUNT; i++)
    {
        drawRect(bees[i].oldx, bees[i].oldy, BEEWIDTH, BEEHEIGHT, GRASS);
        drawBee(bees[i].x, bees[i].y, &bees[i]);
    }

    // draw player
    drawRect(player.oldx, player.oldy, 14, 16, GRASS);
    drawPlayer(player.x, player.y, &player);
}
