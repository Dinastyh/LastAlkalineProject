#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "DisplayPicture.h"
#include "Bmp24.h"
#include "PreProcessPicture.h"
#include <string.h>
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
		int size = 0;
		int charsize =0;
		int charmoyenne =0;
		int sure = 0;
		int mb =0;
		data.length = tpline.length;
		Picture* pics;
		for(int i = tpline.length - 1; i > -1; i--)
			{
				Tuple tpword = captureBlock(p->pixels, &(tpline.block[i]));
				Data* lines = malloc(sizeof(Data) * tpword.length);
				Data line;
				line.length = tpword.length;
				for(int j = 0; j < tpword.length; j++)
					{
						Tuple tpchar = captureChar(p->pixels, &(tpword.block[j]), p->w);
						Data* words = malloc(sizeof(Data) * tpchar.length*4);
						Data word;
						word.length = tpchar.length;
						charsize = 0;
						for(int k = 0; k < tpchar.length; k++)
						{
							charsize += tpchar.block[k].w;
						}
						charmoyenne = (charmoyenne + charsize / tpchar.length)/2;
						sure = 0;
						mb = tpchar.length;
						for(int k = 0; k < tpchar.length; k++)
							{
								Picture oneChar = blockToPicture(&(tpchar.block[k]), p);
								if(oneChar.w < charmoyenne)
								{
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
									words[sure] = charactere;
									sure ++;
								}
								else
								{
									pics = betterDetect(&oneChar,&size);
									if (size > 2)
									{ 
										mb += size -2;
										//void* yet = realloc(word.thing,sizeof(Data)*(mb));
										//if (yet != NULL)
										//{
										//	word.thing = yet;
										//}
										//else
										//{
										//	printf("YES\n");
										//}	
										word.length = mb;
									}

									for(int yup = 0; yup < size -1; yup++)
									{
										
									resize(&pics[yup], 40, 40);
									double* pixChar = malloc(sizeof(double) * 1600);
									Data charactere;
									charactere.length = 1600;
									for(int m = 0; m < 1600; m++)
										{
											if(pics[yup].pixels[m].r == 0)
												{
													pixChar[m] = 1;
												}
											else
												{
													pixChar[m] = 0;
												}
										}
									charactere.thing = (double*)pixChar;
									words[sure] = charactere;
									sure ++;
									}
									free(pics);
								}
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
void create66Picture()
{
    char header[20];
    strcat(header, "datasetPages/0.bmp");
    char charac[16];
    strcat(charac, "TimBG/0.bmp");
    size_t filePassed = 0;
    size_t lenFileName = 14;
    size_t lenFile = 18;
    size_t semi, semiI;
    while(filePassed < 200)
    {
        FILE* f = fopen(header, "r");
        if(f != NULL)
        {
            Picture p = newPicture(header, charac);
            blackAndWhite(&p);
            Tuple tpline = captureLine(&p);
            for(int i = tpline.length - 1; i > -1; i--)
            {
                Tuple tpword = captureBlock(p.pixels, &(tpline.block[i]));
                for(int j = 0; j < tpword.length; j++)
                {
                    Tuple tpchar = captureChar(p.pixels, &(tpword.block[j]), p.w);
                    for(int k = 0; k < tpchar.length; k++)
                    {
                        Picture oneChar = blockToPicture(&(tpchar.block[k]), &p);
                        resize(&oneChar, 28, 28);
                        savePicture(&oneChar);
                        if(incrementerString(charac, &lenFileName) == 1)
                        {
                            semiI = lenFileName;
                            while(charac[semiI - 1] != '/')
                            {
                                charac[semiI] = charac[semiI - 1];
                                semiI -= 1;
                            }
                            charac[semiI] = '1';
                        }
                        free(oneChar.pixels);
                        free(oneChar.head);
                        p.name = charac;
                    }
                }
            }
            free(p.pixels);
            free(p.head);
            fclose(f);
        }
        if(incrementerString(header, &lenFile) == 1)
        {
            semi = lenFile;
            while(header[semi - 1] != '/')
            {
                header[semi] = header[semi - 1];
                semi -= 1;
            }
            header[semi] = '1';
        }
        filePassed++;
    }
}
char incrementerString(char* deb, size_t *len)
{
    int parcours = *len - 5;
    char current = 1;
    while(deb[parcours] != 47 && current == 1)
    {
        current = deb[parcours] ;
        current += 1;
        if(current > 57)
        {
            deb[parcours] = (char)48;
            current = 1;
        }
        else
        {
            deb[parcours] = (char)current;
        }
        parcours--;
    }
    if(current == 1)
    {
        *len += 1;
        return 1;
    }
    return 0;
}
