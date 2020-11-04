<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "NeuralNetwork/Brain.h"
#include "NeuralNetwork/Neuron.h"
#include "NeuralNetwork/Debug.h"
#include "NeuralNetwork/write_read_brain.h"
#include "PictureUtils/bmp24.h"

int main(int argc,char** argv)
{
    rand (time ( NULL));
    char commande[][16]=
    {
        "displaypicture"
    }
    switch (argv[1])
    {
        case commande[1]:
            if(argc > 2):
                displayerPicture(argc[3]);
            else:
                return 0
            break;
        default:
            return 0;
    }
    return 0;
}
