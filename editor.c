/*
editor.c
______
Created by hasan,

Role: Edit the map
Created On 2020/8/24
Last Edit 2020/8/24
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "editor.h"
#include "constants.h"

void editor(SDL_Surface *screen)
{
	SDL_Surface *wall = NULL, *box = NULL,
		*level = NULL, *currentMario = NULL,
		*mario = NULL;
	SDL_Rect position;
	SDL_Event event;
	int cont = 1;
	int leftClickInPeogress = 0, rightClickInPeogress = 0;
	int currentObject = WALL, i = 0, j = 0;
	int map[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT] = {0};

	// Loading the objects and the level
	wall = IMG_Load("imgs/wall.jpg");
	box = IMG_Load("imgs/box.jpg");
	level = IMG_Load("imgs/goal.png");
	mario = IMG_Load("imgs/mario_f.gif");
	if (!loadLevel(map))
		exit(EXIT_FAILURE);
	while (cont)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
			cont = 0;
			break;

			case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) // We put the chosen object (wall, box) in the click position
			{
				map[event.button.x / BLOCK_SIZE][event.button.y / BLOCK_SIZE]
					= currentObject;
				leftClickInPeogress = 1;
				// We put in mind that there's a pushed button			
			}
			else if (event.button.button == SDL_BUTTON_RIGHT) // right click to erase
			{
				map[event.button.x / BLOCK_SIZE][event.button.y / BLOCK_SIZE]
					= EMPTY;
				rightClickInPeogress = 1;
			}
			break;

			case SDL_MOUSEBUTTONUP: // We disable the boolean which
					//+ indicates that there's a clicked button
			if (event.button.button == SDL_BUTTON_RIGHT)
				rightClickInPeogress = 0;
			else if (event.button.button == SDL_BUTTON_LEFT)
				leftClickInPeogress = 0;
			break;

			case SDL_MOUSEMOTION:
			if (leftClickInPeogress) // If we move the mouse and the left button is clicked
			{
				map[event.button.x / BLOCK_SIZE][event.button.y / BLOCK_SIZE]
					= currentObject;
			}
			else if (rightClickInPeogress)
			{
				map[event.button.x / BLOCK_SIZE][event.button.y / BLOCK_SIZE]
					= EMPTY;
			}
			break;

			case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					cont = 0;
					break;

				case SDLK_s:
					saveLevel(map);
					break;

				case SDLK_c:
					loadLevel(map);
					break;

				case SDLK_1:
					currentObject = WALL;
					break;

				case SDLK_2:
					currentObject = BOX;
					break;

				case SDLK_3:
					currentObject = GOAL;
					break;

				case SDLK_4:
					currentObject = MARIO;
					break;
			}
			break;
		}
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
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
					case GOAL:
					SDL_BlitSurface(level, NULL, screen, &position);
					break;
					case MARIO:
					SDL_BlitSurface(mario, NULL, screen, &position);
				}
			}
		}
		SDL_Flip(screen);
	}
	SDL_FreeSurface(wall);
	SDL_FreeSurface(box);
	SDL_FreeSurface(level);
	SDL_FreeSurface(mario);
}