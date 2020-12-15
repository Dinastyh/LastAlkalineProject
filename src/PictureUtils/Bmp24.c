#include <stdio.h>
#include <stdlib.h>
#include "Bmp24.h"
#include "PreProcessPicture.h"
#include "DisplayPicture.h"
int isPictureValid(const char *name)
{
		FILE *f = fopen(name, "r");
		int color = 0;
		if(fgetc(f) == 'B' && fgetc(f) == 'M')
		{
				fseek(f, 26, SEEK_CUR);
				color = fgetc(f) + fgetc(f) * 256;
				if(color == 24)
				{
						return 1;
				}
		}
		return 0;
}

Picture newPicture(const char *fileName,char *newFileName)
{
		FILE* f = fopen(fileName, "r");
		Picture picture;
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
				data[i] = fgetc(f);
			}
		fseek(f, 2, SEEK_SET);
		taille = fgetc(f) + 256 *fgetc(f) + 256 * 256 * fgetc(f)
			+ 256 * 256 * 256 * fgetc(f);
		picture.head = data;
		fseek(f,18,SEEK_SET);
		fseek(f,18,SEEK_SET);

		w = fgetc(f) + 256 *fgetc(f) + 256 * 256 * fgetc(f)
			+ 256 * 256 * 256 * fgetc(f);

		h = fgetc(f) + 256 *fgetc(f) + 256 * 256 * fgetc(f)
			+ 256 * 256 * 256 * fgetc(f);
		picture.h = h;
		picture.w = w;
		for(int i = 0; i < 4; i++)
			{
				if((taille - 54 - (h * w * 3 + h * i)) == 0)
					 picture.offset = i;
			}
		Pixel *pixels = malloc(sizeof(Pixel) * h * w);
		fseek(f,54,SEEK_SET);
		for(int j = 0; j < h; j++)
			{
				for(int i = 0; i < w; i++)
					{
						b =  fgetc(f);
						g =  fgetc(f);
						r =  fgetc(f);
						pixel.r = r;
						pixel.b = b;
						pixel.g = g;
						average += r + g + b;
						pixels[i + j * w] = pixel;
						if(i == w - 1)
						{
								fseek(f, picture.offset, SEEK_CUR);
						}
				}
		}
		picture.name = newFileName;
		picture.pixels = pixels;
		picture.origine = pixels;
		picture.averageColor = average/(h*w*3);
		return picture;
}

void pictureToArray(double *data, char* name)
{
		Picture p;
		p.name = "oke.bmp";
		FILE *f = fopen(name, "rb");
		fseek(f, 2, SEEK_SET);
		int taille = fgetc(f) + 256 *fgetc(f) + 256 * 256 * fgetc(f)
			+ 256 * 256 * 256 * fgetc(f);
		fseek(f,18,SEEK_SET);

		int w = fgetc(f) + 256 *fgetc(f) + 256 * 256 * fgetc(f)
			+ 256 * 256 * 256 * fgetc(f);

		int h = fgetc(f) + 256 *fgetc(f) + 256 * 256 * fgetc(f)
			+ 256 * 256 * 256 * fgetc(f);
		int offset = 0;
		for(int i = 0; i < 4; i++)
			{
				if((taille - 54 - (h * w * 3 + h * i)) == 0)
				{
					offset = i;
				}
			}
		char head[54];
		fseek(f, 0, SEEK_SET);
		for(size_t k = 0; k < 54; k++)
		{
				head[k] = fgetc(f);
		}

		unsigned long average = 0;
		int r, g, b;
		Pixel pixel[h * w];
		for(int i = 0; i < h; i++)
		{
				for(int j = 0; j < w; j++)
				{
						b = fgetc(f);
						g = fgetc(f);
						r = fgetc(f);
						pixel[i * w + j].r = r;
						pixel[i * w + j].b = b;
						pixel[i * w + j].g = g;
						average += r + g + b;
						if(j == w - 1)
							 fseek(f, offset, SEEK_CUR);
				}
		}
		average /= (w * h * 3);
		p.offset = offset;
		p.averageColor = (int)average;
		p.h = h;
		p.w = w;
		p.head = head;
		p.pixels = pixel;
		blackAndWhite(&p);
		resize(&p, 28, 28);
		for(size_t i = 0; i < 784; i++)
		{
				if(p.pixels[i].r == 0)
						data[i] = 1;
				else
				{
						data[i] = 0;
				}
		}
		fclose(f);
}

void savePicture(Picture *picture)
{
		FILE* file =fopen(picture->name,"wb+");
		char *offset = "";
		int w = picture->w;
		int h = picture->h;
		switch(picture->offset)
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
				fputc(picture->head[i],file);
			}

		for(int j = 0; j < h; j++)
			{
				for(int i = 0; i < w; i++)
					{	
						fputc(picture->pixels[i + j * w].b,file);
						fputc(picture->pixels[i + j * w].g,file);
						fputc(picture->pixels[i + j * w].r,file);
						if(i == w - 1)
							{
								fputs(offset, file);
							}
					}
			}
		free(picture->origine);
	//	free(picture->head);
		fclose(file);
	//	free(picture->pixels);
}

