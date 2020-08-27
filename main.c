/*
main.c
_______
created by hasan, 

Role, Control the other part of the game, 
Created on 2020/8/23
Last Edit 2020/8/23
*/

// Including 
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constants.h"
#include "game.h"
#include "editor.h"
#include "files.h"

// main function
int main(int argc, char const *argv[])
{
	SDL_Surface *screen = NULL, *menu = NULL; // Create surfaces
	SDL_Rect menuPosition;
	SDL_Event event;
	int cont = 1;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetIcon(IMG_Load("imgs/box.jpg"), NULL); // The icon must be 
		//+ loaded before SDL_SetVideoMode
	screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT,
		 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Mario Sokoban", NULL);
	menu = IMG_Load("imgs/menu.jpg");
	menuPosition.x = 0;
	menuPosition.y = 0;
	while (cont)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT: // TO exit the game
			cont = 0;
			break;

			case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				cont = 0;
				break;

				case SDLK_1: // Want to play
				play(screen);
				break;

				case SDLK_2:	// Want to edit levels
				editor(screen);
				break;
			}
			break;
		}
		// Cleaning the screen
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
		SDL_BlitSurface(menu, NULL, screen, &menuPosition);
		SDL_Flip(screen);
	}
	SDL_FreeSurface(menu);
	SDL_Quit();
	return EXIT_SUCCESS;
}