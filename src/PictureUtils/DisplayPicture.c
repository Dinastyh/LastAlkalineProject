#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
void DisplayPicture(const char *filename, int width, int height) 
{	
	// take relative || absolute path of a picture to display
	SDL_Surface *picture = NULL;
	SDL_Window  *window  = NULL;
	SDL_Texture *texture = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Display",SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	picture = SDL_LoadBMP(filename);
	if(picture == NULL)
		printf("%c : Invalid Name of Picture", filename);
	texture = SDL_CreateTextureFromSurface(renderer, picture);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, 0, 0);
	SDL_RenderPresent(renderer);
	SDL_Delay(5000);
	SDL_FreeSurface(picture);
	SDL_DestroyWindow(window);
	SDL_Quit();


}
