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
    Brain brain = NewBrain();
    init_random_brain(&brain);
    print_brain(&brain);
    write_brain(&brain);

    Brain brain2 = read_brain("brain.txt");
    print_brain(&brain2);

    return 0;
}
