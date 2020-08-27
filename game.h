/*
game.h
______
Created by hasan,

Role: Contain game.c modules
Created On 2020/8/23
Last Edit 2020/8/23
*/

#ifndef DEF_GAME
#define DEF_GAME

void play(SDL_Surface *screen);
void movePlayer(int map[][NB_BLOCKS_HEIGHT], SDL_Rect *pos, int direction);
void moveBox(int *firstSquare, int *secondSquare);

#endif