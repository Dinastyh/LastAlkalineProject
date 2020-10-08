#include "Brain.h"
#include "Neuron.h"

Neuron NewNeuron(double bias)
{
    Neuron neuron;
    neuron.bias = bias;
    neuron.weights = calloc(SIZE_LAYERS,(sizeof(double)));
    neuron.value = 0;
    neuron.gradient = 0;
    return neuron;
}

void init_random_neuron(Neuron* neuron)
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
    buffer2 = random_value2;

    random_value1 = sqrt(-2*log(buffer)) * cos(2*M_PI*buffer2);

    neuron->bias = random_value1;

    for(int i = 0; i < SIZE_LAYERS; i+=2)
    {	
	random_value1 = (double)rand()/RAND_MAX;//double in range ]0,1]
	random_value2 = (double)rand()/RAND_MAX;//double in range ]0,1]

	buffer = random_value1;
	buffer2 = random_value2;
	
	random_value1 = sqrt(-2*log(buffer)) * cos(2*M_PI*buffer2);
	random_value2 = sqrt(-2*log(buffer)) * sin(2*M_PI*buffer2);
	
	neuron->weights[i] = random_value1;
	neuron->weights[i+1] = random_value2;

    }
}


