#ifndef H_GL_BMP24
#define H_GL_BMP24

struct Pixel
{
	int r,g,b;
};

typedef struct Pixel Pixel;

struct Picture
{
	int h, w, offset;
	char *name, *head;
	float averagecolor;
	Pixel* pixels, *origine;
};

typedef struct Picture Picture;

Picture newPicture(const char *filename, char *filenamenew);
void BlackAndWhite(Picture picture);
Pixel* myPixel(Pixel* pic, int h , int w,int startw,int width);
Picture* CaptureLine(const Picture picture);
Picture* captureChar(const Picture picture);
char* ChangeDimensionHead(char* head,int h, int w,int offset);
void savePicture(Picture picture);
#endif
