#include <stdlio.h>
#include <time.h>
#include <math.h>
#include "Neuron.h"

Neuron NewNeuron(double bias, double weight)
{
    Neuron neuron;
    neuron.bias = bias;
    neuron.weight = weight;
    neuron.value = 0;
    return neuron;
}

void init_random_neuron(Neuron neuron)
{
    double random_value1;
    double random_value2;
    double buffer;
    double buffer2;
    srand ( time ( NULL));
    //box-muller for gaussian distribution
    random_value1 = (double)rand()/RAND_MAX;//double in range ]0,1]
    random_value2 = (double)rand()/RAND_MAX;//double in range ]0,1]
    buffer = random_value1;
    buffer = random_value2;

    random_value1 = sqrt(-2log(buffer)) * cos(2*pi*buffer2);
    random_value2 = sqrt(-2log(buffer)) * sin(2*pi*buffer2);

    neuron.bias = random_value1;
    neuron.weight = random_value2;
}