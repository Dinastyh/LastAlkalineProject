#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#define WIDTH 348
#define HEIGHT 348

Uint32 getpixel(SDL_Surface* surface, int w, int h, int bpp,int pitch)
{
	Uint8 *p = (Uint8 *)surface->pixels + h * pitch + w * bpp;
	switch(bpp)
	{
		case 1:
			return *p;
			break;
		case 2:
			return *(Uint16 *)p;
			break;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return  p[0] << 16 | p[1] << 8 | p[2];
			else 
				return  p[2] << 16 | p[1] << 8 | p[0];
			break;
		default:
			printf("don't know man");
			break;


	
	
	}
}


int main(int argc, char *argv[])
{
	int temps = 0;
	SDL_Surface *test = NULL, *test2 = NULL;
	SDL_Renderer *renderer = NULL;	
	SDL_Window *window = NULL;
	SDL_Texture *texture = NULL;
	SDL_Init(SDL_INIT_VIDEO);
	Uint32 *format = 0;
	size_t i, j;
	Uint8 r;
	Uint8 g;
	Uint8 b;

// création de variable.



	test = SDL_LoadBMP("image2grey.bmp");

// 	création de la fenêtre et du renderer associé
	
	
	window = SDL_CreateWindow("try",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	texture = SDL_CreateTextureFromSurface(renderer, test);
//	SDL_UpdateTexture(texture, NULL, pixels, pitch);


	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, 0, 0);
	SDL_RenderPresent(renderer);
	scanf("%d", &temps);
	SDL_FreeSurface(test);
	SDL_FreeFormat(format);

	SDL_FreeSurface(test2);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
