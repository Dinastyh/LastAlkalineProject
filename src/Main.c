#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include "NeuralNetwork/Brain.h"
#include "NeuralNetwork/Neuron.h"
#include "NeuralNetwork/Debug.h"
#include "NeuralNetwork/write_read_brain.h"

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
    printf("###############Debug forward propagation##################\n");
    check_forward_propagation(&brain);

    return 0;
}
