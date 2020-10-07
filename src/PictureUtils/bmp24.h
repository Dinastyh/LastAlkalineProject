#include <stdio.h>


struct Pixel
{
	int r,g,b;
};

typedef struct Pixel Pixel;

struct Picture
{
	int h,w;
	char* name,head;
	double averagecolor;
	Pixel* pixels;
};

typedef struct Picture Picture;

Picture newPicture( const char* filename, const char* filenamenew);
void savePicture(Picture picture);
