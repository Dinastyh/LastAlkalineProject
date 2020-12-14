#ifndef DISPLAYPICTURE
#define DISPLAYPICTURE

#include "Bmp24.h"
void displayPicture(char *filename);
void waitKeyPressed();
void displaySegmentationPicture(char *filename);
Data createData(Picture *p);
void create66Picture();
char incrementerString(char* string, size_t *len);
#endif
