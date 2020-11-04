#ifndef PRE_PROCESS_PICTURE
#define	PRE_PROCESS_PICTURE

#include "Bmp24.h"

struct Convolution
{
		float *matrix;
		int l, c;
};
typedef struct Convolution Convolution;



void blackAndWhite(Picture picture);
Pixel* resize(Pixel* pixel, int w, int h, int neww, int newh);


Pixel applyConvolutionToPixel(int w, int h, int width, int height, Convolution matrix, Pixel *pixels);
void applyConvolutionToPicture(Picture picture, Convolution matrix);
void lowPassFilter(Picture picture);
#endif
