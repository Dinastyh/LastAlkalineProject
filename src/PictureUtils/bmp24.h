#ifndef H_GL_BMP24
#define H_GL_BMP24

struct Pixel
{
	int r,g,b;
};

typedef struct Pixel Pixel;

struct Picture
{
	int h,w;
	char *name, *head;
	float averagecolor;
	Pixel* pixels;
};

typedef struct Picture Picture;

Picture newPicture(const char *filename, char *filenamenew);
void BlackAndWhite(Picture picture);
void savePicture(Picture picture);
#endif
