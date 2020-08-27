/*
constants.h
____________

By hasan, 

Role: define some constants for all of the program (window size...)
*/

#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS
#define BLOCK_SIZE 34 // Block size (square) in pixels
#define NB_BLOCKS_WIDTH 12
#define NB_BLOCKS_HEIGHT 12
#define WINDOW_WIDTH (NB_BLOCKS_WIDTH * BLOCK_SIZE)
#define WINDOW_HEIGHT (NB_BLOCKS_HEIGHT * BLOCK_SIZE)
enum {UP, DOWN, LEFT, RIGHT}; // 0, 1, 2, 3
enum {EMPTY, WALL, BOX, GOAL, MARIO, BOX_OK}; // 0, 1, 2, 3, 4, 5
#endif