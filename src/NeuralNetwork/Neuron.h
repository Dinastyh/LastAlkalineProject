#ifndef _NEURON_H
#define _NEURON_H

struct Neuron
{
    double bias, value, gradient;
    double* weights;
};
typedef struct Neuron Neuron;

Neuron NewNeuron(double bias);
void init_random_neuron(Neuron* neuron);

#endif
