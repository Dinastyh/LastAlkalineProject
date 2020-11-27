#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "NeuralNetwork/Network.h"
#include "NeuralNetwork/Training.h"
#include "NeuralNetwork/Debug.h"
#include "NeuralNetwork/write_read_brain.h"

int main()
{
    size_t sizeInput = 40 * 40;
    size_t sizeOutput = 66;
    
    Network net = newNetwork(sizeInput, 80, sizeOutput, 3);
    initNetwork(&net);
    printNetwork(&net);
    writeNetwork(&net);
    
    /*
    Network net = readNetwork("network.txt");
    printNetwork(&net);
    */

    /*
    checkForwardPropagation(&net, input, target);
    printLayerValues(net.layers[0]);
    printLayerValues(net.layers[1]);
    printLayerValues(net.layers[2]);

    printf("\n");
    backPropagation(&net);

    printLayerDerivatives(net.layers[1]);
    printLayerDerivatives(net.layers[2]);
    */
    double *data = malloc(sizeInput*sizeof(double));
    double *target = calloc(sizeOutput * sizeof(double));

    size_t nbEpoch = 100;

   
    checkForwardPropagation(&net, data, target);
    printLayerValues(net.layers[2]);
   

    return 0;
}
