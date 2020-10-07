#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bmp24.h"

Picture newPicture(const char* filename,const char* newfilename)
	{
		Picture picture;
		FILE* file = fopen("filename","rb");
		int size = sizeof(file);
		char* data = malloc(size);
		int w = 0;
		int h = 0;
		int r = 0;
		int b = 0;
		int g = 0;
		double average =0;
		Pixel pixel;
		fgets(data,54,file);
		if (data[0] != 'B' || data[1] != 'M')
		{
			printf("wrong format");
			
		}		
		picture.head = data;
		picture.name = newfilename;
		fseek(file,18,SEEK_SET);
		w = fgetc(file) + 256 *fgetc(file) + 256 * 256 * fgetc(file) + 256 * 256 * 256 * fgetc(file);
		h = fgetc(file) + 256 *fgetc(file) + 256 * 256 * fgetc(file) + 256 * 256 * 256 * fgetc(file);
		picture.h = h;
		picture.w = w;
		Pixel* pixels = malloc(h*w);
		fseek(file,54,SEEK_SET);
		for(int i = 0; i <w*h ; i++)
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
		fclose("filename");
		return picture;
	}

	void savePicture(Picture picture)
	{
		FILE* file =fopen(picture.name,"wb+");
		fputs(picture.head, file);
		for(int i = 0; i<picture.w * picture.h;i++)
		{
			fputc(picture.pixels[i].b,file);
			fputc(picture.pixels[i].g,file);
			fputc(picture.pixels[i].r,file);
		}
		free(picture.head);
		free(picture.pixels);
		fclose(file);
	}


