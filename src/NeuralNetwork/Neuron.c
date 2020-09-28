#include <stdlio.h>
#include "Neuron.h"

Neuron NewNeuron(double bias, double weight)
{
    Neuron neuron;
    neuron.bias = bias;
    neuron.weight = weight;
    return neuron;
}
