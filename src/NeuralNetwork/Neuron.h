#ifndef _NEURON_H
#define _NEURON_H

struct Neuron
{
    double bias, weight;
}
typedef struct Neuron Neuron;

Neuron NewNeuron(double bias, double weight);
#endif
