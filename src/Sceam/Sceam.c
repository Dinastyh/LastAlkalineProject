#include "Sceam.h"

long min2(long l1, long l2) {
	if (l1 < l2)
		return l1;
	return l2;
}

long min3(long l1, long l2, long l3) {
	return min2(l1, min2(l2, l3));
}

long dualGradientEnergy(Pixel* p1x, Pixel* p2x, Pixel* p1y, Pixel* p2y)
{
    Pixel xdif;
    pixel xdif;
	xdif.r = abs(p1x->r - p2x->r);
	xdif.g = abs(p1x->g - p2x->g);
	xdif.b = abs(p1x->b - p2x->b);

	Pixel ydif;
	ydif.r = abs(p1y->r - p2y->r);
	ydif.g = abs(p1y->g - p2y->g);
	ydif.b = abs(p1y->b - p2y->b);

    long xgrad = xdif.r * xdif.r + xdif.g * xdif.g + xdif.b * xdif.b;
	long ygrad = ydif.r * ydif.r + ydif.g * ydif.g + ydif.b * ydif.b;

	return xgrad + ygrad;
}

long **generateEnergyMatrix(Picture* p) {
	
    int h = p->h;
    int w = p->w;
    Pixel* colorMat = p->pixels;
	long **energyMatrix = malloc(h * sizeof(long *));
	for (int i = 0; i < h; i++)
		energyMatrix[i] = malloc(w * sizeof(long));

	for (int i = 0; i < h; i++)
		for (j = 0; j < w; j++) {
			long energy;
			/* 
			Corner
			*/
			if (i == 0 && j == 0) {
				energy = ->dualGradientEnergy(colorMat[i*h+w-1], colorMat[i*h+j+1], colorMat[h - 1][(h-1)*h+j], colorMat[(i+1)*h+j]);
			}
			else if (i == 0 && j == w - 1)
				energy = ->dualGradientEnergy(colorMat[i*h+j - 1], colorMat[i*h], colorMat[(h-1)*h+j], colorMat[(i+1)*h+j]);
			else if (i == h - 1 && j == 0)
				energy = ->dualGradientEnergy(colorMat[i*h+w - 1], colorMat[i*h+j + 1], colorMat[(i-1)*h+j], colorMat[j]);
			else if (i == h - 1 && j == w - 1)
				energy = ->dualGradientEnergy(colorMat[h*i+j - 1], colorMat[h*i], colorMat[h*(i - 1)+j], colorMat[j]);
			/*
			Edges
			*/
			else if (i == 0)
				energy = ->dualGradientEnergy(colorMat[i*h+j - 1], colorMat[i*h+j + 1], colorMat[(h-1)*h+j], colorMat[(i+1)*h+j]);
			else if (i == h - 1)
				energy = ->dualGradientEnergy(colorMat[i*h+j - 1], colorMat[i*h+j + 1], colorMat[(i-1)*h+j], colorMat[j]);
			else if (j == 0)
				energy = ->dualGradientEnergy(colorMat[i*h+w - 1], colorMat[i*h+j + 1], colorMat[(i-1)*h+j], colorMat[(i+1)*h+j]);
			else if (j == w - 1)
				energy = ->dualGradientEnergy(colorMat[i*h+j - 1], colorMat[i*h+0], colorMat[(i-1)*h+j], colorMat[(i+1)*h+j]);
			/*
			Inside
			*/
			else
				energy = ->dualGradientEnergy(colorMat[i*h+j - 1], colorMat[i*h+j + 1], colorMat[(i-1)*h+j], colorMat[(i+1)*h+j]);
			energyMatrix[i][j] = energy;
		}
	return energyMatrix;
}

long **generateSeamEnergies(int h, int w, long **energyMatrix) {
	/*
	===============================================================================================
	Function that generates the energies of all seams through dynamic programming
	*/
	long **dp = malloc(h * sizeof(long *));
	for (int i = 0; i < h; i++)
		dp[i] = malloc(w * sizeof(long));

	for (int i = 1; i < h; i++)
		for (int j = 0; j < w; j++)
			if (j == 0)
				dp[i][j] = energyMatrix[i][j] + min2(dp[i - 1][j], dp[i - 1][j + 1]);
			else if (j == w - 1)
				dp[i][j] = energyMatrix[i][j] + min2(dp[i - 1][j - 1], dp[i - 1][j]);
			else
				dp[i][j] = energyMatrix[i][j] + min3(dp[i - 1][j - 1], dp[i - 1][j], dp[i - 1][j + 1]);

	return dp;
}

int *determineMinSeam(int h, int w, long **dp) {
	/*
	===============================================================================================
	Function that determines the minimum seam to be deleted from the image
	*/
	int i, j;
	int *verticalSeam = malloc(h * sizeof(int));
	long minEnergy  = 2000000;

	minEnergy  = dp[h - 1][0];
	for (j = 0; j < w; j++)
		if (dp[h - 1][j] < minEnergy ) {
			minEnergy  = dp[h - 1][j];
			verticalSeam[h - 1] = j;
		}

	for (i = h - 2; i >= 0; i--) {
		if (verticalSeam[i + 1] == 0) {
			if (dp[i][verticalSeam[i + 1]] < dp[i][verticalSeam[i + 1] + 1]) {
				verticalSeam[i] = verticalSeam[i + 1];
			} else {
				verticalSeam[i] = verticalSeam[i + 1] + 1;
			}
		} else if (verticalSeam[i + 1] == w - 1) {
			if (dp[i][verticalSeam[i + 1] - 1] < dp[i][verticalSeam[i + 1]]) {
				verticalSeam[i] = verticalSeam[i + 1] - 1;
			} else {
				verticalSeam[i] = verticalSeam[i + 1];
			}
		} else {
			if (dp[i][verticalSeam[i + 1] - 1] < dp[i][verticalSeam[i + 1]] && dp[i][verticalSeam[i + 1] - 1] < dp[i][verticalSeam[i + 1] + 1]) {
				verticalSeam[i] = verticalSeam[i + 1] - 1;
			} else if (dp[i][verticalSeam[i + 1]] < dp[i][verticalSeam[i + 1] + 1]) {
				verticalSeam[i] = verticalSeam[i + 1];
			} else {
				verticalSeam[i] = verticalSeam[i + 1] + 1;
			}
		}
	}

	return verticalSeam;
}

void sceamReduceW(Picture* p, int newW)
{
    int nbRemove = w-p->w;
    for(int k = 0; k< to_be_removed; k++)
    {
        //Energy of each pixel	
        long**energyMatrix = generateEnergyMatrix(p);
        //Detection energy of seams by dynamic programing
        long **dp = generateSeamEnergies(p->h, p->w, energyMatrix);
        //Detection which seams must be removed
        int *verticalSeam = determineMinSeam(p->h, p->w, dp);
        //Remove seam and reduce W
        for(int i = 0; i< h; i++)
        {
            Pixel *newLine = malloc((w-1)*sizeof(Pixel));
            int skipped = 0;
            for(int j = 0; j < w; j++)
            {
                if(verticalSeam[i]== j)
                    skipped = 1;
                else
                    newLine[j-skipped] = p->pixels[i*h+j];
            }
            free(p->pixels[i*h]);
            for(int j = 0; j < w; j++)
            {
                P->pixels[i*h+j] = newLine[j];
            }
        }
        p->w++;;

    }
    free(verticalSeam);
    for(int i = 0; i <h; i++)
    {
        free(energyMatrix[i]);
        free(dp[i]);
    }
    free(energyMatrix);
    free(dp);9
}