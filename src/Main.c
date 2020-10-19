#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "NeuralNetwork/Brain.h"
#include "NeuralNetwork/Neuron.h"
#include "NeuralNetwork/Debug.h"
#include "NeuralNetwork/write_read_brain.h"
#include "PictureUtils/bmp24.h"

int main()
{
    srand (time ( NULL));
    //Brain brain = NewBrain();
    //init_random_brain(&brain);
    Brain brain = read_brain("brain.txt");
    print_brain(&brain);
    //write_brain(&brain);
    //print_brain(&brain2);
    
    //printf("\n\n\n\n");
    //printf("###############Debug forward propagation##################\n");
    //check_forward_propagation(&brain);

    // TRAINING FOR XOR
    int nb_trainings = 1000;
    for(int i = 0; i < nb_trainings;i++)
    {
        printf("Training : %d\n",i);
        double data[2] ={rand()%2, rand()%2};
        double label[1] = {0};
        if ((data[0] == 0.0 && data[1] == 1.0) || (data[0] == 1.0 && data[1] == 0.0))//xor
            label[0] = 1.0;

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
        calculate_gradient(&brain,label);
        update_weights(&brain,0.2,1);
    }




    return 0;
}
