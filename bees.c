#include "gba.h"
#include "bees.h"
#include <stdio.h>
#include <stdlib.h>

BEE bees[BEECOUNT];
u16 bee[10][11] = {
    {GRASS, GRASS, GRASS, BLACK, BLACK, GRASS, BLACK, BLACK, GRASS, GRASS, GRASS},
    {GRASS, GRASS, BLACK, WHITE, WHITE, BLACK, WHITE, WHITE, BLACK, GRASS, GRASS},
    {GRASS, GRASS, BLACK, WHITE, WHITE, WHITE, BLACK, WHITE, BLACK, GRASS, GRASS},
    {GRASS, GRASS, GRASS, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GRASS, GRASS},
    {GRASS, GRASS, BLACK, BLACK, YELLOW, BLACK, YELLOW, YELLOW, YELLOW, BLACK, GRASS},
    {GRASS, BLACK, YELLOW, BLACK, YELLOW, BLACK, YELLOW, YELLOW, YELLOW, YELLOW, BLACK},
    {BLACK, BLACK, YELLOW, BLACK, YELLOW, BLACK, YELLOW, YELLOW, BLACK, YELLOW, BLACK},
    {GRASS, BLACK, YELLOW, BLACK, YELLOW, BLACK, YELLOW, YELLOW, YELLOW, YELLOW, BLACK},
    {GRASS, GRASS, BLACK, BLACK, YELLOW, BLACK, YELLOW, YELLOW, YELLOW, BLACK, GRASS},
    {GRASS, GRASS, GRASS, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GRASS, GRASS},
};

u16 *beeBitmaps[] = {bee};

void initializeBees()
{
  for (int i = 0; i < BEECOUNT; i++)
  {
    bees[i].x = 120 + (i * 40) % 140;
    bees[i].y = 40;
    bees[i].oldx = bees[i].x;
    bees[i].oldy = bees[i].y;
    bees[i].bitmap = beeBitmaps[i];
  }
}

void drawBee(int x, int y, BEE *bee_ptr)
{
  for (int i = 0; i < BEEHEIGHT; i++)
  {
    DMANow(3, &(bee_ptr->bitmap[i * BEEWIDTH]), &videoBuffer[OFFSET(x, y + i, SCREENWIDTH)], BEEWIDTH);
  }
}
