#ifndef _NEURON_H
#define _NEURON_H

struct Neuron
{
    double bias, weight, value;
}
typedef struct Neuron Neuron;

Neuron NewNeuron(double bias, double weight);
void init_random_neuron(Neuron neuron);

#endif
