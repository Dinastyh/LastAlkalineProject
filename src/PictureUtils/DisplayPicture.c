#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "DisplayPicture.h"
#include "Bmp24.h"
#include "PreProcessPicture.h"
void displayPicture(char *filename)
{
		// take relative || absolute path of a picture to display
		SDL_Surface *picture = NULL;
		SDL_Window  *window  = NULL;
		SDL_Texture *texture = NULL;
		SDL_Renderer *renderer = NULL;
		SDL_Init(SDL_INIT_VIDEO);

		Picture p = newPicture(filename, "test.bmp");
		window =  SDL_CreateWindow("Display",SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED, p.w, p.h, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		savePicture(&p);
		picture = SDL_LoadBMP(filename);
		if(picture == NULL)
			 printf("%s : Invalid Name of Picture\n", filename);

		texture = SDL_CreateTextureFromSurface(renderer, picture);

		if(texture == NULL)
			 printf("%s : Invalide Format of BMP\n", filename);


		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, 0, 0);
		SDL_RenderPresent(renderer);
		waitKeyPressed();
		SDL_FreeSurface(picture);
		SDL_DestroyWindow(window);
		SDL_Quit();
}

void waitKeyPressed()
{
		SDL_Event event;
		do
			{
				SDL_PollEvent(&event);
			} while(event.type != SDL_KEYDOWN);

		do
			{
				SDL_PollEvent(&event);
			} while(event.type != SDL_KEYUP);
}

void displaySegmentationPicture(char* filename)
{
		Picture p = newPicture(filename, "test.bmp");
		Tuple tple = captureLine(&p);
		displayPicture(filename);
		for(int i = 0; i < tple.length; i++)
			{
				Picture c = blockToPicture(&(tple.block[tple.length - i - 1]), &p);
				Tuple ch = captureChar(p.pixels, &(tple.block[tple.length - i - 1]), p.w);
				savePicture(&c);
				displayPicture(c.name);
				for(int j = 0; j < ch.length; j++)
					{
						Picture carac = blockToPicture(&(ch.block[j]), &p);
						resize(&carac, 28, 28);
						savePicture(&carac);
						displayPicture(carac.name);
					}
			}
}

Data createData(Picture *p)
{
		Tuple tpline = captureLine(p);
		Data* dataLines = malloc(sizeof(Data) * tpline.length);
		Data data;
		data.length = tpline.length;
		for(int i = tpline.length - 1; i > -1; i--)
		{
				Tuple tpword = captureBlock(p->pixels, &(tpline.block[i]));
				Data* lines = malloc(sizeof(Data) * tpword.length);
				Data line;
				line.length = tpword.length;
				for(int j = 0; j < tpword.length; j++)
				{
						Tuple tpchar = captureChar(p->pixels, &(tpword.block[j]), p->w);
						Data* words = malloc(sizeof(Data) * tpchar.length);
						Data word;
						word.length = tpchar.length;
						for(int k = 0; k < tpchar.length; k++)
						{
								Picture oneChar = blockToPicture(&(tpchar.block[k]), p);
								resize(&oneChar, 40, 40);
								double* pixChar = malloc(sizeof(double) * 1600);
								Data charactere;
								charactere.length = 1600;
								for(int m = 0; m < 1600; m++)
								{
										if(oneChar.pixels[m].r == 0)
										{
												pixChar[m] = 1;
										}
										else
										{
												pixChar[m] = 0;
										}
								}
								charactere.thing = (double*)pixChar;
								words[k] = charactere;
								savePicture(&oneChar);
								displayPicture("tmp.bmp");
						}
						word.thing = (Data*)words;
						lines[j] = word;
				}
				line.thing = (Data*)lines;
				dataLines[tpline.length - i - 1] = line;
		}
		data.thing = (Data*)dataLines;
		return data;
}
