#include <stdio.h>
#include <stdlib.h>
#include "Bmp24.h"
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
		int taille = 0;
		Pixel pixel;
		for(int i = 0; i < 54; i++)
		{
			data[i] = fgetc(file);
		}
		if (data[0] != 'B' || data[1] != 'M')
		{
			printf("wrong format");
			
		}
		fseek(file, 2, SEEK_SET);
		taille = fgetc(file) + 256 *fgetc(file) + 256 * 256 * fgetc(file) 
			+ 256 * 256 * 256 * fgetc(file);
		picture.head = data;
		picture.name = newfilename;
		fseek(file,18,SEEK_SET);
		fseek(file,18,SEEK_SET);
		
		w = fgetc(file) + 256 *fgetc(file) + 256 * 256 * fgetc(file) 
			+ 256 * 256 * 256 * fgetc(file);

		h = fgetc(file) + 256 *fgetc(file) + 256 * 256 * fgetc(file) 
			+ 256 * 256 * 256 * fgetc(file);
		picture.h = h;
		picture.w = w;
		for(int i = 0; i < 4; i++)
		{
			if((taille - 54 - (h * w * 3 + h * i)) == 0)
				picture.offset = i;
		}
		Pixel *pixels = malloc(sizeof(Pixel) * h * w);
		fseek(file,54,SEEK_SET);
		int i = 0;
		for(int j = 0; j < h; j++)
		{
			for(int i = 0; i < w; i++)
			{
				b =  fgetc(file);
				g =  fgetc(file);
				r =  fgetc(file); 
				pixel.r = r;
				pixel.b = b;
				pixel.g = g;
				average += r + g + b; 
				pixels[i + j * w] = pixel;
				if( i == w - 1)
				{
					fseek(file, picture.offset, SEEK_CUR);
				}
			}
		}
		picture.pixels = pixels;
		picture.origine = pixels;

		picture.averagecolor = average/(h*w*3);
		fclose(file);
		return picture;
	}

void savePicture(Picture picture)
	{
		FILE* file =fopen(picture.name,"wb+");
		char *offset = "";
		int w = picture.w;
		int h = picture.h;
		switch(picture.offset)
		{
			case 0:
				offset = "";
				break;
			case 1:
				offset = "F";
				break;
			case 2:
				offset = "0F";
				break;
			default:
				offset = "00F";
				break;
		}
		
		for(int i = 0; i<54; i++)
		{
			fputc(picture.head[i],file);
		}


		for(int j = 0; j < h; j++)
		{
			for(int i = 0; i < w; i++)
			{	
				fputc(picture.pixels[i + j * w].b,file);
				fputc(picture.pixels[i + j * w].g,file);
				fputc(picture.pixels[i + j * w].r,file);
				if(i == w - 1)
				{
					fputs(offset, file);
				}
			}

		}
//		free(picture.origine);
		free(picture.head);
		fclose(file);
	}

int* browseImage(int w, int h, Pixel *pixels, int width, int line, int start)
{
	int j = 0;

	if(line == 1)
	{
		int *intermed = calloc(h, sizeof(int));
		for(int i = 0; i < h; i++)
		{
			for(int j = 0; j < w; j++)
			{
				if(pixels[i * width + j + start].r == 0)
				{
					intermed[i]++;
				}
			}
		}
		return intermed;
	}
	int *intermed = calloc(w, sizeof(int));
	for(int i = 0; i < w; i++)
	{
		for(int j = 0; j < h; j++)
		{
			if(pixels[j * width + i + start].r == 0)
			{
				intermed[i]++;
			}
		}
	}
	
	return intermed;
}
char* ChangeDimensionHead(char* head,int h, int w,int offset)
{
	int sizeall = h * w * 3 + 54 + h * offset;
	int height = h;
	int width = w;
	int i = 0;
	char* rep = malloc(54);
	for(int i = 0; i < 54; i++)
	{
		rep[i] = head[i];
	}
	while (i <4)
	{
		rep[2+i] = (unsigned char) (sizeall%256);
		rep[18+i] = (unsigned char) (width%256);
		rep[22+i] = (unsigned char) (height%256);
		sizeall /= 256;
		height /= 256;
		width /= 256;
		i++;
	}
	return rep;
}


Block* CaptureLine(Picture picture)
{
	Block *pics = malloc(sizeof(Block) *  picture.h);
	int height = 0;
	int lines = 0;
	int width = picture.w;
	int color = 0;
	int debut = 0;
	int *intermed = browseImage(picture.w, picture.h, picture.pixels, picture.w, 1, 0);	
	for(int i = 0; i < picture.h; i++)
	{
		if(intermed[i] != 0 && debut == 0)
		{
			debut = i * width;
			height = i;

		}
		if(debut != 0 && (intermed[i] == 0 || i == picture.h - 1))
		{
			Block line;
			line.w = width;
			line.h = i - height;
		        line.start = debut;
			pics[lines++] = line;
			height = 0;
			debut = 0;
		}
	}
	return pics;
}


Pixel* myPixel (Pixel* pic, int h , int w,int startw,int width)
{
	Pixel* newPic = malloc(sizeof(Pixel)*h*w);
	for(int i = 0 ; i <h ; i++)
	{
		for (int j =0; j <w; j++)
		{
			newPic[j+i*w] = pic[j+startw+i*(width)];
		}
	}
	return newPic;
}


Block* captureChar(Pixel* pixels,Block block,int w)
{
	Block *pics = malloc(sizeof(Block) *  block.w);
        int height = block.h;
	int lines = 0;
	int width = 0;
	int color = 0;
	int debut = 0;
	int *intermed = browseImage(block.w, block.h, pixels, w, 0, block.start);
	for(int i = 0; i < block.w; i++)
	{
		if(intermed[i] != 0 && debut == 0)
		{
			debut = i + block.start;
			width = i;

		}
		if(debut != 0 && (intermed[i] == 0 || i == block.w - 1))
		{
			Block line;
			line.w = i - width;
			line.h = height;
		        line.start = debut;
			pics[lines++] = line;
			width = 0;
			debut = 0;
		}
	}
        return pics;
}

Picture blockToPicture(Block block,Picture pic)
{
	Picture result;
	result.name = pic.name;
	result.h = block.h;
	result.w = block.w;
	result.offset = (4-((block.w*3)%4))%4;
	result.pixels = myPixel(pic.pixels, block.h,block.w, block.start, pic.w);
	result.head =  ChangeDimensionHead(pic.head,block.h, block.w,result.offset);
	return result;

}
