#ifndef GAME_H
#define GAME_H

extern int score;
extern int lives;

// function prototypes
void initGame();
void updateGame();
void updatePlayer();
void updateFlowers();
void updateBees();
void updateApple();
void drawGame();

#endif