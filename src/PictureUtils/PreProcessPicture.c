#include <stdio.h>
#include <stdlib.h>
#include "PreProcessPicture.h"
#include <math.h>
#include "Bmp24.h"


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


void lowPassFilter(Picture picture, int line, int column)
{
		Convolution clt;
		clt.l = line;
		clt.c = column;
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

Picture rotate(Picture pic, int degree)
{
		Picture ref = pixelsToSquare(pic);
		float rotation = (float)degree / (float)(360);
		rotation *= 2 * (float)3.14;
		double middlex = ref.w/2;
		double middley = ref.h/2;
		double currentx;
		double currenty;
		Pixel blc;
		blc.r = 255;
		blc.g = 255;
		blc.b = 255;
		Pixel *p = malloc(sizeof(Pixel) * ref.h * ref.w);
		for(int k = 0; k < ref.h * ref.w; k++)
		{
				p[k] = blc;
		}
		for(double i = 0; i < ref.h; i++)
		{
				for(double j = 0; j < ref.w; j++)
				{
						currentx = cos(rotation) * (j - middlex) - sin(rotation) * (i - middley) + middlex;
						currenty = sin(rotation) * (j - middlex) - cos(rotation) * (i - middley) + middley;
						if(currentx >= 0 && currentx < ref.w && currenty >= 0 && currenty < ref.h )
								p[(int)currenty * ref.w + (int)currentx] = ref.pixels[(int)i * ref.w + (int)j];
				}
		}
		ref.pixels = p;
		return ref;
}
Picture pixelsToSquare(Picture p)
{
		int w = p.w;
		int h = p.h;
		int max = w;
		if(max<h)
			 max = h;
		max += 4 - max%4;
		Pixel *pix = malloc(sizeof(Pixel) * max * max);
		int debutx = (max - w)/2;
		int debuty = (max - h)/2;
		Pixel blc;
		blc.r = 255;
		blc.g = 255;
		blc.b = 255;
		long average = 0;
		for(int k = 0; k < max * max; k++)
		{
				pix[k] = blc;
			//	average += 255 * 3;
		}
		for(int i = 0; i < h; i++)
		{
				for(int k = 0; k < debutx; k++)
				{
						pix[(debuty + i) * max + k] = blc;
						average += 255 * 3;
				}
				for(int j = 0; j < w; j++)
				{
						pix[(debuty + i) * max + j + debutx] = p.pixels[i * w + j];
						average += p.pixels[i * w + j].r + p.pixels[i * w + j].g +  p.pixels[i * w + j].b;
				}
				for(int k = max - debutx; k < max; k++)
				{
						pix[(debuty + i) * max + k] = blc;
						average += 255 * 3;
				}
		}
		for(int k = max - debuty; k < debuty * max; k++)
		{
				pix[k] = blc;
				average += 255 * 3;
		}
		Picture resul;
		resul.w = max;
		resul.h = max;
		resul.pixels = pix;
		resul.offset = 0;
		resul.name = p.name;
		resul.head = changeDimensionHead(p.head, max, max, 0);
		resul.origine = p.origine;
		resul.averageColor = (float)average / (float)(max * max * 3);
		return resul;
}
void upContrast(Picture picture)
{
		Convolution clt;
		clt.l = 3;
		clt.c = 3;
		clt.matrix = malloc(sizeof(float) * 9);
		for(int i = 0; i < 9; i++)
		{
				clt.matrix[i] = 0;
				if(i%2 ==1)
						clt.matrix[i] = -1;
				else if(i == 4)
				{
						clt.matrix[i] = 5;
				}
		}
		applyConvolutionToPicture(picture, clt);
}
void detectEdge(Picture picture)
{
		Convolution clt;
		clt.l = 3;
		clt.c = 3;
		clt.matrix = malloc(sizeof(float) * 9);
		for(int i = 0; i < 9; i++)
		{
				clt.matrix[i] = 0;
				if(i%2 ==1)
						clt.matrix[i] = 1;
				else if(i == 4)
				{
						clt.matrix[i] = -4;
				}
		}
		applyConvolutionToPicture(picture, clt);
}
void pushBack(Picture picture)
{
		Convolution clt;
		clt.l = 3;
		clt.c = 3;
		clt.matrix = malloc(sizeof(float) * 9);
		for(int i = 0; i < 9; i++)
		{
				clt.matrix[i] = 0;
				if(i%2 ==1)
				{
						clt.matrix[i] = 1;
						if(i == 3 || i == 7)
							 clt.matrix[i] = -1;
				}
				else if(i == 4)
				{
						clt.matrix[i] = 1;
				}
				else if(i == 2)
				{
						clt.matrix[i] = 2;
				}
				else if(i == 6)
				{
						clt.matrix[i] = -2;
				}
		}
		applyConvolutionToPicture(picture, clt);
}
void strengthenEdge(Picture picture)
{
		Convolution clt;
		clt.l = 3;
		clt.c = 3;
		clt.matrix = malloc(sizeof(float) * 9);
		for(int i = 0; i < 9; i++)
		{
				clt.matrix[i] = 0;
				if(i == 4)
				{
						clt.matrix[i] = 1;
				}
				else if(i == 3)
				{
						clt.matrix[i] = -1;
				}
		}
		applyConvolutionToPicture(picture, clt);
}
