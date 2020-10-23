#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//#include "NeuralNetwork/Brain.h"
//#include "NeuralNetwork/Neuron.h"
#include "NeuralNetwork/Network.h"
#include "NeuralNetwork/Debug.h"
#include "NeuralNetwork/write_read_brain.h"
//#include "PictureUtils/bmp24.h"

int main()
{
    srand (time ( NULL));
    Network net = newNetwork(5,2,1,2);
    initNetwork(&net);

    printNetwork(&net);
    writeNetwork(&net);

    //print_brain(&brain2);
    //Network net = readNetwork("network.txt");

    //printf("\n\n\n\n");
    //printf("###############Debug forward propagation##################\n");
    //check_forward_propagation(&brain);

#if 0
    // TRAINING FOR XOR
    int nb_trainings = 10;
    for(int i = 0; i < nb_trainings;i++)
    {
        printf("Training : %d\n",i);
        int choice ={rand()%4};
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

        double end_data[1] = {0};
        printf("Data In :\n");
        print_vector(2,data);
        forward_propagation(&brain, data, end_data);
        printf("Data Out :\n");
        print_vector(1, end_data);
        //printf("Ground Truth :\n");
        //print_vector(1,label);
        printf("Total cost : %lf",mean_square_function(label,end_data));
        printf("\n\n");
        backPropagation(&brain,label,4);
    }
#endif

    return 0;
}
