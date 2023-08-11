#include "gba.h"
#include "hearts.h"

HEART hearts[HEARTCOUNT];
u16 heart[11][13] = {
    {GRASS, GRASS, BLACK, BLACK, BLACK, GRASS, GRASS, GRASS, BLACK, BLACK, BLACK, GRASS, GRASS},
    {GRASS, BLACK, RED, RED, RED, BLACK, GRASS, BLACK, RED, RED, RED, BLACK, GRASS},
    {BLACK, RED, WHITE, WHITE, RED, RED, BLACK, RED, RED, RED, RED, RED, BLACK},
    {BLACK, RED, WHITE, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK},
    {BLACK, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK},
    {GRASS, BLACK, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, GRASS},
    {GRASS, GRASS, BLACK, RED, RED, RED, RED, RED, RED, RED, BLACK, GRASS, GRASS},
    {GRASS, GRASS, GRASS, BLACK, RED, RED, RED, RED, RED, BLACK, GRASS, GRASS, GRASS},
    {GRASS, GRASS, GRASS, GRASS, BLACK, RED, RED, RED, BLACK, GRASS, GRASS, GRASS, GRASS},
    {GRASS, GRASS, GRASS, GRASS, GRASS, BLACK, RED, BLACK, GRASS, GRASS, GRASS, GRASS, GRASS},
    {GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, BLACK, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS},

};

u16 *heartBitmaps[] = {heart, heart, heart};

void initializeHearts()
{
  for (int i = 0; i < HEARTCOUNT; i++)
  {
    hearts[i].x = 5 + (15 * i);
    hearts[i].y = 5;
    hearts[i].oldx = hearts[i].x;
    hearts[i].oldy = hearts[i].y;
    hearts[i].bitmap = heartBitmaps[i];
    hearts[i].active = 1;
  }
}

void drawHeart(int x, int y, HEART *heart_ptr)
{
  for (int i = 0; i < HEARTHEIGHT; i++)
  {
    DMANow(3, &(heart_ptr->bitmap[i * HEARTWIDTH]), &videoBuffer[OFFSET(x, y + i, SCREENWIDTH)], HEARTWIDTH);
  }
}