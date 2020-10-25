#include <stdio.h>
#include <stdlib.h>
#include "PreProcessPicture.h"



void blackAndWhite(Picture picture)
{
		float color;
		for(int i = 0; i < picture.h * picture.w; i++)
		{
				color =((float)picture.pixels[i].r +
								(float)picture.pixels[i].g +
								(float)picture.pixels[i].b) / 3;
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
Pixel applyConvolutionToPixel(int w, int h, int width, int height, Convolution clt, Pixel* pixels)
{
		float *matrix = clt.matrix;
		int line = clt.l;
		int column = clt.c;
		double r = 0;
		double g = 0;
		double b = 0;
		Pixel pixel;
		int currentL;
	  int currentC;
		int milieuMatrix = clt.l / 2;
		float inter;
		for(size_t l = 0; l < line; l++)
		{
				for(size_t c = 0; c < column; c++)
				{
						currentL = l + h - milieuMatrix;
						currentC = c + w - milieuMatrix;
						if(currentL >= 0 && currentL < height)
						{
								if(currentC >= 0 && currentC < width)
								{
										inter = matrix[l * column + c];
										r += inter * pixels[currentL * width + currentC].r;
										b += inter * pixels[currentL * width + currentC].b;
										g += inter * pixels[currentL * width + currentC].g;
								}
						}
				}
		}
		pixel.r = (int)r;
		pixel.g = (int)g;
		pixel.b = (int)b;
		return pixel;
}

void applyConvolutionToPicture(Picture picture, Convolution clt)
{
		Pixel inter;
		inter.r = 0;
		inter.g = 0;
		inter.b = 0;
		Pixel *convoluted = myPixel(picture.pixels, picture.h, picture.w, 0, picture.w);
		for(size_t h = 0; h < picture.h; h++)
		{
				for(size_t w = 0; w < picture.w; w++)
				{
						inter = applyConvolutionToPixel(w, h, picture.w, picture.h, clt, convoluted);
						picture.pixels[h * picture.w + w].r = inter.r;
						picture.pixels[h * picture.w + w].b = inter.b;
						picture.pixels[h * picture.w + w].g = inter.g;
				}
		}
		free(convoluted);
}


void lowPassFilter(Picture picture)
{
		Convolution clt;
		clt.l = 5;
		clt.c = 5;
		float normalize = (float)clt.l * (float)clt.c;
		clt.matrix = malloc(sizeof(float) * clt.l * clt.c);
		for(size_t i = 0; i < clt.l; i++)
		{
				for(size_t j = 0; j < clt.c; j++)
				{
						clt.matrix[i * clt.c + j] = 1.0f/normalize;
				}
		}
		applyConvolutionToPicture(picture, clt);
}


Pixel* resize(Pixel* pixel,int w, int h, int neww, int newh)
{
		Pixel* result = malloc(sizeof(Pixel) * newh * neww);
		double hf = (double) h;
		double wf = (double) w;
		double nhf =(double) newh;
		double nwf =(double) neww;
		double x = 0;
		double y = 0;
		double plusx = wf/nwf;
		double plusy = hf/nhf;
		for(int j = 0; j < newh; j++)
		{
			for(int i = 0; i < neww; i++)
				{
					
					result[i + j * neww] = pixel[((int)x)+((int)y)*w ];
					x += plusx;
				}
			y += plusy;
			x= 0;
		}
		return result;
}




