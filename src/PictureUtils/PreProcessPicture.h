#ifndef PRE_PROCESS_PICTURE
#define	PRE_PROCESS_PICTURE

#include "Bmp24.h"

void blackAndWhite(Picture picture);



Pixel applyConvolutionToPixel(int h, int w, int height, int width, float* matrix, Pixel *pixels);
void applyConvolutionToPicture(Picture picture, float* matrix);
void lowPassFilter(Picture picture);
#endif
