#include "Brain.h"
#include "Neuron.h"

Neuron NewNeuron()
{
    Neuron neuron;
    neuron.bias = 0;
    neuron.weights = calloc(SIZE_LAYERS,(sizeof(double)));
    neuron.value = 0;
    neuron.gradient = 0;
    return neuron;
}

double box_muller() //box-muller for gaussian distribution (polar method).
{
    double u = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double v = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double r = u * u + v * v;

    if (r == 0 || r > 1) return box_muller();
    return u * sqrt(-2 * log(r) / r) / 3;

}

void init_random_neuron(Neuron* neuron)
{
    neuron->bias = box_muller();

    for(int i = 0; i < SIZE_LAYERS; i+=2)
    {
        neuron->weights[i] = box_muller();
        neuron->weights[i+1] = box_muller();

    }
}


