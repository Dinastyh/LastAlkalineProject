#include <stdio.h>
#include <stdlib.h>
#include "PreProcessPicture.h"



void blackAndWhite(Picture picture)
{
	float color;
	for(int i = 0; i < picture.h * picture.w; i++)
	{
		color = (float)picture.pixels[i].r +	
			(float)picture.pixels[i].g +
			(float)picture.pixels[i].b / 3;
		if(color > picture.averageColor)
		{
			picture.pixels[i].r = 255;
			picture.pixels[i].g = 255;
			picture.pixels[i].b = 255;
		}
		else
		{
			picture.pixels[i].r = 0;
			picture.pixels[i].b = 0;
			picture.pixels[i].g = 0;
		}
	}
}
Pixel applyConvolutionToPixel(int w, int h, int width, int height, float* matrix, Pixel* pixels)
{
	double r = 0;
	double g = 0;
	double b = 0;
	Pixel pixel;
	float intermed;
	for(size_t line = 0; line < 3; line++)
	{	
		for(size_t column = 0; column < 3; column++)
		{
			if(h > 0 && h < height - 1)
			{
				if(w > 0 && w < width - 1)
				{
					intermed = matrix[line * 3 + column];
					r += intermed * pixels[(h + line - 1) * width + w + (column - 1)].r;
					b += intermed * pixels[(h + line - 1) * width + w + (column - 1)].b;
					g += intermed * pixels[(h + line - 1) * width + w + (column - 1)].g;	
				}
				else if(w == width - 1 && column < 2)
				{
					intermed = matrix[line * 3 + column];
					r += intermed * pixels[(h + line - 1) * width + w + (column - 1)].r;
					b += intermed * pixels[(h + line - 1) * width + w + (column - 1)].b;
					g += intermed * pixels[(h + line - 1) * width + w + (column - 1)].g;
				}
				else if(w == 0 && column > 0)
				{
					intermed = matrix[line * 3 + column];
					r += intermed * pixels[(h + line - 1) * width + w + (column - 1)].r;
					b += intermed * pixels[(h + line - 1) * width + w + (column - 1)].b;
					g += intermed * pixels[(h + line - 1) * width + w + (column - 1)].g;
				}

			}
			else if(h == height - 1 && line < 2)
			{
				if(w > 0 && w < width - 1)
				{
					intermed = matrix[line * 3 + column];
					r += intermed * pixels[(h + line - 1) * width + w + (column - 1)].r;
					b += intermed * pixels[(h + line - 1) * width + w + (column - 1)].b;
					g += intermed * pixels[(h + line - 1) * width + w + (column - 1)].g;	
				}
				else if(w == width - 1 && column < 2)
				{
					intermed = matrix[line * 3 + column];
					r += intermed * pixels[(h + line - 1) * width + w + (column - 1)].r;
					b += intermed * pixels[(h + line - 1) * width + w + (column - 1)].b;
					g += intermed * pixels[(h + line - 1) * width + w + (column - 1)].g;
				}
				else if(w == 0 && column > 0)
				{
					intermed = matrix[line * 3 + column];
					r += intermed * pixels[(h + line - 1) * width + w + (column - 1)].r;
					b += intermed * pixels[(h + line - 1) * width + w + (column - 1)].b;
					g += intermed * pixels[(h + line - 1) * width + w + (column - 1)].g;
				}
			}
			else if(h == 0 && line > 0)
			{
				if(w > 0 && w < width - 1)
				{
					intermed = matrix[line * 3 + column];
					r += intermed * pixels[(h + line - 1) * width + w + (column - 1)].r;
					b += intermed * pixels[(h + line - 1) * width + w + (column - 1)].b;
					g += intermed * pixels[(h + line - 1) * width + w + (column - 1)].g;	
				}
				else if(w == width - 1 && column < 2)
				{ 
					intermed = matrix[line * 3 + column];
					r += intermed * pixels[(h + line - 1) * width + w + (column - 1)].r;
					b += intermed * pixels[(h + line - 1) * width + w + (column - 1)].b;
					g += intermed * pixels[(h + line - 1) * width + w + (column - 1)].g;
				}
				else if(w == 0 && column > 0)
				{
					intermed = matrix[line * 3 + column];
					r += intermed * pixels[(h + line - 1) * width + w + (column - 1)].r;
					b += intermed * pixels[(h + line - 1) * width + w + (column - 1)].b;
					g += intermed * pixels[(h + line - 1) * width + w + (column - 1)].g;
				}
			}
		}

	}
	pixel.r = (int)r;
	pixel.g = (int)g;
	pixel.b = (int)b;
	return pixel;
}

void applyConvolutionToPicture(Picture picture, float* matrix)
{
	Pixel intermed;
	intermed.r = 0;
	intermed.g = 0;
	intermed.b = 0;
	Pixel *convoluted = myPixel(picture.pixels, picture.h, picture.w, 0, picture.w);
	for(size_t h = 0; h < picture.h; h++)
	{
		for(size_t w = 0; w < picture.w; w++)
		{
			intermed = applyConvolutionToPixel(w, h, picture.w, picture.h, matrix, convoluted);
			picture.pixels[h * picture.w + w].r = intermed.r;
		       	picture.pixels[h * picture.w + w].b = intermed.b;
		       	picture.pixels[h * picture.w + w].g = intermed.g; 
		}
	}
	free(convoluted);
}


void lowPassFilter(Picture picture)
{ 
	float* matrix = malloc(sizeof(float) * 9);
	for(size_t i = 0; i < 9; i++)
	{
		matrix[i] = 1.0/9.0;
	}
	applyConvolutionToPicture(picture, matrix);
}


Pixel* resize(Pixel* pixel,int w, int h, int neww, int newh)
{
	Pixel* result = malloc(sizeof(pixel) * h * w);
	for(int j = 0; j < newh; j++)
	{
		for(int i = 0; i < newh; i++)
		{
			result[i+j*newh] = pixel[i * (w / neww) + j*(h / newh) * h];
		}
	}
	return result;
}




