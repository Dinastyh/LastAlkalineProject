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

char* ChangeDimensionHead(char* head,int h, int w,int offset)
{
	int sizeall = h*w*3+54+h*offset;
	int height = h;
	int width = w;
	int i = 0;
	char* heads = malloc(54);
	for (int i = 0; i <54; i++)
	{
		heads[i] = head[i];
	}

	while (sizeall >0 && i <4)
	{
		i++;
		heads[2+i] = (char) (sizeall%256);
		heads[18+i] = (char) (width%256);
		heads[22+i] = (char) (height%256);
		sizeall = sizeall/256;
		height = h/256;
		width = width/256;
	}
	return heads;
}


Picture* CaptureLine(const Picture picture)
{
	Picture *pics = malloc(sizeof(Picture)*90);
	Pixel* pixels = malloc(sizeof(Pixel)*picture.h*picture.w);
	int height =0;
	int lines =0;
	int width = picture.w;
	int color = 0;
	for (int i = 0; i < picture.h;i++)
	{
		for (int j = 0; j < width; j++)
		{
			if(color == 1)
			{
				pixels[height*width+j].r = picture.pixels[i*width + j].r;
				pixels[height*width+j].g = picture.pixels[i*width + j].r;
				pixels[height*width+j].b = picture.pixels[i*width + j].r;
			}
			else if(picture.pixels[i*width + j].r == 0 && color == 0)
			{
				j = 0;
				color = 1;
			}
		}

		if (color == 1)
		{
			height ++;
			color = 0;
		}
		else if (height >0)
		{
			
			Picture line;
			line.w = width;
			line.h = height;
			line.name = "line.bmp";
			line.pixels = pixels;
			line.head =  ChangeDimensionHead(picture.head,height, width,picture.offset);
			pics[lines] = line;
			line.offset = picture.offset;
			lines++;
			//free(pixels);
			Pixel* pixels = malloc(sizeof(Pixel)*(picture.h-i)*picture.w);
			height = 0;
		}
	}
	if (height > 0)
	{
		Picture line;
		line.w = width;
		line.h = height;
		line.name = "line.bmp";
		line.pixels = pixels;
		line.offset = picture.offset;
		line.head =  ChangeDimensionHead(picture.head,height, width,picture.offset);
		pics[lines] = line;
		//free(pixels);
	}
	return pics;
}
                      
