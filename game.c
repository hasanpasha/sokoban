/*
game.c
______
Created by hasan,

Role: Move the content on screen
Created On 2020/8/24
Last Edit 2020/8/24
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constants.h"
#include "game.h"
#include "files.h"

void play(SDL_Surface *screen)
{
	SDL_Surface *mario[4] = {NULL}; // 4 surface for the 4 directions of mario
	SDL_Surface *wall = NULL, *box = NULL, *boxOK = NULL,
		*objective = NULL, *level = NULL, *currentMario = NULL;
	SDL_Rect position, playerPosition;
	SDL_Event event;
	int cont = 1, remainingGoals = 0, i = 0, j = 0;
	int map[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT] = {0}; // for the mapping 
	
	// Loading the sprites (Boxes, Player...)
	wall = IMG_Load("imgs/wall.jpg");
	box = IMG_Load("imgs/box.jpg");
	boxOK = IMG_Load("imgs/box_ok.jpg");
	level = IMG_Load("imgs/goal.png");
	mario[DOWN] = IMG_Load("imgs/mario_f.gif");
	mario[UP] = IMG_Load("imgs/mario_b.gif");
	mario[RIGHT] = IMG_Load("imgs/mario_right.gif");
	mario[LEFT] = IMG_Load("imgs/mario_left.gif");
	currentMario = mario[DOWN];

	// Loading the level
	if (!(loadLevel(map)))
		exit(EXIT_FAILURE); // we stop the game if we couldn't load the level

	// We search for the position of Mario in the begining of the game
	for (i = 0; i < NB_BLOCKS_WIDTH; ++i)
	{
		for (j = 0; j < NB_BLOCKS_HEIGHT; ++j)
		{
			if (map[i][j] == MARIO)
			{
				playerPosition.x = i;
				playerPosition.y = j;
				map[i][j] = EMPTY;
			}
		}
	}

	// Enabling keys repetition
	SDL_EnableKeyRepeat(100, 100);

	// The main loop
	while (cont)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
			cont = 0;
			break;

			case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				cont = 0;
				break;

				case SDLK_UP:
				currentMario = mario[UP];
				movePlayer(map, &playerPosition, UP);
				break;

				case SDLK_DOWN:
				currentMario = mario[DOWN];
				movePlayer(map, &playerPosition, DOWN);
				break;

				case SDLK_RIGHT:
				currentMario = mario[RIGHT];
				movePlayer(map, &playerPosition, RIGHT);
				break;

				case SDLK_LEFT:
				currentMario = mario[LEFT];
				movePlayer(map, &playerPosition, LEFT);
				break;
			}
			break;
		}

		// Cleaning the screen
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

		// Placing the objects on screen
		remainingGoals = 0;
		for (i = 0; i < NB_BLOCKS_WIDTH; ++i)
		{
			for (j = 0; j < NB_BLOCKS_HEIGHT; ++j)
			{
				position.x = i * BLOCK_SIZE;
				position.y = j * BLOCK_SIZE;
				switch (map[i][j])
				{
					case WALL:
					SDL_BlitSurface(wall, NULL, screen, &position);
					break;
					case BOX:
					SDL_BlitSurface(box, NULL, screen, &position);
					break;
					case BOX_OK:
					SDL_BlitSurface(boxOK, NULL, screen, &position);
					break;
					case GOAL:
					SDL_BlitSurface(level, NULL, screen, &position);
					remainingGoals = 1;
					break;
				}
			}
		}
		if (!remainingGoals)
		{
			cont = 0;
		}

		// We place the player in the right position
		position.x = playerPosition.x * BLOCK_SIZE;
		position.y = playerPosition.y * BLOCK_SIZE;
		SDL_BlitSurface(currentMario, NULL, screen, &position);

		// Refresh the screen for the player
		SDL_Flip(screen);
	}

	// Disabling keys repetiton (reset to 0)
	SDL_EnableKeyRepeat(0, 0);

	// Freeing the used surfaces
	SDL_FreeSurface(wall);
	SDL_FreeSurface(box);
	SDL_FreeSurface(boxOK);
	SDL_FreeSurface(level);
	for (int i = 0; i < 4; ++i)
		SDL_FreeSurface(mario[i]);
}

void movePlayer(int map[][NB_BLOCKS_HEIGHT], SDL_Rect *pos, int direction)
{
	switch (direction)
	{
		case UP:
		if (pos->y -1 < 0) // If the player exceeds the screen, we stop
			break;
		if (map[pos->x][pos->y - 1] == WALL) // If there's a wall, we stop
			break;
		if ((map[pos->x][pos->y - 1] == BOX || map[pos->x][pos->y - 1] == BOX_OK)
		 && (pos->y -2 < 0 || map[pos->x][pos->y - 2] == BOX || 
		 	map[pos->x][pos->y - 2] == BOX_OK || map[pos->x][pos->y - 2]
		 	== WALL))
		 	break;
		 // If we are here, so we can move the player 
		 // We verify if there's a box to move first
		moveBox(&map[pos->x][pos->y - 1], &map[pos->x][pos->y - 2]);
		pos->y--; // Finally, we can move up the player (ouf!)
		break;

		case DOWN:
		if (pos->y + 1 > (NB_BLOCKS_HEIGHT * BLOCK_SIZE)) // If the player exceeds the screen, we stop
			break;
		if (map[pos->x][pos->y + 1] == WALL) // If there's a wall, we stop
			break;
		if ((map[pos->x][pos->y + 1] == BOX || map[pos->x][pos->y + 1] == BOX_OK)
		 && (pos->y + 2 > (NB_BLOCKS_HEIGHT * BLOCK_SIZE) 
		 	|| map[pos->x][pos->y + 2] == BOX || 
		 	map[pos->x][pos->y + 2] == BOX_OK || map[pos->x][pos->y + 2]
		 	== WALL))
		 	break;
		moveBox(&map[pos->x][pos->y + 1], &map[pos->x][pos->y + 2]);
		pos->y++;
		break;

		case RIGHT:
		if (pos->x + 1 > (NB_BLOCKS_WIDTH * BLOCK_SIZE)) // If the player exceeds the screen, we stop
			break;
		if (map[pos->x + 1][pos->y] == WALL) // If there's a wall, we stop
			break;
		if ((map[pos->x + 1][pos->y] == BOX || map[pos->x + 1][pos->y] == BOX_OK)
		 && (pos->x + 2 > (NB_BLOCKS_WIDTH * BLOCK_SIZE) 
		 	|| map[pos->x + 2][pos->y] == BOX || 
		 	map[pos->x + 2][pos->y] == BOX_OK || map[pos->x + 2][pos->y]
		 	== WALL))
		 	break;
		moveBox(&map[pos->x + 1][pos->y], &map[pos->x + 2][pos->y]);
		pos->x++;
		break;

		case LEFT:
		if (pos->x - 1 < 0) // If the player exceeds the screen, we stop
			break;
		if (map[pos->x - 1][pos->y] == WALL) // If there's a wall, we stop
			break;
		if ((map[pos->x - 1][pos->y] == BOX || map[pos->x - 1][pos->y] == BOX_OK)
		 && (pos->x - 2 < 0 
		 	|| map[pos->x - 2][pos->y] == BOX || 
		 	map[pos->x - 2][pos->y] == BOX_OK || map[pos->x - 2][pos->y]
		 	== WALL))
		 	break;
		moveBox(&map[pos->x - 1][pos->y], &map[pos->x - 2][pos->y]);
		pos->x--;
		break;
	}
}

void moveBox(int *firstSquare, int *secondSquare)
{
	if (*firstSquare == BOX || *firstSquare == BOX_OK)
	{
		if (*secondSquare == GOAL)
			*secondSquare = BOX_OK;
		else
			*secondSquare = BOX;
		
		if (*firstSquare == BOX_OK)
			*firstSquare = GOAL;
		else
			*firstSquare = EMPTY;
	}
}