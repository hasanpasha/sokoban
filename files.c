/*
files.c
______
Created by hasan,

Role: load the level and save it
Created On 2020/8/24
Last Edit 2020/8/24
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "files.h"
#include "constants.h"

int loadLevel(int level[][NB_BLOCKS_HEIGHT])
{
	FILE *file = NULL;
	char fileLine[NB_BLOCKS_WIDTH * NB_BLOCKS_HEIGHT + 1] = {};
	int i = 0, j = 0;
	file = fopen("levels.lvl", "r");
	if (file == NULL)
		return 0;
	
	fgets(fileLine, NB_BLOCKS_WIDTH * NB_BLOCKS_HEIGHT + 1, file);
	for (i = 0; i < NB_BLOCKS_WIDTH; ++i)
	{
		for (j = 0; j < NB_BLOCKS_HEIGHT; ++j)
		{
			switch (fileLine[(i * NB_BLOCKS_WIDTH) + j])
			{
				case '0':
				level[j][i] = 0;
				break;

				case '1':
				level[j][i] = 1;
				break;

				case '2':
				level[j][i] = 2;
				break;

				case '3':
				level[j][i] = 3;
				break;

				case '4':
				level[j][i] = 4;
				break;
			}
		}
	}
	fclose(file);
	return 1;
}

int saveLevel(int level[][NB_BLOCKS_HEIGHT])
{
	FILE *file = NULL;
	int i = 0, j = 0;
	file = fopen("levels.lvl", "w");
	if (file == NULL)
		return 0;
	for (i = 0; i < NB_BLOCKS_WIDTH; i++)
	{
		for (j = 0; j < NB_BLOCKS_HEIGHT; j++)
		{
			fprintf(file, "%d", level[j][i]);
		}
	}
	fclose(file);
	return 1;
}