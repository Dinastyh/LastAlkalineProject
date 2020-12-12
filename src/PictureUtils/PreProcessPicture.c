#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "PreProcessPicture.h"


void blackAndWhite(Picture *picture)
{
	printf("YEETTTT\n");
    float color;
		upContrast(picture);
		for(int i = 0; i < picture->h * picture->w; i++)
    {
        color =((float)picture->pixels[i].r +
                (float)picture->pixels[i].g +
                (float)picture->pixels[i].b) / (float)3;
        if(color > picture->averageColor)
        {
            picture->pixels[i].r = 255;
            picture->pixels[i].g = 255;
            picture->pixels[i].b = 255;
        }
        else
        {
            picture->pixels[i].r = 0;
            picture->pixels[i].b = 0;
            picture->pixels[i].g = 0;
        }
    }
}
Pixel applyConvolutionToPixel(int w, int h, int width, int height, Convolution clt, Pixel* pixels)
{
    float *matrix = clt.matrix;
    int line = clt.l;
    int column = clt.c;
    double r = 0;
    double g = 0;
    double b = 0;
    Pixel pixel;
    int currentL;
    int currentC;
    int milieuMatrix = clt.l / 2;
    float inter;
    for(int l = 0; l < line; l++)
    {
        for(int c = 0; c < column; c++)
        {
            currentL = l + h - milieuMatrix;
            currentC = c + w - milieuMatrix;
            if(currentL >= 0 && currentL < height)
            {
                if(currentC >= 0 && currentC < width)
                {
                    inter = matrix[l * column + c];
                    r += inter * pixels[currentL * width + currentC].r;
                    b += inter * pixels[currentL * width + currentC].b;
                    g += inter * pixels[currentL * width + currentC].g;
                }
            }
        }
    }
    pixel.r = (int)r;
    pixel.g = (int)g;
    pixel.b = (int)b;
    return pixel;
}

void applyConvolutionToPicture(Picture *picture, Convolution clt)
{
    Pixel inter;
    inter.r = 0;
    inter.g = 0;
    inter.b = 0;
    Pixel *convoluted = myPixel(picture->pixels, picture->h, picture->w, 0, picture->w);
    for(int h = 0; h < picture->h; h++)
    {
        for(int w = 0; w < picture->w; w++)
        {
            inter = applyConvolutionToPixel(w, h, picture->w, picture->h, clt, convoluted);
            picture->pixels[h * picture->w + w].r = inter.r;
            picture->pixels[h * picture->w + w].b = inter.b;
            picture->pixels[h * picture->w + w].g = inter.g;
        }
    }
    free(convoluted);
}


void lowPassFilter(Picture *picture, int line, int column)
{
    Convolution clt;
    clt.l = line;
    clt.c = column;
    float normalize = (float)clt.l * (float)clt.c;
    clt.matrix = malloc(sizeof(float) * clt.l * clt.c);
    for(int i = 0; i < clt.l; i++)
    {
        for(int j = 0; j < clt.c; j++)
        {
            clt.matrix[i * clt.c + j] = 1.0f/normalize;
        }
    }
    applyConvolutionToPicture(picture, clt);
}

void resize(Picture *p, int neww, int newh)
{

    *p = pixelsToSquare(*p);
    double hf = (double) p->h;
    double wf = (double) p->w;
    double nhf =(double) newh;
    double nwf =(double) neww;
    Pixel *result = malloc(sizeof(Pixel)*neww*newh);
    double plusx = wf/nwf;
    double plusy = hf/nhf;
    int j = 0;
    int i = 0;
    double x1 = 0;
    double  x2 = 1.0;
    double y1 = 0;
    double y2= 1.0;
    double color;
    double average = 0;
    while(j <newh)
    {
        while(i < neww)
        {
		color = ((double) p->pixels[(int)x1 * p->w + (int)y1].g)*(x1 - x2 +1.0)*(y1 -  y2 + 1.0);
		color += ((double) p->pixels[(int)x2 * p->w + (int)y1].g)*(-x1 +  x2)*(y1 -  y2 + 1.0);
		color += ((double) p->pixels[(int)x2 * p->w + (int)y2].g)*(-x1 +  x2)*(-y1 +  y2);
		color += ((double) p->pixels[(int)x1 * p->w +(int) y2].g)*(x1 - x2 +1.0)*(-y1 + y2);

		result[i*neww + j].r = (int) color;
		result[i*neww + j].g = (int) color;
		result[i*neww + j].b = (int) color;
		if(color != 0.0 && (int)color != 255)
		{
			printf("x1 = %f,x2 = %f,y1= %f,y2= %f, color =%f\n",x1,x2,y1,y2,color);
		}
		average += color;
            x1 += plusx;
	    if( x1 > x2)
	    {
		    x2 = (float)((int) x1) +1.0;
		    if(x2 == p->w)
		    {
			    x2 --;
		    }
	    }
            i++;

        }
        y1 += plusy;
        x1= 0;
	x2 = 1.0;
        j ++;
        i = 0; 
	if( y1 > y2)
	    {
		    y2 = (float)((int)y1) +1.0; 
		    if(y2 == p->h)
		    {
			    y2 --;
		    }

	    }

    }
        free(p->pixels);
 p->head = changeDimensionHead(p->head, newh, neww, (4-(neww*newh*3)%4)%4);
 p->h = newh;
 p->w = neww;
 p->pixels = result;
 p->averageColor = average/ (float)(neww * newh);
 blackAndWhite(p);
}

