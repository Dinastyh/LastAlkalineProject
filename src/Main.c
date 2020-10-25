#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//#include "NeuralNetwork/Brain.h"
//#include "NeuralNetwork/Neuron.h"
#include "NeuralNetwork/Network.h"
#include "NeuralNetwork/Debug.h"
#include "NeuralNetwork//Training.h"
#include "NeuralNetwork/write_read_brain.h"
//#include "PictureUtils/bmp24.h"

int main()
{
    Network net = demoWriteRead(5,3,1,5);
    double input[5] = {1.0,0.2,0.6,0.0,0.8};
    double desiredOutput[3] = {0.0,0.0,1.0};
    demoTraining(&net, input, desiredOutput);

#if 0
    // TRAINING FOR XOR

    for(int i = 0; i < nb_trainings;i++) // one training
    {
        printf("Training : %d\n",i);
        for(int j = 0; j < 4; j++) // one batch of 4
        {
            int choice ={j%4}; //rand()%4
            double label[1] = {0};
            double data[2] = {0.0,0.0};
            switch (choice)
            {
                case 0:
                    break;
                case 1:
                    data[0] = 0.0;
                    data[1] = 1.0;
                    label[0] = 1.0;
                    break;
                case 2:
                    data[0] = 1.0;
                    data[1] = 0.0;
                    label[0] = 1.0;
                    break;
                case 3:
                    data[0] = 1.0;
                    data[1] = 1.0;
                    break;
                default:
                    printf("choice random is not between 0 and 4]");
                    printf("%d",choice);
            }
            printf("Data In :\n");
            print_vector(2,data);
            printf("Forward prop start :\n");
            forwardPropagation(&net, data);
            double cost = meanSquareFunction(label, &net.layers[net.nbLayers-1]);
            printf("Total cost : %lf\n", cost);
            printf("Backprop start :\n");
            backPropagation(&net);
            printf("### backprop end ###\n\n");
        }
        gradientDescent(&net,0.2);
        printf("#### train end ####\n");
        //double endData[1] = {0};

        //printf("Data Out :\n");
        //print_vector(1, endData);
        //printf("Ground Truth :\n");
        //print_vector(1,label);


    }
#endif

    return 0;
}
