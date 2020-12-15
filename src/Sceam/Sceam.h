#ifndef SCEAM
#define SCEAM
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../PictureUtils/Bmp24.h"
long min2(long l1, long l2);
long min3(long l1, long l2, long l3);
long dualGradientEnergy(Pixel* p1x, Pixel* p2x, Pixel* p1y, Pixel* p2y);
long **generateEnergyMatrix(Picture* p);
long **generateSeamEnergies(int h, int w, long **energyMatrix);
int *determineMinSeam(int h, int w, long **dp);
void sceamReduceW(Picture* p, int newW);
#endif