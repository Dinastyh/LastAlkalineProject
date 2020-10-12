#include <stdio.h>
#include <stdlib.h>
#include "bmp24.h"
Picture newPicture(const char *filename,char *newfilename)
	{
		Picture picture;
		FILE *file = fopen(filename,"rb");
		char* data = malloc(56);
		int w = 0;
		int h = 0;
		int r = 0;
		int b = 0;
		int g = 0;
		float average = 0;
		Pixel pixel;
		for(int i = 0; i < 54; i++)
		{
			data[i] = fgetc(file);
		}
		if (data[0] != 'B' || data[1] != 'M')
		{
			printf("wrong format");
			
		}		
		
		picture.head = data;
		picture.name = newfilename;
		
		fseek(file,18,SEEK_SET);
		
		w = fgetc(file) + 256 *fgetc(file) + 256 * 256 * fgetc(file) 
			+ 256 * 256 * 256 * fgetc(file);
		h = fgetc(file) + 256 *fgetc(file) + 256 * 256 * fgetc(file) 
			+ 256 * 256 * 256 * fgetc(file);
		picture.h = h;
		picture.w = w;
		
		Pixel *pixels = malloc(sizeof(Pixel) * h * w);
		fseek(file,54,SEEK_SET);
		for(int i = 0; i < w * h; i++)
		{
			b =  fgetc(file);
			g =  fgetc(file);
			r =  fgetc(file); 
			pixel.r = r;
			pixel.b = b;
			pixel.g = g;
			average += r + g + b; 
			pixels[i] = pixel;
		}
		picture.pixels = pixels;
		picture.averagecolor = average/(h*w*3);
		fclose(file);
		return picture;
	}

void savePicture(Picture picture)
	{
		FILE* file =fopen(picture.name,"wb+");
		for(int i = 0; i<54; i++)
		{
			fputc(picture.head[i],file);
		}

		for(int i = 0; i<picture.w * picture.h;i++)
		{
			fputc(picture.pixels[i].b,file);
			fputc(picture.pixels[i].g,file);
			fputc(picture.pixels[i].r,file);
		}
		free(picture.pixels);
		free(picture.head);
		fclose(file);
	}

void BlackAndWhite (Picture picture)
	{
		float color;
		for (int i = 0; i < picture.h*picture.w;i++)
		{
			color = ((float)(picture.pixels[i].r + picture.pixels[i].g + picture.pixels[i].b))/3;
			if (color > picture.averagecolor)
			{
				picture.pixels[i].r = 255;
				picture.pixels[i].g = 255;
			       	picture.pixels[i].b = 255;
			}
			else
			{
				 picture.pixels[i].r = 0;
				 picture.pixels[i].g = 0;
				 picture.pixels[i].b = 0;
			}
		}
	}

