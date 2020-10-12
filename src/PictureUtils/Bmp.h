#ifndef _BMP_H
#define _BMP_H

//General picture structure
struct Pixel
{
    unsigned char r,g,b;
};
typedef struct Pixel Pixel;

struct Picture
{
    int w,h;
    Pixel* pixels;
    //Pixels format: to go to [i,j]: pixels[w*j+i]
};
typedef struct Picture Picture;

//BMP management function
Picture* NewPicture(int w, int h);
Picture* LoadPictureBMP(const char* file);
Picture* Copy(Picture* picture);

//Pixel management function
Pixel NewPixel(unsigned char r, unsigned char v, unsigned char b);
void setPixel(Picture* picture, int i, int j, Pixel pixel);
Pixel* getPixel(Picture* picture, int w, int h);

//To free some memory
void DelPicuture(Picture*);

//Structure for loading BMP
#pragma pack(1) //turn off memory aligment
typedef int int32;
typedef short int16;
//http://www.commentcamarche.net/contents/video/format-bmp.php3

struct BMPPictureHead
{
    int32 headSize;
    int32 w;
    int32 h;
    int16 numberOfPlans;
    int16 depth;
    int32 compression;
    int32 pictureSize;
    int32 hres;
    int32 vres;
    int32 colorOnPalette;
    int32 mainColor;
};
typedef struct BMPPictureHead BMPPictureHead;

struct BMPHead
{
    char signature[2];
    int32 size;
    int32 reservedField;
    int32 offset;
    BMPPictureHead pictureHead;
};
typedef struct BMPHead BMPHead;
#endif
