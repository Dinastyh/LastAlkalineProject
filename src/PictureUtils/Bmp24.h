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
	float averageColor;
	Pixel* pixels, *origine;
};

typedef struct Picture Picture;

struct Block
{
	        int h,w,start;
};

typedef struct Block Block;
Picture newPicture(const char *fileName, char *fileNameNew);
Pixel* myPixel(Pixel* pic, int h , int w,int startw,int width);
Block* captureLine(Picture picture);
Block* captureChar(Pixel* pixels,Block block,int w);
char* changeDimensionHead(char* head,int h, int w,int offset);
void savePicture(Picture picture);
Picture blockToPicture(Block block,Picture pic);
int* browseImage(int, int, Pixel*, int, int, int);
#endif
