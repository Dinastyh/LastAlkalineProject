#ifndef PRE_PROCESS_PICTURE
#define	PRE_PROCESS_PICTURE

#include "Bmp24.h"

struct Convolution
{
		float *matrix;
		int l, c;
};
typedef struct Convolution Convolution;

void blackAndWhite(Picture* picture);
void resize(Picture* p, int neww, int newh);

Pixel applyConvolutionToPixel(int w, int h, int width, int height, Convolution matrix, Pixel *pixels);
void applyConvolutionToPicture(Picture *picture, Convolution matrix);
void lowPassFilter(Picture *picture, int line, int column);
void strengthenEdge(Picture *picture);
void pushBack(Picture *picture);
void detectEdge(Picture *picture);
void upContrast(Picture *picture);
Picture rotate(Picture picture, int degree);
Picture pixelsToSquare(Picture p);
void denoizing(Picture *p);
Pixel denoizingMedianWeight(double *m1, Pixel *m2, int w, int h, int width, int height);
void grayscale(Picture *p);
void grayscaleLuminate(Picture *p);
void invert(Picture *p);
double sumRGBPixel(Pixel *p);
double varianceP(Picture *p);

Picture detectionAngle(Picture pic, Tuple* l,int);
float variance(Picture pic, Tuple l);
Picture invertDetection(Picture pic1, Picture pic2, Tuple l1, Tuple l2);
void detecAngle(Picture *picture);
#endif
