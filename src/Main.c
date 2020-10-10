#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include "NeuralNetwork/write_read_brain.h"
#include "NeuralNetwork/Brain.h"
#include "NeuralNetwork/Neuron.h"
#include "NeuralNetwork/Debug.h"


int main()
{
    Brain* brain = NewBrain();
    srand (time ( NULL));
    init_random_brain(brain);
    print_brain(brain);

    return 0;
}
