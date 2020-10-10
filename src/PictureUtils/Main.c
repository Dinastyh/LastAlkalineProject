#include <stdlib.h>
#include <stdio.h>
#include "bmp24.h"
int main(int argc, char* argv[])
{
	printf("ok\n");
	Picture cobaye = newPicture("image.bmp","essai.bmp");
	printf("w : %d, h : %d\n",cobaye.w, cobaye.h);
	savePicture(cobaye);
	return 0;
}
