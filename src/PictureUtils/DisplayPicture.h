#ifndef DISPLAYPICTURE
#define DISPLAYPICTURE

#include "Bmp24.h"
void displayPicture(char *filename);
void waitKeyPressed();
void displaySegmentationPicture(char *filename);
double**** createData(Picture *p);
#endif
