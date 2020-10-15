#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>


int main(int argv, char *argc[])
{
	FILE *image = NULL, *image_grey = NULL;
	image = fopen("image2.bmp", "rb");
	image_grey = fopen("image2grey.bmp", "wb");


	if(image == NULL)
	{
		printf("File not found");
	}
	if((int)fgetc(image) !=  66 || (int)fgetc(image) != 77)
	{
		printf("Not a Bitmap");
	}
	fseek(image, 8, SEEK_CUR);
	int offset = (int)fgetc(image) + 256 *(int)fgetc(image) + 256 * 256 * (int)fgetc(image) + 256 * 256 * 256 * (int)fgetc(image);

	fseek(image, 4, SEEK_CUR);

	int width = (int)fgetc(image) + 256 *(int)fgetc(image) + 256 * 256 * (int)fgetc(image) + 256 * 256 * 256 * (int)fgetc(image);
	
	int height = (int)fgetc(image) + 256 *(int)fgetc(image) + 256 * 256 * (int)fgetc(image) + 256 * 256 * 256 * (int)fgetc(image);

	fseek(image, 2, SEEK_CUR);

	int bpp = fgetc(image) + 256 * fgetc(image);
	fseek(image, 0, SEEK_SET);
	for(int i = 0; i < 54; i++)
	{
		fputc(fgetc(image),image_grey);
	}
	int g = 0;
	int b = 0;
	int r = 0;
	int grey = 0;
	for(int i = 0; i < width * height * 3; i++)
	{
		b = fgetc(image);
		g = fgetc(image);
		r = fgetc(image);
		grey = ( r + g + b) / 3;
		fputc(grey,image_grey);
		fputc(grey,image_grey);
		fputc(grey,image_grey);
		printf(" I : %d\n", i);

	}


	fclose(image_grey);
	fclose(image);
	return 0;
}
