#ifndef PRE_PROCESS_PICTURE
#define	PRE_PROCESS_PICTURE

#include "Bmp24.h"

void blackAndWhite(Picture picture);
Pixel* resize(Pixel* pixel, int w, int h, int neww, int newh);


Pixel applyConvolutionToPixel(int w, int h, int width, int height, float* matrix, Pixel *pixels);
void applyConvolutionToPicture(Picture picture, float* matrix);
void lowPassFilter(Picture picture);
#endif
