#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "NeuralNetwork/Network.h"
#include "NeuralNetwork/Training.h"
#include "NeuralNetwork/Debug.h"
#include "NeuralNetwork/write_read_brain.h"
#include "PictureUtils/Bmp24.h"

int main()
{
    #if 0
    size_t sizeInput = 40 * 40;
    size_t sizeOutput = 66;
    
    Network net = newNetwork(sizeInput, 80, sizeOutput, 3);
    
    initNetwork(&net);
    writeNetwork(&net);
    #endif

    #if 1
    Network net = readNetwork("network.txt");
    //printNetwork(&net);
    #endif

    #if 0
    size_t nbEpoch = 1000000;
    size_t nbElement = 52536;
    size_t batchSize = 1;
    training(&net, nbEpoch, batchSize, nbElement);
    writeNetwork(&net);
    #endif

    #if 1
    size_t nbTestElement = 52536;

    TestNetwork(&net, nbTestElement);
    #endif
    
    return 0;
}
