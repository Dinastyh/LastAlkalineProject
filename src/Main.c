#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Network.h"
#include "Training.h"
#include "Debug.h"
#include "write_read_brain.h"

int main()
{
    
    Network net = newNetwork(2,2,1,1);
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
    double data[2] = {0.0, 0.0};
    double target[1] = {0.0};

   for(int i = 0; i < 1000000; i ++)
   {
        switch(i%4)
        {
            case 0:
                target[0] = 0;
            break;
            case 1:
                data[0] = 0.0;
                data[1] = 1.0;
                target[0] = 1.0;
            break;
            case 2:
                data[0] = 1.0;
                data[1] = 0.0;
                target[0] = 1.0;
            break;
            case 3:
                data[0] = 1.0;
                data[1] = 1.0;
                target[0] = 0;
            break;
        }

        forwardPropagation(&net, data, target);
        backPropagation(&net);
        gradientDescent(&net, 0.5);
   }

    for(int i = 0; i < 4; i ++)
   {
        switch(i%4)
        {
            case 0:
                target[0] = 0;
            break;
            case 1:
                data[0] = 0.0;
                data[1] = 1.0;
                target[0] = 1.0;
            break;
            case 2:
                data[0] = 1.0;
                data[1] = 0.0;
                target[0] = 1.0;
            break;
            case 3:
                data[0] = 1.0;
                data[1] = 1.0;
                target[0] = 0;
            break;
        }
        checkForwardPropagation(&net, data, target);
        printLayerValues(net.layers[2]);
   }

    printNetwork(&net);

   /*
    for (size_t i = 0; i < 10; i++)
    {
        double data[2] = {0.0, 0.0};
        double target[1] = {0.0};
        switch(i%4)
        {
            case 0:
                target[0] = 0;
            break;
            case 1:
                data[0] = 0.0;
                data[1] = 1.0;
                target[0] = 1.0;
            break;
            case 2:
                data[0] = 1.0;
                data[1] = 0.0;
                target[0] = 1.0;
            break;
            case 3:
                data[0] = 1.0;
                data[1] = 1.0;
                target[0] = 0;
            break;
        }

        if((i < 10) || i > 1000000 - 10)
        {
            printf("Data In\n");
            print_vector(2, data);
            printf("Target\n");
            print_vector(1, target);
        }
        
        forwardPropagation(&net, data, target);
        backPropagation(&net);
        gradientDescent(&net, 12);

        if((i < 10) || i > 1000000 - 10)
        {   
            double lastvalue = net.layers[2].neurons[0].value;
            printf("last layer neuron %d value %lf\n",0,lastvalue);
            printf("\n");
            printNetwork(&net);
        }
        
    }
    */
    
    return 0;
}