int* browseImage(int w, int h, Pixel *pixels, int width, int line, int start)
{
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
char* changeDimensionHead(char* head,int h, int w,int offset)
{
		int sizeAll = h * w * 3 + 54 + h * offset;
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
				rep[2+i] = (unsigned char) (sizeAll%256);
				rep[18+i] = (unsigned char) (width%256);
				rep[22+i] = (unsigned char) (height%256);
				sizeAll /= 256;
				height /= 256;
				width /= 256;
				i++;
			}
		return rep;
}


Tuple captureLine(Picture *picture)
{
		Block *pics = malloc(sizeof(Block) *  picture->h);
		int height = 0;
		int lines = 0;
		int width = picture->w;
		int debut = 0;
		int *intermed = browseImage(picture->w, picture->h, picture->pixels, picture->w, 1, 0);
		for(int i = 0; i < picture->h; i++)
			{
				if(intermed[i] != 0 && debut == 0)
					{
						debut = i * width;
						height = i;

					}
				if(debut != 0 && (intermed[i] == 0 || i == picture->h - 1))
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
		Tuple tuple;
		tuple.block = pics;
		tuple.length = lines;
		return tuple;
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


Tuple captureChar(Pixel* pixels,Block *block,int w)
{
		Block *pics = malloc(sizeof(Block) *  block->w);
		int height = block->h;
		int lines = 0;
		int width = 0;
		int debut = 0;
		int *intermed = browseImage(block->w, block->h, pixels, w, 0, block->start);
		for(int i = 0; i < block->w; i++)
			{
				if(intermed[i] != 0 && debut == 0)
					{
						debut = i + block->start;
						width = i;
					}
				if(debut != 0 && (intermed[i] == 0 || i == block->w - 1))
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
		Tuple tuple;
		tuple.block= pics;
		tuple.length = lines;
		return tuple;
}

Picture blockToPicture(Block *block,Picture *pic)
{
		Picture result;
		result.name = pic->name;
		result.h = block->h;
		result.w = block->w;
		result.offset = (4-((block->w*3)%4))%4;
		result.pixels = myPixel(pic->pixels, block->h,block->w, block->start, pic->w);
		result.head =  changeDimensionHead(pic->head,block->h, block->w,result.offset);
		return result;
}
Tuple captureBlock(Pixel* pixel, Block *block)
{
		Block* bck = malloc(sizeof(Block)*block->w);
		int height = block->h;
		int lines = 0;
		int width = 0;
		int color = 0;
		int debut = 0;
		int average =0;
		int i = 0;
		int l = 0;
		int *intermed = browseImage(block->w, height, pixel, block->w, 0, block->start);
		for(int j = 0; j <block->w; j++)
			{  
				if(intermed[j] != 0)
					{
						color = 1;
					}
				if(intermed[j]==0 && color == 1)
					{
						l += 1;
					}
				else if (l != 0)
					{
						average += l;
						l = 0;
						i ++;
					}
			}
		average = (int)(((float)average/(float)i)+0.5);
		color =0;
		for (int j = 0; j<block->w; j++)
			{
				if(intermed[j] != 0)
					{
						width ++;
						if(color != 1)
							{
								debut = j;
							}
						color = 1;
						i = 0;
					}
				else if(color == 1)
					{
						if (width > 0 && i>average)
							{
								Block word;
								word.w = width;
								word.h = block->h;
								word.start = debut + block->start;
								width = 0;
								bck[lines++] = word;
								color = 0;
							}
						else
							{
								width ++;
								i ++;
							}
					}
			}
		if (width != 0)
			{
				Block word;
				word.w = width;
				word.h = block->h;
				word.start = debut + block->start;
				width = 0;
				bck[lines++] = word;
			}
		Tuple tuple;
		tuple.block= bck;
		tuple.length = lines;
		return tuple;
}

void colorImage(Pixel* pix,int h ,int w, int* fw,int* sw)
{
	int b = 0;
	while (b == 0)
	{
		b = 1;
		for(int i = 0; i< h; i++)
		{
			for(int j =0; j <w ;j++)
			{
				if(pix[i*w+j].g == 0 && pix[i*w+j].b == 0 && pix[i*w+j].r == 255)
				{
					pix[i*w+j].g = 255;
			      	 	pix[i*w+j].r = 0;
					if( i>0 && pix[(i - 1) * w + j].g == 0 && pix[(i - 1) * w + j].b ==0 && pix[(i - 1) * w + j].r == 0)	
					{
						pix[(i - 1) * w + j].r = 255;
					}
					if( j>0 && pix[(i) * w + j-1].g == 0 && pix[(i) * w + j-1].b ==0 && pix[i * w + j-1].r == 0)	
					{
						pix[i  * w + j-1].r = 255;
					}
					if( i<h-1 && pix[(i + 1) * w + j].g == 0 && pix[(i + 1) * w + j].b ==0 && pix[(i + 1) * w + j].r == 0)	
					{
						pix[(i + 1) * w + j].r = 255;
					}
					if( j<w-1 && pix[i * w + j+1].g == 0 && pix[i  * w + j+1].b ==0 && pix[i  * w + j+1].r == 0)	
					{
						pix[i * w + j+1].r = 255;
					}
					b = 0;	
					if(*fw < j)
					{
						*fw = j;
					}
					if(*sw > j)
					{
						*sw = j;
					}			
				} 
			}
		}
		if (b == 0)
		{
		b = 1;
		for(int i = h-1; i>-1; i--)
		{
			for(int j =w-1; j >-1 ;j--)
			{
				if(pix[i*w+j].g == 0 && pix[i*w+j].b == 0 && pix[i*w+j].r == 255)
				{
					pix[i*w+j].g = 255;
			      	 	pix[i*w+j].r = 0;
					if( i>0 && pix[(i - 1) * w + j].g == 0 && pix[(i - 1) * w + j].b ==0 && pix[(i - 1) * w + j].r == 0)	
					{
						pix[(i - 1) * w + j].r = 255;
					}
					if( j>0 && pix[(i) * w + j-1].g == 0 && pix[(i) * w + j-1].b ==0 && pix[i * w + j-1].r == 0)	
					{
						pix[i  * w + j-1].r = 255;
					}
					if( i<h-1 && pix[(i + 1) * w + j].g == 0 && pix[(i + 1) * w + j].b ==0 && pix[(i + 1) * w + j].r == 0)	
					{
						pix[(i + 1) * w + j].r = 255;
					}
					if( j<w-1 && pix[i * w + j+1].g == 0 && pix[i  * w + j+1].b ==0 && pix[i  * w + j+1].r == 0)	
					{
						pix[i * w + j+1].r = 255;
					}
					b = 0;				
					if(*fw < j)
					{
						*fw = j;
					}
					if(*sw > j)
					{
						*sw = j;
					}
				}		
			}

		}
		}
	}

}

Picture* betterDetect(Picture *pic,int* size)
{
	*size = 0;
	int capacity = 4;
	int b = 1;
	int i = 0;
	int j = 0;
	int w;
	int startw;
	Pixel* pix = malloc(sizeof(Pixel));
	Picture* list = malloc(sizeof(Picture)*8);
	while(b == 1)
	{	
		w = 0;
		startw = pic->w;
		*size += 1;
		b=0;
		i = 0;
		j = 0;
		while (b == 0 && i < pic->h)
		{
			while(b == 0 && j<pic->w)
			{
				if(pic->pixels[i*pic->w +j].g == 0)
				{
					pic->pixels[i*pic->w +j].r = 255; 
					b = 1;
				}
				j++;
			}
			j = 0;
			i++;
		}
		if( b == 1)
		{
		 	colorImage(pic->pixels ,pic->h ,pic->w,&w,&startw);
			if(w-startw == pic->w)
			{
				return pic;
			}
			pix = malloc(sizeof(Pixel)*(pic->h)*(w-startw+1));
			for(int x = 0; x<pic->h;x++)
			{
				for(int y = 0; y <w+1-startw; y++)
				{
					if(pic->pixels[(x)*pic->w +startw+ y].g == 255 && pic->pixels[(x)*pic->w + y+startw].r == 0 && pic->pixels[(x)*pic->w + startw + y].b == 0 )
					{

						pic->pixels[(x)*pic->w + startw +y].b = 255;
						pic->pixels[(x)*pic->w + startw +y].r = 255;
						pix[x*(w+1-startw) + y].r =0;	
						pix[(x)*(w+1-startw) + y].g =0;	
						pix[(x)*(w+1-startw) + y].b =0;
					}
					else
					{
						pix[(x)*(w+1-startw) + y].r =255;	
						pix[(x)*(w+1-startw) + y].g =255;	
						pix[(x)*(w+1-startw) + y].b =255;

					}
				}
			}
			if(*size == capacity)
			{
				capacity *= 2;
				list = realloc(list,sizeof(Picture)*capacity);
			}
			list[*size-1].name = pic->name;
			list[*size-1].pixels = pix;
			list[*size-1].w = w - startw +1;
			list[*size-1].h = pic->h;
			list[*size-1].offset = (4 - (3*list[*size-1].w)%4)%4;
			list[*size-1].head = pic->head;
			list[*size-1].head =  changeDimensionHead(list[*size-1].head,list[*size-1].h, list[*size-1].w, list[*size-1].offset);
		}
	}
    free(pic->pixels);
    free(pic->head);
	return list;

}

