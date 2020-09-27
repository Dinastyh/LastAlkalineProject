#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Bmp.h"

Picture* NewPicture(int w, int h)
{
    Picture* picture = malloc(sizeof(Picture));
    picture ->w = w;
    picture ->h = h;
    //Using Calloc for init all memory case to 0
    picture ->pixels = calloc(w*h,sizeof(Pixel*));
    return picture;
}

void DelPicture(Picture* picture)
{
    if(picture)
    {
        free(picture->pixels);
        free(picture);
    }
}

Pixel NewPixel(unsigned char r, unsigned char g, unsigned char b)
{
    Pixel pixel;
    pixel.r = r;
    pixel.g = g;
    pixel.b = b;
    return pixel;
}

void setPixel(Picture* picture, int i, int j, Pixel pixel)
{
    if(picture && i>= 0 && i< picture->w && j>=0 && j< picture->h)
        picture->pixels[picture->w*j+i]=pixel;
}

Pixel* getPixel(Picture* picture, int i, int j)
{
    if(picture && i>=0 && i< picture->w && j>=0 && j< picture->h)
        return &picture->pixels[picture->w*j+i];
}

Picture* LoadPicture(const char* file)
{
    Picture* picture;
    Pixel pixel;
    BMPHead bmpHead;
    unsigned char dataPixel[3];
    FILE* fileO = fopen(file, "rb");
    if(!fileO)
        return NULL; //File not found
    fread(&bmpHead, sizeof(BMPHead),1,fileO);
    if(bmpHead.signature[0] != 'B' || bmpHead.signature[1] != 'M')
        return NULL;
    BMPPictureHead pictureHead = bmpHead.pictureHead;
    if(pictureHead.depth != 24 || pictureHead.compression !=0 || pictureHead.colorOnPalette != 0
        || pictureHead.mainColor !=0)
        return NULL;
    picture = NewPicture(pictureHead.w, pictureHead.h);
    int memoryCorrection = (3*pictureHead.w)%4;
    switch(memoryCorrection)
    {
        case 0:
            memoryCorrection = 0;
            break;
        case 1:
            memoryCorrection = 3;
            break;
        case 2:
            memoryCorrection = 2;
            break;
        default:
            memoryCorrection = 1;
            break;
    }
    for(int i = 0; i<picture->w; i++)
    {
        for(int j=0; j<picture->h; j++)
        {
            fread(&dataPixel,1,2,fileO);
            pixel.b = dataPixel[0];
            pixel.g = dataPixel[1];
            pixel.r = dataPixel[2];
            setPixel(picture, i, picture->h-j-1,pixel); //Caution in BMP pixel are save from bottom to top
        }
        fread(&dataPixel, 1, memoryCorrection, fileO); //To set the correct memory
    }
    fclose(fileO);
    return picture;
}


