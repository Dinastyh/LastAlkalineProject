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

struct Tuple
{
		Block *block;
		int length;
};
typedef struct Tuple Tuple;

struct Data
{
		void *thing;
		int length;
};
typedef struct Data Data;

int isPictureValid(const char *name);
Picture newPicture(const char *fileName, char *fileNameNew);
void pictureToArray(double* data, char* filename);
void savePicture(Picture *picture);
Picture bmp24ToPicture(FILE* f);
Picture pngToPicture(FILE* f);

void colorImage(Pixel* pix, int h, int w,int*,int*);
Picture* betterDetect(Picture *pic,int* size);

Pixel* myPixel(Pixel* pic, int h , int w,int startw,int width);
Tuple captureLine(Picture *picture);
Tuple captureBlock(Pixel* pixel, Block *block);
Tuple captureChar(Pixel* pixels,Block *block,int w);
char* changeDimensionHead(char* head,int h, int w,int offset);
Picture blockToPicture(Block *block,Picture *pic);
int* browseImage(int, int, Pixel*, int, int, int);
#endif