Picture rotate(Picture pic, int degree)
{
    Picture ref = pixelsToSquare(pic);
    float rotation = (float)degree / (float)(360);
    rotation *= 2 * (float)3.14;
    double middlex = ref.w/2;
    double middley = ref.h/2;
    double currentx;
    double currenty;
    Pixel blc;
    blc.r = 255;
    blc.g = 255;
    blc.b = 255;
    Pixel *p = malloc(sizeof(Pixel) * ref.h * ref.w);
    for(int k = 0; k < ref.h * ref.w; k++)
    {
        p[k] = blc;
    }
    for(double i = 0; i < ref.h; i++)
    {
        for(double j = 0; j < ref.w; j++)
        {
            currentx = cos(rotation) * (j - middlex) - sin(rotation) * (i - middley) + middlex;
            currenty = sin(rotation) * (j - middlex) - cos(rotation) * (i - middley) + middley;
            if(currentx >= 0 && currentx < ref.w && currenty >= 0 && currenty < ref.h )
                p[(int)currenty * ref.w + (int)currentx] = ref.pixels[(int)i * ref.w + (int)j];
        }
    }
    ref.pixels = p;
    return ref;
}
Picture pixelsToSquare(Picture p)
{
    int w = p.w;
    int h = p.h;
    int max = w;
    if(max<h)
        max = h;
    max += 4 - max%4;
    Pixel *pix = malloc(sizeof(Pixel) * max * max);
    int debutx = (max - w)/2;
    int debuty = (max - h)/2;
    Pixel blc;
    blc.r = 255;
    blc.g = 255;
    blc.b = 255;
    long average = 0;
    for(int k = 0; k < max * max; k++)
    {
        pix[k] = blc;
        average += 255 * 3;
    }
    for(int i = 0; i < h; i++)
    {
        for(int k = 0; k < debutx; k++)
        {
            pix[(debuty + i) * max + k] = blc;
            average += 255 * 3;
        }
        for(int j = 0; j < w; j++)
        {
            pix[(debuty + i) * max + j + debutx] = p.pixels[i * w + j];
            average += p.pixels[i * w + j].r + p.pixels[i * w + j].g +  p.pixels[i * w + j].b;
        }
        for(int k = max - debutx; k < max; k++)
        {
            pix[(debuty + i) * max + k] = blc;
            average += 255 * 3;
        }
    }
    for(int k = max - debuty; k < debuty * max; k++)
    {
        pix[k] = blc;
        average += 255 * 3;
    }
    Picture resul;
    resul.w = max;
    resul.h = max;
    resul.pixels = pix;
    resul.offset = 0;
    resul.name = p.name;
    resul.head = changeDimensionHead(p.head, max, max, 0);
    resul.origine = p.origine;
    resul.averageColor = (float)average / (float)(max * max * 3);
    return resul;
}
void upContrast(Picture *picture)
{
    Convolution clt;
    clt.l = 3;
    clt.c = 3;
    clt.matrix = malloc(sizeof(float) * 9);
    for(int i = 0; i < 9; i++)
    {
        clt.matrix[i] = 0;
        if(i%2 ==1)
            clt.matrix[i] = -1;
        else if(i == 4)
        {
            clt.matrix[i] = 5;
        }
    }
    applyConvolutionToPicture(picture, clt);
}
void detectEdge(Picture *picture)
{
    Convolution clt;
    clt.l = 3;
    clt.c = 3;
    clt.matrix = malloc(sizeof(float) * 9);
    for(int i = 0; i < 9; i++)
    {
        clt.matrix[i] = 0;
        if(i%2 ==1)
            clt.matrix[i] = 1;
        else if(i == 4)
        {
            clt.matrix[i] = -4;
        }
    }
    applyConvolutionToPicture(picture, clt);
}
void pushBack(Picture *picture)
{
    Convolution clt;
    clt.l = 3;
    clt.c = 3;
    clt.matrix = malloc(sizeof(float) * 9);
    for(int i = 0; i < 9; i++)
    {
        clt.matrix[i] = 0;
        if(i%2 ==1)
        {
            clt.matrix[i] = 1;
            if(i == 3 || i == 7)
                clt.matrix[i] = -1;
        }
        else if(i == 4)
        {
            clt.matrix[i] = 1;
        }
        else if(i == 2)
        {
            clt.matrix[i] = 2;
        }
        else if(i == 6)
        {
            clt.matrix[i] = -2;
        }
    }
    applyConvolutionToPicture(picture, clt);
}
void strengthenEdge(Picture *picture)
{
    Convolution clt;
    clt.l = 3;
    clt.c = 3;
    clt.matrix = malloc(sizeof(float) * 9);
    for(int i = 0; i < 9; i++)
    {
        clt.matrix[i] = 0;
        if(i == 4)
        {
            clt.matrix[i] = 1;
        }
        else if(i == 3)
        {
            clt.matrix[i] = -1;
        }
    }
    applyConvolutionToPicture(picture, clt);
}
void denoizing(Picture *p)
{
    double* mask = malloc(sizeof(double)* 9);
    mask[0] = (double)1/(double)16;
    mask[1] = (double)2/(double)16;
    mask[2] = (double)1/(double)16;
    mask[3] = (double)2/(double)16;
    mask[4] = (double)4/(double)16;
    mask[5] = (double)2/(double)16;
    mask[6] = (double)1/(double)16;
    mask[7] = (double)2/(double)16;
    mask[8] = (double)1/(double)16;
    int w = p->w;
    Pixel* ia = p->pixels;
    int h = p->h;
    Pixel inter;
    Pixel *autre = myPixel(ia, h, w, 0, w);
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            inter =  denoizingMedianWeight(mask, autre, j , i, w, h);
            ia[i * w + j].r = inter.r;
            ia[i * w + j].b = inter.b;
            ia[i * w + j].g = inter.g;
        }
    }
    free(autre);
}
Pixel denoizingMedianWeight(double *m1, Pixel *m2, int w, int h, int width, int height)
{
    int currentX;
    int currentY;
    double median[9];
    Pixel matrixOfPixels[9];
    Pixel interP;
    for(int i = 0; i < 3; i++)
    {
        currentY = h + i - 1;
        for(int j = 0; j < 3; j++)
        {
            currentX = w + j - 1;
            if(currentX > -1 && currentX < width && currentY > -1 && currentY < height)
            {
                interP = m2[currentY * width + currentX];
                matrixOfPixels[i * 3 + j] = interP;
                median[i * 3 + j] = ((double)interP.r + (double)interP.g + (double)interP.b) * m1[i * 3 + j];
            }
        }
    }
    int aud = 0;
    int end = 0;
    double current;
    int currentIndex = 0;
    while(!((aud == 4 && end == 4) || (aud == 5 && end == 4)) && currentIndex < 10)
    {
        current = median[currentIndex];
        aud = 0;
        end = 0;
        for(int k = 0; k < 9; k++)
        {
            if(k != currentIndex)
            {
                if(current > median[k])
                    end++;
                else
                    aud++;
            }
        }
        currentIndex++;
    }
    Pixel x = matrixOfPixels[currentIndex - 1];
    x.r = (int)((double)x.r * m1[currentIndex - 1]);
    x.g = (int)((double)x.g * m1[currentIndex - 1]);
    x.b = (int)((double)x.b * m1[currentIndex - 1]);
    if(x.r > 255)
        x.r = 255;
    if(x.b > 255)
        x.b = 255;
    if(x.g > 255)
        x.g = 255;
    return x;
}
void grayscale(Picture *p)
{
		int gray;
		Pixel pix;
		for(int i = 0; i < p->h; i++)
		{
				for(int j = 0; j < p->w; j++)
				{
						pix = p->pixels[i * p->w + j];
						gray = pix.r + pix.g + pix.b;
						pix.r = gray;
						pix.b = gray;
						pix.g = gray;
						p->pixels[i * p->w + j] = pix;
				}
		}
}
void grayscaleLuminate(Picture *p)
{
		int gray;
		Pixel pix;
		for(int i = 0; i < p->h; i++)
		{
				for(int j = 0; j < p->w; j++)
				{
						pix = p->pixels[i * p->w + j];
						gray = (int)((float)pix.r * 0.2627f + (float)pix.g * 0.6780f + (float)pix.b * 0.0593f);
						pix.r = gray;
						pix.b = gray;
						pix.g = gray;
						p->pixels[i * p->w + j] = pix;
				}
		}
}
void invert(Picture *p)
{
		Pixel pix;
		for(int i = 0; i < p->h; i++)
		{
				for(int j = 0; j < p->w; j++)
				{
						pix = p->pixels[i * p->w + j];
						pix.r -= 255;
						pix.b -= 255;
						pix.g -= 255;
						p->pixels[i * p->w + j] = pix;
				}
		}
}
